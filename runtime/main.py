"""
PLCOpen 运行时入口

提供嵌入式 Python 运行时的主入口点。
"""

import logging
import os
import signal
import sys
import time
from pathlib import Path
from typing import Any, Dict, Optional

# Python 版本检查
MIN_PYTHON_VERSION = (3, 10)
if sys.version_info < MIN_PYTHON_VERSION:
    sys.exit(f"错误: 需要 Python {MIN_PYTHON_VERSION[0]}.{MIN_PYTHON_VERSION[1]} 或更高版本，"
             f"当前版本: {sys.version_info.major}.{sys.version_info.minor}")

from .config import RuntimeConfig
from .debug import init_debug
from .script_manager import ScriptManager

logger = logging.getLogger(__name__)


def check_environment() -> list[str]:
    """
    检查运行时环境

    验证 Python 解释器配置和依赖项可用性。

    Returns:
        错误消息列表，空列表表示环境正常
    """
    errors = []

    # 检查 plcopen 模块可用性
    try:
        import plcopen  # noqa: F401
    except ImportError as e:
        errors.append(f"plcopen 模块未安装或无法加载: {e}")

    # 检查 watchdog 可用性
    try:
        import watchdog  # noqa: F401
    except ImportError:
        errors.append("watchdog 模块未安装，热重载功能将不可用")

    # 检查调试器可用性
    try:
        import debugpy  # noqa: F401
    except ImportError:
        errors.append("debugpy 模块未安装，远程调试功能将不可用")

    return errors


class Runtime:
    """
    PLCOpen 运行时

    管理脚本生命周期、执行周期、热重载和信号处理。
    """

    def __init__(self, config: RuntimeConfig):
        """
        初始化运行时

        Args:
            config: 运行时配置
        """
        self.config = config
        self._script_manager: Optional[ScriptManager] = None
        self._running = False
        self._cycle_count = 0
        self._last_cycle_time = 0.0

        # 设置日志
        self._setup_logging()

    @property
    def is_running(self) -> bool:
        """是否正在运行"""
        return self._running

    @property
    def cycle_count(self) -> int:
        """已执行的周期数"""
        return self._cycle_count

    def _setup_logging(self) -> None:
        """配置日志系统"""
        log_dir = Path(self.config.log_dir)
        log_dir.mkdir(parents=True, exist_ok=True)

        log_file = log_dir / "runtime.log"

        # 配置根日志器
        logging.basicConfig(
            level=logging.DEBUG if self.config.debug_enabled else logging.INFO,
            format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
            handlers=[
                logging.StreamHandler(sys.stdout),
                logging.FileHandler(log_file, encoding="utf-8"),
            ],
        )

        logger.info(f"日志初始化完成，日志文件: {log_file}")

    def init(self) -> None:
        """
        初始化运行时

        加载配置、初始化脚本管理器、启动调试服务器。
        """
        logger.info("PLCOpen 运行时初始化...")
        logger.info(f"配置: {self.config}")

        # 验证配置
        errors = self.config.validate()
        if errors:
            for error in errors:
                logger.error(f"配置错误: {error}")
            raise ValueError(f"配置验证失败: {errors}")

        # 确保目录存在
        self.config.ensure_directories()

        # 初始化脚本管理器
        self._script_manager = ScriptManager(
            script_dir=self.config.script_dir,
            max_consecutive_errors=self.config.max_script_errors,
            on_script_change=self._on_script_change,
            on_script_error=self._on_script_error,
        )

        # 加载脚本
        loaded = self._script_manager.scan_and_load()
        logger.info(f"加载了 {len(loaded)} 个脚本: {loaded}")

        # 初始化调试
        if self.config.debug_enabled:
            success = init_debug(
                port=self.config.debug_port,
                wait_for_client=self.config.debug_wait,
                enabled=True,
            )
            if success:
                logger.info(f"调试服务器已启动，端口: {self.config.debug_port}")
            else:
                logger.warning("调试服务器启动失败")

        logger.info("运行时初始化完成")

    def run(self) -> None:
        """
        运行主循环

        进入周期执行循环，直到收到停止信号。
        """
        self._running = True
        self._setup_signal_handlers()

        # 启动文件监控
        if self._script_manager:
            self._script_manager.start_watching()

        logger.info("运行时主循环开始")

        try:
            while self._running:
                cycle_start = time.perf_counter()

                # 执行周期
                self.execute_cycle()

                # 等待下一个周期
                self._wait_cycle(cycle_start)

        except KeyboardInterrupt:
            logger.info("收到键盘中断")
        finally:
            self._cleanup()

        logger.info("运行时主循环结束")

    def execute_cycle(self) -> Dict[str, Any]:
        """
        执行一个周期

        调用所有脚本的 main 函数。

        Returns:
            脚本名称到返回值的映射
        """
        self._cycle_count += 1
        results = {}

        if self._script_manager:
            results = self._script_manager.execute_all()

        return results

    def _wait_cycle(self, cycle_start: Optional[float] = None) -> None:
        """
        等待下一个周期

        Args:
            cycle_start: 周期开始时间，None 使用上次记录的时间
        """
        if cycle_start is None:
            cycle_start = self._last_cycle_time

        elapsed = time.perf_counter() - cycle_start
        sleep_time = self.config.cycle_time - elapsed

        if sleep_time > 0:
            time.sleep(sleep_time)
        elif elapsed > self.config.cycle_time * 1.5:
            # 周期超时警告
            logger.warning(
                f"周期 {self._cycle_count} 超时: {elapsed:.3f}s > {self.config.cycle_time}s"
            )

        self._last_cycle_time = time.perf_counter()

    def check_and_reload(self) -> None:
        """
        检查并重载修改的脚本
        """
        if not self._script_manager:
            return

        # 检查文件变更
        changed = self._script_manager.check_for_changes()
        for name in changed:
            logger.info(f"重载脚本: {name}")
            self._script_manager.reload_script(name)

        # 检查删除的文件
        deleted = self._script_manager.check_for_deletions()
        for name in deleted:
            logger.info(f"移除脚本: {name}")
            self._script_manager.remove_script(name)

    def stop(self) -> None:
        """
        停止运行时
        """
        logger.info("停止运行时...")
        self._running = False

    def _cleanup(self) -> None:
        """
        清理资源
        """
        logger.info("清理资源...")

        if self._script_manager:
            self._script_manager.stop_watching()

        logger.info("清理完成")

    def _setup_signal_handlers(self) -> None:
        """
        设置信号处理器
        """
        if sys.platform != "win32":
            signal.signal(signal.SIGTERM, self._handle_signal)
            signal.signal(signal.SIGHUP, self._handle_signal)

        signal.signal(signal.SIGINT, self._handle_signal)

    def _handle_signal(self, signum: int, frame) -> None:
        """
        处理信号

        Args:
            signum: 信号编号
            frame: 栈帧
        """
        sig_name = signal.Signals(signum).name
        logger.info(f"收到信号: {sig_name}")

        if signum in (signal.SIGTERM, signal.SIGINT):
            self.stop()
        elif sys.platform != "win32" and signum == signal.SIGHUP:
            # SIGHUP 触发配置重载
            logger.info("重载配置...")
            self.check_and_reload()

    def _on_script_change(self, name: str) -> None:
        """
        脚本变更回调

        Args:
            name: 脚本名称
        """
        logger.info(f"脚本已变更: {name}")

    def _on_script_error(self, name: str, error: Exception) -> None:
        """
        脚本错误回调

        Args:
            name: 脚本名称
            error: 异常对象
        """
        logger.error(f"脚本 {name} 执行错误: {error}")


def main() -> int:
    """
    主入口函数

    Returns:
        退出码
    """
    print("PLCOpen 嵌入式运行时 v1.0.0")
    print(f"Python: {sys.version}")
    print("=" * 40)

    # 检查运行环境
    env_errors = check_environment()
    if env_errors:
        for error in env_errors:
            print(f"警告: {error}", file=sys.stderr)

    try:
        # 从环境变量加载配置
        config = RuntimeConfig.from_env()

        # 创建并运行
        runtime = Runtime(config)
        runtime.init()
        runtime.run()

        return 0

    except KeyboardInterrupt:
        print("\n用户中断")
        return 0

    except Exception as e:
        logger.exception(f"运行时错误: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
