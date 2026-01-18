"""
PLCOpen 功能块运行时

提供工业控制领域常用的功能块：
  - PID: 位置式PID控制器
  - FirstOrder: 一阶惯性滤波器

示例:
    >>> import plcopen
    >>> pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1)
    >>> output = pid.execute(setpoint=100.0, pv=80.0)
"""

# 导入C扩展模块中的所有公共符号
try:
    from .plcopen import PID, FirstOrder, version, list_types, __version__
except ImportError as e:
    import sys
    raise ImportError(
        f"无法加载PLCOpen C扩展模块: {e}\n"
        f"请确保已正确编译C扩展并安装到Python路径中。\n"
        f"Python路径: {sys.path}"
    ) from e

__all__ = ["PID", "FirstOrder", "version", "list_types", "__version__"]
