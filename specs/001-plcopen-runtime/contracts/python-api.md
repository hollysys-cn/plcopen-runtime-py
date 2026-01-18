# PLCOpen运行时 - Python API契约

**日期**: 2026-01-18
**版本**: 1.0

## 模块结构

```python
plcopen/
├── __init__.py      # 导出所有公共API
├── pid.py           # PID功能块（C扩展包装）
├── first_order.py   # 一阶惯性功能块（C扩展包装）
└── _plcopen.so      # C扩展模块（编译产物）
```

## 公共API

### plcopen.PID

PID控制器功能块。

```python
class PID:
    """
    位置式PID控制器。

    算法: output = Kp * error + Ki * ∫error + Kd * d(error)/dt

    参数:
        kp: 比例增益，默认1.0
        ki: 积分增益，默认0.0
        kd: 微分增益，默认0.0
        out_min: 输出下限，默认-inf
        out_max: 输出上限，默认+inf
        dt: 采样周期（秒），默认0.1

    示例:
        >>> pid = plcopen.PID(kp=1.0, ki=0.1, kd=0.05)
        >>> output = pid.execute(setpoint=100.0, pv=80.0)
        >>> print(f"控制输出: {output}")
    """

    def __init__(
        self,
        kp: float = 1.0,
        ki: float = 0.0,
        kd: float = 0.0,
        out_min: float = float('-inf'),
        out_max: float = float('inf'),
        dt: float = 0.1
    ) -> None:
        """创建PID实例。"""
        ...

    def execute(self, setpoint: float, pv: float) -> float:
        """
        执行一步PID计算。

        参数:
            setpoint: 设定值
            pv: 过程值（反馈）

        返回:
            float: 控制输出值

        异常:
            ValueError: 输入值为NaN或Inf时抛出
        """
        ...

    def reset(self) -> None:
        """重置内部状态（积分累积、历史误差）。"""
        ...

    def get_state(self) -> dict:
        """
        获取内部状态（用于热重载时保存）。

        返回:
            dict: 包含所有内部状态的字典
        """
        ...

    def set_state(self, state: dict) -> None:
        """
        恢复内部状态（用于热重载时恢复）。

        参数:
            state: get_state()返回的状态字典
        """
        ...

    # 属性（可读写）
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, value: float) -> None: ...

    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, value: float) -> None: ...

    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, value: float) -> None: ...

    @property
    def out_min(self) -> float: ...
    @out_min.setter
    def out_min(self, value: float) -> None: ...

    @property
    def out_max(self) -> float: ...
    @out_max.setter
    def out_max(self, value: float) -> None: ...

    # 只读属性
    @property
    def output(self) -> float:
        """上一次计算的输出值。"""
        ...

    @property
    def error(self) -> float:
        """上一次计算的偏差值。"""
        ...

    @property
    def saturated(self) -> bool:
        """上一次输出是否被限幅。"""
        ...
```

### plcopen.FirstOrder

一阶惯性（一阶滞后）功能块。

```python
class FirstOrder:
    """
    一阶惯性滤波器。

    传递函数: G(s) = K / (Ts + 1)
    离散化: y[n] = alpha * K * x[n] + (1-alpha) * y[n-1]
            alpha = dt / (T + dt)

    参数:
        k: 增益，默认1.0
        t: 时间常数（秒），默认1.0
        dt: 采样周期（秒），默认0.1

    示例:
        >>> fo = plcopen.FirstOrder(k=1.0, t=0.5)
        >>> for _ in range(10):
        ...     output = fo.execute(100.0)
        ...     print(f"输出: {output:.2f}")
    """

    def __init__(
        self,
        k: float = 1.0,
        t: float = 1.0,
        dt: float = 0.1
    ) -> None:
        """创建一阶惯性实例。"""
        ...

    def execute(self, input_value: float) -> float:
        """
        执行一步滤波计算。

        参数:
            input_value: 输入信号

        返回:
            float: 滤波后的输出信号

        异常:
            ValueError: 输入值为NaN或Inf时抛出
        """
        ...

    def reset(self, initial_value: float = 0.0) -> None:
        """
        重置内部状态。

        参数:
            initial_value: 初始输出值，默认0.0
        """
        ...

    def get_state(self) -> dict:
        """获取内部状态。"""
        ...

    def set_state(self, state: dict) -> None:
        """恢复内部状态。"""
        ...

    # 属性（可读写）
    @property
    def k(self) -> float: ...
    @k.setter
    def k(self, value: float) -> None: ...

    @property
    def t(self) -> float: ...
    @t.setter
    def t(self, value: float) -> None:
        """设置时间常数，必须大于0。"""
        ...

    # 只读属性
    @property
    def output(self) -> float:
        """当前输出值。"""
        ...
```

## 脚本约定

### 脚本结构

用户脚本必须遵循以下结构：

```python
# scripts/my_control.py
"""
控制脚本示例。
"""
import plcopen

# 在模块级别创建功能块实例（热重载时状态保留）
pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1)
filter_out = plcopen.FirstOrder(k=1.0, t=0.3)

def main() -> None:
    """
    主循环函数，由运行时按周期调用。

    此函数将被运行时以配置的周期（默认100ms）重复调用。
    不要在此函数内进行阻塞操作。
    """
    # 读取输入（示例：从外部获取）
    setpoint = get_setpoint()
    pv = get_process_value()

    # 执行PID计算
    output = pid.execute(setpoint=setpoint, pv=pv)

    # 滤波输出
    filtered = filter_out.execute(output)

    # 输出到执行机构
    set_actuator(filtered)

def on_reload(saved_states: dict) -> None:
    """
    可选：热重载回调。

    当脚本被修改并重新加载时调用。
    功能块实例状态已自动保留，此回调用于额外的自定义处理。

    参数:
        saved_states: 保存的功能块状态字典
    """
    print("脚本已重新加载")

def on_unload() -> None:
    """
    可选：卸载回调。

    当脚本被删除或运行时关闭时调用。
    用于清理资源。
    """
    print("脚本已卸载")
```

### 命名规范

| 项目 | 规范 | 示例 |
|------|------|------|
| 脚本文件名 | 小写字母+下划线，有效Python标识符 | `temperature_control.py` |
| 功能块变量 | 小写字母+下划线 | `pid_loop1`, `filter_in` |
| 函数 | 小写字母+下划线 | `main()`, `on_reload()` |

## 错误处理

### 异常类型

```python
class PlcopenError(Exception):
    """PLCOpen运行时基础异常。"""
    pass

class FunctionBlockError(PlcopenError):
    """功能块执行错误。"""
    pass

class ParameterError(PlcopenError):
    """参数验证错误。"""
    pass
```

### 错误码

| 码 | 名称 | 说明 |
|----|------|------|
| 0 | SUCCESS | 成功 |
| 1 | INVALID_PARAM | 参数无效 |
| 2 | EXECUTION_ERROR | 执行错误 |
| 3 | STATE_ERROR | 状态错误 |
| 4 | MEMORY_ERROR | 内存分配失败 |

## 线程安全

- 单个功能块实例**非线程安全**，不应在多线程中共享
- 运行时保证每个脚本的`main()`在同一线程中顺序调用
- 功能块实例在脚本间隔离，无需考虑跨脚本访问
