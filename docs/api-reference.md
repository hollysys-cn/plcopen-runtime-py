# API 参考文档

## plcopen 模块

PLCOpen 功能块 Python 模块。

```python
import plcopen

# 获取版本
print(plcopen.__version__)  # "1.0.0"
print(plcopen.version())    # "1.0.0"
```

---

## PID 类

位置式 PID 控制器。

### 构造函数

```python
plcopen.PID(
    kp: float = 1.0,      # 比例增益
    ki: float = 0.0,      # 积分增益
    kd: float = 0.0,      # 微分增益
    out_min: float = -inf, # 输出下限
    out_max: float = +inf, # 输出上限
    dt: float = 0.1       # 采样周期（秒）
)
```

**参数说明：**

| 参数 | 类型 | 范围 | 说明 |
|------|------|------|------|
| kp | float | ≥ 0 | 比例增益，控制响应速度 |
| ki | float | ≥ 0 | 积分增益，消除稳态误差 |
| kd | float | ≥ 0 | 微分增益，抑制超调 |
| out_min | float | < out_max | 输出下限 |
| out_max | float | > out_min | 输出上限 |
| dt | float | > 0 | 采样周期，单位秒 |

**异常：**
- `ValueError`: 参数无效（如 kp < 0 或 out_min >= out_max）

**示例：**

```python
# 温度控制 PID
pid = plcopen.PID(
    kp=2.0,
    ki=0.1,
    kd=0.5,
    out_min=0.0,    # 0% 加热功率
    out_max=100.0,  # 100% 加热功率
    dt=0.1          # 100ms 采样周期
)
```

### execute 方法

执行一步 PID 计算。

```python
def execute(self, setpoint: float, pv: float) -> float
```

**参数：**
- `setpoint`: 设定值（目标值）
- `pv`: 过程值（当前测量值）

**返回：**
- `float`: 控制输出值（已限幅）

**异常：**
- `ValueError`: 输入为 NaN 或无穷大

**示例：**

```python
setpoint = 100.0  # 目标温度 100°C
pv = 85.0         # 当前温度 85°C

output = pid.execute(setpoint=setpoint, pv=pv)
print(f"加热功率: {output}%")  # 输出正值，需要加热
```

### reset 方法

重置内部状态。

```python
def reset(self) -> None
```

清除积分器和历史值，从零开始。

**示例：**

```python
pid.reset()
# 积分器清零，适合切换控制模式时调用
```

### get_state 方法

获取内部状态（用于热重载）。

```python
def get_state(self) -> dict
```

**返回：**
```python
{
    "integral": float,     # 积分累积值
    "prev_error": float,   # 上一次误差
    "prev_output": float   # 上一次输出
}
```

### set_state 方法

恢复内部状态（用于热重载）。

```python
def set_state(self, state: dict) -> None
```

**参数：**
- `state`: 由 `get_state()` 返回的状态字典

**异常：**
- `KeyError`: 状态字典缺少必要的键

### 属性

| 属性 | 类型 | 读/写 | 说明 |
|------|------|-------|------|
| kp | float | R/W | 比例增益 |
| ki | float | R/W | 积分增益 |
| kd | float | R/W | 微分增益 |
| out_min | float | R/W | 输出下限 |
| out_max | float | R/W | 输出上限 |
| output | float | R | 上一次输出值 |
| error | float | R | 上一次误差值 |
| saturated | bool | R | 上一次是否限幅 |

**动态调参示例：**

```python
# 运行时调整增益
if oscillating:
    pid.kp *= 0.8  # 减小增益抑制振荡
```

---

## FirstOrder 类

一阶惯性滤波器（一阶低通滤波）。

### 传递函数

$$G(s) = \frac{K}{Ts + 1}$$

### 离散化公式

$$y[n] = \alpha \cdot K \cdot x[n] + (1-\alpha) \cdot y[n-1]$$

其中 $\alpha = \frac{dt}{T + dt}$

### 构造函数

```python
plcopen.FirstOrder(
    k: float = 1.0,   # 增益
    t: float = 1.0,   # 时间常数（秒）
    dt: float = 0.1   # 采样周期（秒）
)
```

**参数说明：**

| 参数 | 类型 | 范围 | 说明 |
|------|------|------|------|
| k | float | 任意 | 增益（可为负） |
| t | float | > 0 | 时间常数，越大响应越慢 |
| dt | float | > 0 | 采样周期 |

**异常：**
- `ValueError`: t ≤ 0 或 dt ≤ 0

**示例：**

```python
# 平滑传感器噪声
filter = plcopen.FirstOrder(
    k=1.0,   # 无增益
    t=0.5,   # 500ms 时间常数
    dt=0.1   # 100ms 采样
)
```

### execute 方法

执行一步滤波计算。

```python
def execute(self, input_value: float) -> float
```

**参数：**
- `input_value`: 输入信号

**返回：**
- `float`: 滤波后的输出

**异常：**
- `ValueError`: 输入为 NaN 或无穷大

**示例：**

```python
raw_value = read_sensor()  # 噪声信号
smooth_value = filter.execute(raw_value)
```

### reset 方法

重置滤波器状态。

```python
def reset(self, initial_value: float = 0.0) -> None
```

**参数：**
- `initial_value`: 初始输出值（可选）

**示例：**

```python
# 重置到当前测量值，避免启动阶跃
current = read_sensor()
filter.reset(current)
```

### get_state / set_state

与 PID 类似，用于热重载时保留滤波器状态。

```python
state = filter.get_state()
# {"prev_output": 45.6}

filter.set_state(state)
```

### 属性

| 属性 | 类型 | 读/写 | 说明 |
|------|------|-------|------|
| k | float | R/W | 增益 |
| t | float | R/W | 时间常数 |
| output | float | R | 当前输出值 |

---

## 运行时模块 (runtime)

### RuntimeConfig 类

运行时配置。

```python
from runtime.config import RuntimeConfig

config = RuntimeConfig(
    script_dir="scripts",
    log_dir="logs",
    cycle_time=0.1,
    debug_enabled=True,
    debug_port=5678,
)
```

**属性：**

| 属性 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| script_dir | str | "scripts" | 脚本目录 |
| log_dir | str | "logs" | 日志目录 |
| cycle_time | float | 0.1 | 主循环周期（秒） |
| debug_enabled | bool | False | 是否启用调试 |
| debug_port | int | 5678 | 调试端口 |
| debug_wait | bool | False | 是否等待调试器连接 |
| max_script_errors | int | 5 | 脚本最大连续错误次数 |

**类方法：**

```python
# 从环境变量加载
config = RuntimeConfig.from_env()
```

**环境变量：**
- `PLCOPEN_SCRIPT_DIR`
- `PLCOPEN_LOG_DIR`
- `PLCOPEN_CYCLE_TIME`
- `PLCOPEN_DEBUG`
- `PLCOPEN_DEBUG_PORT`
- `PLCOPEN_DEBUG_WAIT`

### ScriptManager 类

脚本管理器。

```python
from runtime.script_manager import ScriptManager

manager = ScriptManager(
    script_dir="scripts",
    max_consecutive_errors=5,
    on_script_change=lambda name: print(f"脚本变更: {name}"),
)
```

**方法：**

| 方法 | 说明 |
|------|------|
| `scan_and_load()` | 扫描并加载所有脚本 |
| `execute_script(name)` | 执行指定脚本的 main() |
| `execute_all()` | 执行所有已加载脚本 |
| `reload_script(name)` | 重载脚本（保留状态） |
| `start_watching()` | 开始文件监控 |
| `stop_watching()` | 停止文件监控 |
| `get_status()` | 获取所有脚本状态 |

### Runtime 类

运行时主类。

```python
from runtime.main import Runtime
from runtime.config import RuntimeConfig

config = RuntimeConfig.from_env()
runtime = Runtime(config)
runtime.init()
runtime.run()  # 阻塞运行
```

**方法：**

| 方法 | 说明 |
|------|------|
| `init()` | 初始化运行时 |
| `run()` | 运行主循环（阻塞） |
| `stop()` | 停止运行时 |
| `execute_cycle()` | 执行单个周期 |
| `check_and_reload()` | 检查并重载脚本 |

---

## 错误处理

### Python 异常

| 异常类型 | 触发条件 |
|----------|----------|
| `ValueError` | 参数无效、NaN/Inf 输入 |
| `RuntimeError` | 初始化失败、执行错误 |
| `KeyError` | 脚本不存在、状态键缺失 |
| `TypeError` | 参数类型错误 |

### C 错误码

```c
PLCOPEN_OK         // 成功
PLCOPEN_ERR_NULL   // 空指针
PLCOPEN_ERR_PARAM  // 参数错误
PLCOPEN_ERR_RANGE  // 范围错误
PLCOPEN_ERR_NAN    // NaN 输入
PLCOPEN_ERR_INF    // 无穷大输入
PLCOPEN_ERR_MEMORY // 内存错误
```

---

## 使用示例

### 温度 PID 控制

```python
import plcopen

# 创建 PID 控制器
pid = plcopen.PID(
    kp=2.0, ki=0.1, kd=0.5,
    out_min=0.0, out_max=100.0
)

def main():
    setpoint = 60.0
    pv = read_temperature()
    output = pid.execute(setpoint=setpoint, pv=pv)
    set_heater_power(output)
    return {"temp": pv, "power": output}
```

### 信号滤波

```python
import plcopen

# 创建一阶惯性滤波器
filter = plcopen.FirstOrder(k=1.0, t=0.3)

def main():
    raw = read_sensor()
    smooth = filter.execute(raw)
    return smooth
```

### 级联控制

```python
import plcopen

# 外环：温度控制
temp_pid = plcopen.PID(kp=1.0, ki=0.05)

# 内环：流量控制
flow_pid = plcopen.PID(kp=2.0, ki=0.2, out_min=0, out_max=100)

def main():
    temp_setpoint = 80.0
    temp_pv = read_temperature()

    # 外环输出作为内环设定值
    flow_setpoint = temp_pid.execute(temp_setpoint, temp_pv)
    flow_pv = read_flow()

    valve_output = flow_pid.execute(flow_setpoint, flow_pv)
    set_valve(valve_output)
```
