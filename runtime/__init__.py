"""
PLCOpen 运行时模块

嵌入式PLCOpen运行时环境，支持Python脚本调用功能块。
"""

__version__ = "1.0.0"
__author__ = "Hollysys"

from .config import RuntimeConfig, get_config

__all__ = [
    "RuntimeConfig",
    "get_config",
]
