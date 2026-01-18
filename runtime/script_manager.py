"""
PLCOpen 脚本管理器

负责加载、执行、热重载 Python 脚本。
支持 watchdog 文件监控和功能块状态保留。
"""

import importlib.util
import logging
import sys
import time
from dataclasses import dataclass, field
from enum import Enum, auto
from pathlib import Path
from types import ModuleType
from typing import Any, Callable, Dict, List, Optional, Set

logger = logging.getLogger(__name__)


class ScriptState(Enum):
    """脚本状态枚举"""

    UNLOADED = auto()  # 未加载
    LOADED = auto()  # 已加载
    ERROR = auto()  # 加载或执行错误
    DISABLED = auto()  # 被禁用（连续失败）


@dataclass
class ScriptInfo:
    """脚本信息"""

    name: str  # 脚本名称（不含.py）
    path: Path  # 脚本完整路径
    mtime: float  # 最后修改时间
    state: ScriptState = ScriptState.UNLOADED
    module: Optional[ModuleType] = None  # 已加载的模块
    has_main: bool = False  # 是否有main函数
    error_count: int = 0  # 连续错误计数
    last_error: Optional[str] = None  # 最后一次错误信息
    fb_instances: Dict[str, Any] = field(default_factory=dict)  # 功能块实例缓存


class ScriptManager:
    """
    Python 脚本管理器

    功能：
    - 扫描并加载脚本目录中的 .py 文件
    - 执行脚本的 main() 函数
    - 检测文件变更并热重载
    - 保留功能块状态跨重载
    - 错误隔离和自动禁用
    """

    def __init__(
        self,
        script_dir: str,
        max_consecutive_errors: int = 5,
        on_script_change: Optional[Callable[[str], None]] = None,
        on_script_error: Optional[Callable[[str, Exception], None]] = None,
    ):
        """
        初始化脚本管理器

        Args:
            script_dir: 脚本目录路径
            max_consecutive_errors: 最大连续错误次数，超过后禁用脚本
            on_script_change: 脚本变更回调
            on_script_error: 脚本错误回调
        """
        self.script_dir = Path(script_dir)
        self.max_consecutive_errors = max_consecutive_errors
        self.on_script_change = on_script_change
        self.on_script_error = on_script_error

        self.scripts: Dict[str, ScriptInfo] = {}
        self._observer = None
        self._watching = False

        # 确保目录存在
        self.script_dir.mkdir(parents=True, exist_ok=True)

        logger.info(f"脚本管理器初始化，脚本目录: {self.script_dir}")

    @property
    def is_watching(self) -> bool:
        """是否正在监控文件变更"""
        return self._watching

    def scan_and_load(self) -> List[str]:
        """
        扫描目录并加载所有脚本

        Returns:
            加载成功的脚本名称列表
        """
        loaded = []

        for path in self.script_dir.glob("*.py"):
            # 忽略 __开头的文件
            if path.name.startswith("__"):
                continue

            name = path.stem
            if name not in self.scripts:
                self._load_script(name, path)

            if self.scripts.get(name) and self.scripts[name].state == ScriptState.LOADED:
                loaded.append(name)

        logger.info(f"扫描完成，加载了 {len(loaded)} 个脚本")
        return loaded

    def _load_script(self, name: str, path: Path) -> bool:
        """
        加载单个脚本

        Args:
            name: 脚本名称
            path: 脚本路径

        Returns:
            是否加载成功
        """
        logger.debug(f"加载脚本: {name} ({path})")

        try:
            mtime = path.stat().st_mtime

            # 创建模块规格
            spec = importlib.util.spec_from_file_location(
                f"plcopen_scripts.{name}",
                path,
            )

            if spec is None or spec.loader is None:
                raise ImportError(f"无法创建模块规格: {path}")

            # 创建模块
            module = importlib.util.module_from_spec(spec)

            # 添加到 sys.modules 以支持相对导入
            sys.modules[spec.name] = module

            # 执行模块代码
            spec.loader.exec_module(module)

            # 检查是否有 main 函数
            has_main = hasattr(module, "main") and callable(module.main)

            # 更新脚本信息
            self.scripts[name] = ScriptInfo(
                name=name,
                path=path,
                mtime=mtime,
                state=ScriptState.LOADED,
                module=module,
                has_main=has_main,
            )

            if has_main:
                logger.info(f"脚本加载成功: {name}")
            else:
                logger.warning(f"脚本 {name} 没有 main 函数")

            return True

        except Exception as e:
            logger.error(f"加载脚本 {name} 失败: {e}")

            self.scripts[name] = ScriptInfo(
                name=name,
                path=path,
                mtime=path.stat().st_mtime if path.exists() else 0,
                state=ScriptState.ERROR,
                last_error=str(e),
            )

            return False

    def execute_script(self, name: str) -> Any:
        """
        执行脚本的 main 函数

        Args:
            name: 脚本名称

        Returns:
            main 函数的返回值

        Raises:
            KeyError: 脚本不存在
            RuntimeError: 脚本未加载或已禁用
        """
        if name not in self.scripts:
            raise KeyError(f"脚本不存在: {name}")

        info = self.scripts[name]

        if info.state == ScriptState.DISABLED:
            raise RuntimeError(f"脚本已禁用: {name}")

        if info.state != ScriptState.LOADED:
            raise RuntimeError(f"脚本未加载: {name}")

        if not info.has_main:
            raise RuntimeError(f"脚本没有 main 函数: {name}")

        try:
            result = info.module.main()

            # 成功执行，重置错误计数
            info.error_count = 0
            info.last_error = None

            return result

        except Exception as e:
            info.error_count += 1
            info.last_error = str(e)

            logger.error(f"执行脚本 {name} 失败 (第{info.error_count}次): {e}")

            # 检查是否需要禁用
            if info.error_count >= self.max_consecutive_errors:
                info.state = ScriptState.DISABLED
                logger.warning(
                    f"脚本 {name} 连续失败 {info.error_count} 次，已自动禁用"
                )

            # 触发错误回调
            if self.on_script_error:
                self.on_script_error(name, e)

            raise

    def execute_all(self) -> Dict[str, Any]:
        """
        执行所有已加载且有 main 函数的脚本

        Returns:
            脚本名称到返回值的映射
        """
        results = {}

        for name, info in self.scripts.items():
            if info.state == ScriptState.LOADED and info.has_main:
                try:
                    results[name] = self.execute_script(name)
                except Exception as e:
                    results[name] = e

        return results

    def check_for_changes(self) -> Set[str]:
        """
        检查文件变更

        Returns:
            需要重载的脚本名称集合
        """
        changed = set()

        # 检查现有脚本的修改
        for name, info in list(self.scripts.items()):
            if info.path.exists():
                current_mtime = info.path.stat().st_mtime
                if current_mtime > info.mtime:
                    changed.add(name)
                    logger.debug(f"检测到脚本修改: {name}")

        # 检查新文件
        for path in self.script_dir.glob("*.py"):
            if path.name.startswith("__"):
                continue

            name = path.stem
            if name not in self.scripts:
                changed.add(name)
                logger.debug(f"检测到新脚本: {name}")

        return changed

    def check_for_deletions(self) -> Set[str]:
        """
        检查已删除的脚本

        Returns:
            已删除的脚本名称集合
        """
        deleted = set()

        for name, info in list(self.scripts.items()):
            if not info.path.exists():
                deleted.add(name)
                logger.debug(f"检测到脚本删除: {name}")

        return deleted

    def reload_script(self, name: str, preserve_state: bool = True) -> bool:
        """
        重载脚本

        Args:
            name: 脚本名称
            preserve_state: 是否保留功能块状态

        Returns:
            是否重载成功
        """
        if name not in self.scripts:
            logger.warning(f"无法重载不存在的脚本: {name}")
            return False

        info = self.scripts[name]

        # 保存状态
        saved_states = {}
        if preserve_state and info.state == ScriptState.LOADED:
            saved_states = self.get_script_fb_states(name)
            logger.debug(f"保存脚本 {name} 的功能块状态: {list(saved_states.keys())}")

        # 卸载旧模块
        self.unload_script(name)

        # 重新加载
        if not info.path.exists():
            logger.warning(f"脚本文件不存在: {info.path}")
            return False

        success = self._load_script(name, info.path)

        # 恢复状态
        if success and preserve_state and saved_states:
            self.set_script_fb_states(name, saved_states)
            logger.debug(f"恢复脚本 {name} 的功能块状态")

        # 触发变更回调
        if success and self.on_script_change:
            self.on_script_change(name)

        return success

    def unload_script(self, name: str) -> None:
        """
        卸载脚本

        Args:
            name: 脚本名称
        """
        if name not in self.scripts:
            return

        info = self.scripts[name]

        # 从 sys.modules 移除
        module_name = f"plcopen_scripts.{name}"
        if module_name in sys.modules:
            del sys.modules[module_name]

        # 清理引用
        info.module = None
        info.state = ScriptState.UNLOADED
        info.fb_instances.clear()

        logger.debug(f"卸载脚本: {name}")

    def remove_script(self, name: str) -> None:
        """
        移除脚本（从管理器中删除）

        Args:
            name: 脚本名称
        """
        self.unload_script(name)

        if name in self.scripts:
            del self.scripts[name]
            logger.info(f"移除脚本: {name}")

    def get_script_fb_states(self, name: str) -> Dict[str, Any]:
        """
        获取脚本中所有功能块的状态

        Args:
            name: 脚本名称

        Returns:
            功能块名称到状态的映射
        """
        states = {}

        if name not in self.scripts:
            return states

        info = self.scripts[name]
        if info.module is None:
            return states

        # 遍历模块属性，查找有 get_state 方法的对象
        for attr_name in dir(info.module):
            if attr_name.startswith("_"):
                continue

            try:
                obj = getattr(info.module, attr_name)

                # 检查是否有 get_state 方法
                if hasattr(obj, "get_state") and callable(obj.get_state):
                    states[attr_name] = obj.get_state()

            except Exception as e:
                logger.warning(f"获取 {name}.{attr_name} 状态失败: {e}")

        return states

    def set_script_fb_states(self, name: str, states: Dict[str, Any]) -> None:
        """
        设置脚本中功能块的状态

        Args:
            name: 脚本名称
            states: 功能块名称到状态的映射
        """
        if name not in self.scripts:
            return

        info = self.scripts[name]
        if info.module is None:
            return

        for attr_name, state in states.items():
            try:
                if hasattr(info.module, attr_name):
                    obj = getattr(info.module, attr_name)

                    if hasattr(obj, "set_state") and callable(obj.set_state):
                        obj.set_state(state)
                        logger.debug(f"恢复 {name}.{attr_name} 状态")

            except Exception as e:
                logger.warning(f"设置 {name}.{attr_name} 状态失败: {e}")

    def start_watching(self) -> None:
        """启动文件监控"""
        if self._watching:
            return

        try:
            from watchdog.events import FileSystemEventHandler
            from watchdog.observers import Observer

            class ScriptEventHandler(FileSystemEventHandler):
                def __init__(handler_self, manager: "ScriptManager"):
                    handler_self.manager = manager
                    handler_self._last_event_time: Dict[str, float] = {}

                def _should_process(handler_self, path: str) -> bool:
                    """防抖：忽略短时间内的重复事件"""
                    now = time.time()
                    last = handler_self._last_event_time.get(path, 0)
                    if now - last < 0.5:  # 500ms 防抖
                        return False
                    handler_self._last_event_time[path] = now
                    return True

                def on_modified(handler_self, event):
                    if event.is_directory:
                        return

                    path = Path(event.src_path)
                    if path.suffix != ".py" or path.name.startswith("__"):
                        return

                    if not handler_self._should_process(event.src_path):
                        return

                    name = path.stem
                    logger.info(f"检测到脚本修改: {name}")
                    handler_self.manager.reload_script(name)

                def on_created(handler_self, event):
                    if event.is_directory:
                        return

                    path = Path(event.src_path)
                    if path.suffix != ".py" or path.name.startswith("__"):
                        return

                    if not handler_self._should_process(event.src_path):
                        return

                    name = path.stem
                    logger.info(f"检测到新脚本: {name}")
                    handler_self.manager._load_script(name, path)

                    if handler_self.manager.on_script_change:
                        handler_self.manager.on_script_change(name)

                def on_deleted(handler_self, event):
                    if event.is_directory:
                        return

                    path = Path(event.src_path)
                    if path.suffix != ".py":
                        return

                    name = path.stem
                    if name in handler_self.manager.scripts:
                        logger.info(f"检测到脚本删除: {name}")
                        handler_self.manager.remove_script(name)

            self._observer = Observer()
            handler = ScriptEventHandler(self)
            self._observer.schedule(handler, str(self.script_dir), recursive=False)
            self._observer.start()
            self._watching = True

            logger.info("文件监控已启动")

        except ImportError:
            logger.warning("watchdog 未安装，无法启用文件监控")

    def stop_watching(self) -> None:
        """停止文件监控"""
        if not self._watching or self._observer is None:
            return

        self._observer.stop()
        self._observer.join(timeout=2.0)
        self._observer = None
        self._watching = False

        logger.info("文件监控已停止")

    def enable_script(self, name: str) -> bool:
        """
        重新启用已禁用的脚本

        Args:
            name: 脚本名称

        Returns:
            是否成功启用
        """
        if name not in self.scripts:
            return False

        info = self.scripts[name]
        if info.state != ScriptState.DISABLED:
            return False

        info.state = ScriptState.LOADED
        info.error_count = 0
        info.last_error = None

        logger.info(f"脚本已重新启用: {name}")
        return True

    def get_status(self) -> Dict[str, Dict[str, Any]]:
        """
        获取所有脚本状态

        Returns:
            脚本名称到状态信息的映射
        """
        status = {}

        for name, info in self.scripts.items():
            status[name] = {
                "state": info.state.name,
                "has_main": info.has_main,
                "error_count": info.error_count,
                "last_error": info.last_error,
                "path": str(info.path),
            }

        return status
