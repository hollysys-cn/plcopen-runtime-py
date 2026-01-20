"""
PLCOpen 功能块运行时

提供工业控制领域常用的功能块：
  - PID: 位置式PID控制器
  - PIDA: 带过程值报警的PID控制器（IEC61131-3标准）
  - FirstOrder: 一阶惯性滤波器

示例:
    >>> import plcopen
    >>> pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1)
    >>> output = pid.execute(setpoint=100.0, pv=80.0)
    
    >>> pida = plcopen.PIDA(kp=100.0, ti=30.0, td=5.0)
    >>> pida.sp = 60.0
    >>> pida.mode = plcopen.PIDA_MODE_AUTO
    >>> output = pida.execute(pv=45.0)
"""

# 导入C扩展模块中的所有公共符号
try:
    from .plcopen import (
        # 功能块
        PID, 
        FirstOrder,
        PIDA,
        # PIDA模式常量
        PIDA_MODE_MANUAL,
        PIDA_MODE_AUTO,
        PIDA_MODE_CASCADE,
        PIDA_MODE_MANUAL_TRACK,
        PIDA_MODE_AUTO_TRACK,
        # PIDA类型常量
        PIDA_TYPE_SINGLE,
        PIDA_TYPE_CASCADE_MASTER,
        PIDA_TYPE_CASCADE_SLAVE,
        PIDA_TYPE_EXTERNAL_SP,
        # PIDA公式常量
        PIDA_EQN_STANDARD,
        PIDA_EQN_DERIVATIVE_FIRST,
        PIDA_EQN_PD_FIRST,
        # 版本信息
        version, 
        list_types, 
        __version__,
    )
except ImportError as e:
    import sys
    raise ImportError(
        f"无法加载PLCOpen C扩展模块: {e}\n"
        f"请确保已正确编译C扩展并安装到Python路径中。\n"
        f"Python路径: {sys.path}"
    ) from e

__all__ = [
    # 功能块
    "PID", 
    "FirstOrder",
    "PIDA",
    # PIDA模式常量
    "PIDA_MODE_MANUAL",
    "PIDA_MODE_AUTO",
    "PIDA_MODE_CASCADE",
    "PIDA_MODE_MANUAL_TRACK",
    "PIDA_MODE_AUTO_TRACK",
    # PIDA类型常量
    "PIDA_TYPE_SINGLE",
    "PIDA_TYPE_CASCADE_MASTER",
    "PIDA_TYPE_CASCADE_SLAVE",
    "PIDA_TYPE_EXTERNAL_SP",
    # PIDA公式常量
    "PIDA_EQN_STANDARD",
    "PIDA_EQN_DERIVATIVE_FIRST",
    "PIDA_EQN_PD_FIRST",
    # 版本信息
    "version", 
    "list_types", 
    "__version__",
]
