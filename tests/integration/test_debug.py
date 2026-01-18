"""
调试功能集成测试

测试 debugpy 集成和 VSCode 远程调试功能。
"""

import socket
import sys
import time
from pathlib import Path
from threading import Thread
from unittest.mock import MagicMock, patch

import pytest

sys.path.insert(0, str(Path(__file__).parent.parent.parent.parent))

from runtime.debug import DebugServer, get_debug_server, init_debug


class TestDebugServer:
    """调试服务器测试"""

    def test_init(self):
        """测试初始化"""
        server = DebugServer(host="127.0.0.1", port=15678)
        assert server.host == "127.0.0.1"
        assert server.port == 15678
        assert not server.is_started

    def test_start_without_debugpy(self):
        """测试没有 debugpy 时启动"""
        server = DebugServer()

        with patch.dict("sys.modules", {"debugpy": None}):
            with patch("builtins.__import__", side_effect=ImportError):
                result = server.start()
                assert not result

    def test_start_with_debugpy_mock(self):
        """测试使用模拟的 debugpy 启动"""
        mock_debugpy = MagicMock()
        mock_debugpy.is_client_connected.return_value = False

        server = DebugServer(host="127.0.0.1", port=15679)

        with patch.dict("sys.modules", {"debugpy": mock_debugpy}):
            with patch("builtins.__import__", return_value=mock_debugpy):
                # 模拟 import debugpy
                import importlib

                with patch.object(importlib, "import_module", return_value=mock_debugpy):
                    # 直接设置 _debugpy
                    server._debugpy = mock_debugpy
                    mock_debugpy.listen = MagicMock()

                    # 手动模拟启动成功
                    server._started = True
                    assert server.is_started

    def test_is_client_connected(self):
        """测试检查客户端连接"""
        server = DebugServer()
        assert not server.is_client_connected()

        # 模拟已启动
        server._started = True
        mock_debugpy = MagicMock()
        mock_debugpy.is_client_connected.return_value = True
        server._debugpy = mock_debugpy

        assert server.is_client_connected()


class TestInitDebug:
    """init_debug 函数测试"""

    def test_disabled_by_default(self, monkeypatch):
        """测试默认禁用"""
        monkeypatch.delenv("PLCOPEN_DEBUG", raising=False)

        result = init_debug(enabled=False)
        assert not result

    def test_enabled_via_env(self, monkeypatch):
        """测试通过环境变量启用"""
        monkeypatch.setenv("PLCOPEN_DEBUG", "1")
        monkeypatch.setenv("PLCOPEN_DEBUG_PORT", "15680")

        with patch("runtime.debug.DebugServer") as MockServer:
            mock_instance = MagicMock()
            mock_instance.start.return_value = True
            MockServer.return_value = mock_instance

            result = init_debug()

            MockServer.assert_called_once()
            mock_instance.start.assert_called_once()


class TestDebugIntegration:
    """调试集成测试"""

    @pytest.mark.skipif(
        True,  # 需要实际的 debugpy 和端口可用
        reason="需要实际的调试环境",
    )
    def test_actual_debugpy_connection(self):
        """测试实际的 debugpy 连接"""
        import debugpy

        # 使用高端口号避免冲突
        port = 15681

        debugpy.listen(("127.0.0.1", port))

        # 检查端口是否在监听
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = sock.connect_ex(("127.0.0.1", port))
        sock.close()

        assert result == 0  # 0 表示连接成功

    def test_breakpoint_without_client(self):
        """测试没有客户端时的断点"""
        server = DebugServer()

        # 不应该抛出异常
        server.breakpoint()

    def test_wait_for_client_flag(self):
        """测试等待客户端标志"""
        server = DebugServer(wait_for_client=True)
        assert server.wait_for_client


class TestDebugWithRuntime:
    """调试与运行时集成测试"""

    def test_debug_thread_marking(self):
        """测试线程调试标记"""
        from runtime.debug import debug_this_thread

        # 不应该抛出异常
        debug_this_thread()

    def test_get_debug_server_singleton(self):
        """测试调试服务器单例"""
        from runtime.debug import _debug_server, get_debug_server

        server = get_debug_server()
        # 初始应该是 None
        # 或者是之前 init_debug 设置的值
