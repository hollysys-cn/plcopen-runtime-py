"""
PLCOpen 运行时集成测试

测试完整的运行时功能，包括主循环、脚本执行、信号处理等。
"""

import os
import signal
import subprocess
import sys
import tempfile
import time
from pathlib import Path
from threading import Thread
from unittest.mock import MagicMock, patch

import pytest

# 添加项目根目录到路径
sys.path.insert(0, str(Path(__file__).parent.parent.parent.parent))

from runtime.config import RuntimeConfig
from runtime.main import Runtime


class TestRuntimeInit:
    """运行时初始化测试"""

    def test_default_config(self, tmp_path):
        """测试默认配置初始化"""
        config = RuntimeConfig(
            script_dir=str(tmp_path / "scripts"),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        assert runtime.config == config
        assert not runtime.is_running

    def test_config_from_env(self, tmp_path, monkeypatch):
        """测试从环境变量读取配置"""
        monkeypatch.setenv("PLCOPEN_SCRIPT_DIR", str(tmp_path / "custom_scripts"))
        monkeypatch.setenv("PLCOPEN_CYCLE_TIME", "0.05")
        monkeypatch.setenv("PLCOPEN_DEBUG", "1")

        config = RuntimeConfig.from_env()
        assert "custom_scripts" in config.script_dir
        assert config.cycle_time == 0.05
        assert config.debug_enabled


class TestRuntimeScriptExecution:
    """运行时脚本执行测试"""

    def test_load_and_execute_script(self, tmp_path):
        """测试加载并执行脚本"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        # 创建测试脚本
        script_file = script_dir / "test_script.py"
        script_file.write_text(
            """
counter = 0

def main():
    global counter
    counter += 1
    return counter
"""
        )

        config = RuntimeConfig(
            script_dir=str(script_dir),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        runtime.init()

        # 执行一个周期
        results = runtime.execute_cycle()

        assert "test_script" in results
        assert results["test_script"] == 1

    def test_multiple_scripts(self, tmp_path):
        """测试多个脚本并行执行"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        (script_dir / "script_a.py").write_text(
            """
def main():
    return "A"
"""
        )

        (script_dir / "script_b.py").write_text(
            """
def main():
    return "B"
"""
        )

        config = RuntimeConfig(
            script_dir=str(script_dir),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        runtime.init()
        results = runtime.execute_cycle()

        assert results["script_a"] == "A"
        assert results["script_b"] == "B"


class TestRuntimeMainLoop:
    """运行时主循环测试"""

    def test_start_stop(self, tmp_path):
        """测试启动和停止"""
        config = RuntimeConfig(
            script_dir=str(tmp_path / "scripts"),
            log_dir=str(tmp_path / "logs"),
            cycle_time=0.01,
        )

        runtime = Runtime(config)
        runtime.init()

        # 在后台线程启动
        def run():
            runtime.run()

        thread = Thread(target=run)
        thread.start()

        # 等待启动
        time.sleep(0.05)
        assert runtime.is_running

        # 停止
        runtime.stop()
        thread.join(timeout=1.0)

        assert not runtime.is_running

    def test_cycle_timing(self, tmp_path):
        """测试周期时间"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        (script_dir / "timing.py").write_text(
            """
import time
times = []

def main():
    times.append(time.time())
    return len(times)
"""
        )

        config = RuntimeConfig(
            script_dir=str(script_dir),
            log_dir=str(tmp_path / "logs"),
            cycle_time=0.05,  # 50ms
        )

        runtime = Runtime(config)
        runtime.init()

        # 运行10个周期
        def run():
            for _ in range(10):
                if not runtime.is_running:
                    break
                runtime.execute_cycle()
                runtime._wait_cycle()

        runtime._running = True
        start = time.time()
        run()
        elapsed = time.time() - start

        # 10个周期应该约500ms
        assert 0.4 < elapsed < 0.7


class TestRuntimeSignalHandling:
    """运行时信号处理测试"""

    @pytest.mark.skipif(
        sys.platform == "win32",
        reason="信号处理在Windows上不同",
    )
    def test_sigterm_graceful_shutdown(self, tmp_path):
        """测试 SIGTERM 优雅关闭"""
        config = RuntimeConfig(
            script_dir=str(tmp_path / "scripts"),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        runtime.init()

        # 模拟信号处理
        runtime._running = True
        runtime._handle_signal(signal.SIGTERM, None)

        assert not runtime.is_running


class TestRuntimeHotReload:
    """运行时热重载测试"""

    def test_script_modification_detected(self, tmp_path):
        """测试检测脚本修改"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        script_file = script_dir / "modifiable.py"
        script_file.write_text(
            """
def main():
    return 1
"""
        )

        config = RuntimeConfig(
            script_dir=str(script_dir),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        runtime.init()

        result1 = runtime.execute_cycle()
        assert result1["modifiable"] == 1

        # 修改脚本
        time.sleep(0.1)
        script_file.write_text(
            """
def main():
    return 2
"""
        )

        # 触发热重载检查
        runtime.check_and_reload()

        result2 = runtime.execute_cycle()
        assert result2["modifiable"] == 2


class TestRuntimeWithFunctionBlocks:
    """运行时功能块集成测试"""

    @pytest.mark.skipif(
        True,  # 需要编译 plcopen 模块后才能运行
        reason="需要编译 plcopen 扩展模块",
    )
    def test_pid_in_script(self, tmp_path):
        """测试脚本中使用PID功能块"""
        script_dir = tmp_path / "scripts"
        script_dir.mkdir()

        (script_dir / "pid_control.py").write_text(
            """
import plcopen

pid = plcopen.PID(kp=1.0, ki=0.1, kd=0.05, out_min=-100, out_max=100)

def main():
    # 模拟温度控制
    setpoint = 100.0
    pv = 80.0  # 当前温度
    output = pid.execute(setpoint=setpoint, pv=pv)
    return output
"""
        )

        config = RuntimeConfig(
            script_dir=str(script_dir),
            log_dir=str(tmp_path / "logs"),
        )

        runtime = Runtime(config)
        runtime.init()
        result = runtime.execute_cycle()

        # PID输出应该是正值（需要加热）
        assert result["pid_control"] > 0


class TestRuntimeDebug:
    """运行时调试功能测试"""

    def test_debug_server_starts(self, tmp_path, monkeypatch):
        """测试调试服务器启动"""
        monkeypatch.setenv("PLCOPEN_DEBUG", "1")

        config = RuntimeConfig(
            script_dir=str(tmp_path / "scripts"),
            log_dir=str(tmp_path / "logs"),
            debug_enabled=True,
            debug_port=15678,  # 使用非标准端口避免冲突
        )

        runtime = Runtime(config)

        # 模拟 debugpy
        with patch("runtime.debug.init_debug") as mock_init:
            mock_init.return_value = True
            runtime.init()
            mock_init.assert_called_once()


class TestRuntimeLogging:
    """运行时日志测试"""

    def test_log_file_created(self, tmp_path):
        """测试创建日志文件"""
        log_dir = tmp_path / "logs"

        config = RuntimeConfig(
            script_dir=str(tmp_path / "scripts"),
            log_dir=str(log_dir),
        )

        runtime = Runtime(config)
        runtime.init()

        # 日志目录应该被创建
        assert log_dir.exists()
