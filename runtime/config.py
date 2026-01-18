"""
PLCOpen 运行时配置管理

从环境变量和配置文件加载配置。
"""

import os
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional


@dataclass
class RuntimeConfig:
    """运行时配置"""

    # 脚本目录
    script_dir: Path = field(default_factory=lambda: Path("scripts"))

    # 目录扫描周期（秒）
    scan_interval: float = 1.0

    # 脚本执行周期（秒）
    cycle_time: float = 0.1

    # 调试配置
    debug_enabled: bool = True
    debug_port: int = 5678
    debug_wait: bool = False  # 是否等待调试器连接后再启动

    # 日志配置
    log_dir: Path = field(default_factory=lambda: Path("logs"))
    log_level: str = "INFO"
    log_max_size: int = 10 * 1024 * 1024  # 10MB
    log_backup_count: int = 5

    # 错误处理
    max_script_errors: int = 5  # 连续错误次数阈值，超过则禁用脚本

    @classmethod
    def from_env(cls) -> "RuntimeConfig":
        """从环境变量加载配置"""
        return cls(
            script_dir=Path(os.getenv("PLCOPEN_SCRIPT_DIR", "scripts")),
            scan_interval=float(os.getenv("PLCOPEN_SCAN_INTERVAL", "1.0")),
            cycle_time=float(os.getenv("PLCOPEN_CYCLE_TIME", "0.1")),
            debug_enabled=os.getenv("PLCOPEN_DEBUG_ENABLED", "true").lower() == "true",
            debug_port=int(os.getenv("PLCOPEN_DEBUG_PORT", "5678")),
            debug_wait=os.getenv("PLCOPEN_DEBUG_WAIT", "false").lower() == "true",
            log_dir=Path(os.getenv("PLCOPEN_LOG_DIR", "logs")),
            log_level=os.getenv("PLCOPEN_LOG_LEVEL", "INFO"),
            log_max_size=int(os.getenv("PLCOPEN_LOG_MAX_SIZE", str(10 * 1024 * 1024))),
            log_backup_count=int(os.getenv("PLCOPEN_LOG_BACKUP_COUNT", "5")),
            max_script_errors=int(os.getenv("PLCOPEN_MAX_SCRIPT_ERRORS", "5")),
        )

    def validate(self) -> None:
        """验证配置有效性"""
        if self.scan_interval <= 0:
            raise ValueError(f"scan_interval 必须大于0，当前值: {self.scan_interval}")

        if self.cycle_time <= 0:
            raise ValueError(f"cycle_time 必须大于0，当前值: {self.cycle_time}")

        if self.debug_port < 1 or self.debug_port > 65535:
            raise ValueError(f"debug_port 必须在1-65535范围内，当前值: {self.debug_port}")

        if self.log_max_size <= 0:
            raise ValueError(f"log_max_size 必须大于0，当前值: {self.log_max_size}")

        if self.log_backup_count < 0:
            raise ValueError(f"log_backup_count 不能为负数，当前值: {self.log_backup_count}")

        if self.max_script_errors < 1:
            raise ValueError(f"max_script_errors 必须大于0，当前值: {self.max_script_errors}")

    def ensure_directories(self) -> None:
        """确保必要的目录存在"""
        self.script_dir.mkdir(parents=True, exist_ok=True)
        self.log_dir.mkdir(parents=True, exist_ok=True)


# 全局配置实例
_config: Optional[RuntimeConfig] = None


def get_config() -> RuntimeConfig:
    """获取全局配置实例"""
    global _config
    if _config is None:
        _config = RuntimeConfig.from_env()
        _config.validate()
    return _config


def set_config(config: RuntimeConfig) -> None:
    """设置全局配置实例"""
    global _config
    config.validate()
    _config = config


def reset_config() -> None:
    """重置全局配置（用于测试）"""
    global _config
    _config = None
