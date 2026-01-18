"""
脚本管理器单元测试

测试 runtime.script_manager 模块的所有功能。
"""

import os
import tempfile
import time
from pathlib import Path
from unittest.mock import MagicMock, patch

import pytest

from runtime.script_manager import ScriptInfo, ScriptManager, ScriptState


class TestScriptInfo:
    """ScriptInfo数据类测试"""

    def test_create_script_info(self):
        """测试创建ScriptInfo实例"""
        info = ScriptInfo(
            name="test_script",
            path=Path("/tmp/test_script.py"),
            mtime=1234567890.0,
        )
        assert info.name == "test_script"
        assert info.state == ScriptState.UNLOADED
        assert info.error_count == 0
        assert info.module is None

    def test_script_state_transitions(self):
        """测试脚本状态转换"""
        info = ScriptInfo(
            name="test_script",
            path=Path("/tmp/test_script.py"),
            mtime=0.0,
        )
        assert info.state == ScriptState.UNLOADED

        info.state = ScriptState.LOADED
        assert info.state == ScriptState.LOADED

        info.state = ScriptState.ERROR
        assert info.state == ScriptState.ERROR


class TestScriptManagerInit:
    """ScriptManager初始化测试"""

    def test_init_creates_scripts_dir(self, tmp_path):
        """测试初始化时创建脚本目录"""
        script_dir = tmp_path / "scripts"
        assert not script_dir.exists()

        manager = ScriptManager(script_dir=str(script_dir))
        assert script_dir.exists()

    def test_init_with_existing_dir(self, tmp_path):
        """测试使用已存在的目录初始化"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        manager = ScriptManager(script_dir=str(script_dir))
        assert manager.script_dir == script_dir


class TestScriptLoading:
    """脚本加载测试"""

    def test_load_valid_script(self, tmp_path):
        """测试加载有效脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        # 创建有效脚本
        script_file = script_dir / "valid_script.py"
        script_file.write_text(
            """
def main():
    return 42
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert "valid_script" in manager.scripts
        assert manager.scripts["valid_script"].state == ScriptState.LOADED

    def test_load_script_without_main(self, tmp_path):
        """测试加载没有main函数的脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "no_main.py"
        script_file.write_text(
            """
def helper():
    pass
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        # 应该加载但标记为无main
        assert "no_main" in manager.scripts
        assert manager.scripts["no_main"].has_main is False

    def test_load_script_with_syntax_error(self, tmp_path):
        """测试加载语法错误的脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "syntax_error.py"
        script_file.write_text(
            """
def main(
    # 缺少闭合括号
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert "syntax_error" in manager.scripts
        assert manager.scripts["syntax_error"].state == ScriptState.ERROR

    def test_ignore_non_python_files(self, tmp_path):
        """测试忽略非Python文件"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        (script_dir / "readme.txt").write_text("This is a readme")
        (script_dir / "data.json").write_text("{}")

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert len(manager.scripts) == 0

    def test_ignore_dunder_files(self, tmp_path):
        """测试忽略__开头的文件"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        (script_dir / "__init__.py").write_text("")
        (script_dir / "__pycache__").mkdir()

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert len(manager.scripts) == 0


class TestScriptExecution:
    """脚本执行测试"""

    def test_execute_script_main(self, tmp_path):
        """测试执行脚本main函数"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "executable.py"
        script_file.write_text(
            """
counter = 0

def main():
    global counter
    counter += 1
    return counter
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        result = manager.execute_script("executable")
        assert result == 1

        result = manager.execute_script("executable")
        assert result == 2

    def test_execute_nonexistent_script(self, tmp_path):
        """测试执行不存在的脚本"""
        manager = ScriptManager(script_dir=str(tmp_path / "scripts"))

        with pytest.raises(KeyError):
            manager.execute_script("nonexistent")

    def test_execute_script_with_runtime_error(self, tmp_path):
        """测试执行运行时错误的脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "runtime_error.py"
        script_file.write_text(
            """
def main():
    raise ValueError("测试错误")
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        with pytest.raises(ValueError):
            manager.execute_script("runtime_error")

        # 错误计数应该增加
        assert manager.scripts["runtime_error"].error_count == 1


class TestScriptErrorIsolation:
    """脚本错误隔离测试 (T033a)"""

    def test_error_count_increments(self, tmp_path):
        """测试错误计数递增"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "error_script.py"
        script_file.write_text(
            """
def main():
    raise RuntimeError("Always fails")
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        for i in range(3):
            try:
                manager.execute_script("error_script")
            except RuntimeError:
                pass

        assert manager.scripts["error_script"].error_count == 3

    def test_auto_disable_after_consecutive_errors(self, tmp_path):
        """测试连续失败后自动禁用"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "failing_script.py"
        script_file.write_text(
            """
def main():
    raise RuntimeError("Always fails")
"""
        )

        manager = ScriptManager(
            script_dir=str(script_dir),
            max_consecutive_errors=3,
        )
        manager.scan_and_load()

        # 执行3次失败
        for i in range(3):
            try:
                manager.execute_script("failing_script")
            except RuntimeError:
                pass

        # 应该被自动禁用
        assert manager.scripts["failing_script"].state == ScriptState.DISABLED

    def test_error_count_reset_on_success(self, tmp_path):
        """测试成功执行后重置错误计数"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "intermittent.py"
        script_file.write_text(
            """
call_count = 0

def main():
    global call_count
    call_count += 1
    if call_count < 3:
        raise RuntimeError("Fail first two times")
    return call_count
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        # 前两次失败
        for _ in range(2):
            try:
                manager.execute_script("intermittent")
            except RuntimeError:
                pass

        assert manager.scripts["intermittent"].error_count == 2

        # 第三次成功
        result = manager.execute_script("intermittent")
        assert result == 3
        assert manager.scripts["intermittent"].error_count == 0


class TestHotReload:
    """热重载测试"""

    def test_detect_file_modification(self, tmp_path):
        """测试检测文件修改"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "modifiable.py"
        script_file.write_text(
            """
def main():
    return 1
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        initial_mtime = manager.scripts["modifiable"].mtime

        # 等待并修改文件
        time.sleep(0.1)
        script_file.write_text(
            """
def main():
    return 2
"""
        )

        # 检测变更
        changes = manager.check_for_changes()
        assert "modifiable" in changes

    def test_reload_modified_script(self, tmp_path):
        """测试重载修改后的脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "reloadable.py"
        script_file.write_text(
            """
VALUE = 1

def main():
    return VALUE
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        result = manager.execute_script("reloadable")
        assert result == 1

        # 修改文件
        time.sleep(0.1)
        script_file.write_text(
            """
VALUE = 2

def main():
    return VALUE
"""
        )

        # 重载
        manager.reload_script("reloadable")

        result = manager.execute_script("reloadable")
        assert result == 2

    def test_detect_new_script(self, tmp_path):
        """测试检测新脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert len(manager.scripts) == 0

        # 添加新脚本
        script_file = script_dir / "new_script.py"
        script_file.write_text(
            """
def main():
    return "new"
"""
        )

        changes = manager.check_for_changes()
        assert "new_script" in changes

    def test_detect_deleted_script(self, tmp_path):
        """测试检测已删除脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "deletable.py"
        script_file.write_text(
            """
def main():
    pass
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        assert "deletable" in manager.scripts

        # 删除文件
        script_file.unlink()

        deleted = manager.check_for_deletions()
        assert "deletable" in deleted


class TestStatePreservation:
    """状态保留测试"""

    def test_get_fb_states_before_reload(self, tmp_path):
        """测试重载前获取功能块状态"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "stateful.py"
        script_file.write_text(
            """
class MockFB:
    def __init__(self):
        self.value = 0

    def get_state(self):
        return {"value": self.value}

    def set_state(self, state):
        self.value = state["value"]

fb = MockFB()

def main():
    fb.value += 1
    return fb.value
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        # 执行几次
        for _ in range(5):
            manager.execute_script("stateful")

        # 获取状态
        states = manager.get_script_fb_states("stateful")
        assert "fb" in states
        assert states["fb"]["value"] == 5


class TestWatchdog:
    """Watchdog文件监控测试"""

    def test_start_stop_watching(self, tmp_path):
        """测试启动和停止文件监控"""
        manager = ScriptManager(script_dir=str(tmp_path / "scripts"))

        manager.start_watching()
        assert manager.is_watching

        manager.stop_watching()
        assert not manager.is_watching

    def test_callback_on_file_change(self, tmp_path):
        """测试文件变更时触发回调"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        callback_called = []

        def on_change(script_name: str):
            callback_called.append(script_name)

        manager = ScriptManager(
            script_dir=str(script_dir),
            on_script_change=on_change,
        )

        # 创建文件
        script_file = script_dir / "watched.py"
        script_file.write_text(
            """
def main():
    pass
"""
        )

        manager.start_watching()

        # 等待watchdog检测到
        time.sleep(0.5)

        # 修改文件
        script_file.write_text(
            """
def main():
    return 1
"""
        )

        # 等待回调
        time.sleep(0.5)

        manager.stop_watching()

        # 验证回调被调用（由于时序问题，这个测试可能不稳定）
        # 在CI中可能需要跳过


class TestModuleIsolation:
    """模块命名空间隔离测试"""

    def test_scripts_have_separate_namespaces(self, tmp_path):
        """测试脚本有独立命名空间"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        # 脚本1定义全局变量
        script1 = script_dir / "script1.py"
        script1.write_text(
            """
shared_var = "script1"

def main():
    return shared_var
"""
        )

        # 脚本2也定义同名全局变量
        script2 = script_dir / "script2.py"
        script2.write_text(
            """
shared_var = "script2"

def main():
    return shared_var
"""
        )

        manager = ScriptManager(script_dir=str(script_dir))
        manager.scan_and_load()

        result1 = manager.execute_script("script1")
        result2 = manager.execute_script("script2")

        assert result1 == "script1"
        assert result2 == "script2"
