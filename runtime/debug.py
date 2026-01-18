"""
PLCOpen 调试支持模块

集成 debugpy 支持 VSCode 远程调试。
"""

import logging
import os
import threading
from typing import Optional

logger = logging.getLogger(__name__)


class DebugServer:
    """
    调试服务器

    使用 debugpy 监听指定端口，允许 VSCode 远程附加调试。
    """

    def __init__(
        self,
        host: str = "0.0.0.0",
        port: int = 5678,
        wait_for_client: bool = False,
    ):
        """
        初始化调试服务器

        Args:
            host: 监听地址
            port: 监听端口
            wait_for_client: 是否等待调试器连接后再继续执行
        """
        self.host = host
        self.port = port
        self.wait_for_client = wait_for_client
        self._started = False
        self._debugpy = None

    @property
    def is_started(self) -> bool:
        """是否已启动"""
        return self._started

    def start(self) -> bool:
        """
        启动调试服务器

        Returns:
            是否启动成功
        """
        if self._started:
            logger.warning("调试服务器已经启动")
            return True

        try:
            import debugpy

            self._debugpy = debugpy

            # 检查是否已经在调试模式
            if debugpy.is_client_connected():
                logger.info("调试器已连接")
                self._started = True
                return True

            # 启动监听
            debugpy.listen((self.host, self.port))
            self._started = True

            logger.info(f"调试服务器已启动，监听 {self.host}:{self.port}")

            if self.wait_for_client:
                logger.info("等待调试器连接...")
                debugpy.wait_for_client()
                logger.info("调试器已连接")

            return True

        except ImportError:
            logger.warning("debugpy 未安装，调试功能不可用")
            return False

        except Exception as e:
            logger.error(f"启动调试服务器失败: {e}")
            return False

    def stop(self) -> None:
        """停止调试服务器"""
        # debugpy 没有官方的停止方法
        # 通常在进程退出时自动清理
        self._started = False
        logger.info("调试服务器已停止")

    def is_client_connected(self) -> bool:
        """
        检查是否有调试器客户端连接

        Returns:
            是否有客户端连接
        """
        if not self._started or self._debugpy is None:
            return False

        try:
            return self._debugpy.is_client_connected()
        except Exception:
            return False

    def breakpoint(self) -> None:
        """
        触发断点

        仅在调试器连接时有效。
        """
        if not self._started or self._debugpy is None:
            return

        try:
            if self._debugpy.is_client_connected():
                self._debugpy.breakpoint()
        except Exception as e:
            logger.debug(f"触发断点失败: {e}")


# 全局调试服务器实例
_debug_server: Optional[DebugServer] = None


def get_debug_server() -> Optional[DebugServer]:
    """获取全局调试服务器实例"""
    return _debug_server


def init_debug(
    host: str = "0.0.0.0",
    port: int = 5678,
    wait_for_client: bool = False,
    enabled: Optional[bool] = None,
) -> bool:
    """
    初始化调试支持

    Args:
        host: 监听地址
        port: 监听端口
        wait_for_client: 是否等待调试器连接
        enabled: 是否启用调试，None 时从环境变量 PLCOPEN_DEBUG 读取

    Returns:
        是否成功初始化
    """
    global _debug_server

    # 检查是否启用
    if enabled is None:
        enabled = os.getenv("PLCOPEN_DEBUG", "0").lower() in ("1", "true", "yes")

    if not enabled:
        logger.debug("调试功能未启用")
        return False

    # 从环境变量读取配置
    host = os.getenv("PLCOPEN_DEBUG_HOST", host)
    port = int(os.getenv("PLCOPEN_DEBUG_PORT", str(port)))
    wait_str = os.getenv("PLCOPEN_DEBUG_WAIT", str(wait_for_client).lower())
    wait_for_client = wait_str.lower() in ("1", "true", "yes")

    # 创建并启动
    _debug_server = DebugServer(
        host=host,
        port=port,
        wait_for_client=wait_for_client,
    )

    return _debug_server.start()


def debug_this_thread() -> None:
    """
    标记当前线程可调试

    在非主线程中调用此函数以支持断点调试。
    """
    if _debug_server is None or not _debug_server.is_started:
        return

    try:
        import debugpy

        debugpy.debug_this_thread()
    except Exception as e:
        logger.debug(f"标记线程可调试失败: {e}")
