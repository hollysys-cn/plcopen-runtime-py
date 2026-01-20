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

## PIDA 类

带过程值报警的 PID 控制器，基于 IEC61131-3 标准实现。

### 功能特点

- **五种运行模式**：手动、自动、串级、手动跟踪、自动跟踪
- **四级过程值报警**：HH（高高限）、AH（高限）、AL（低限）、LL（低低限）
- **偏差报警**：设定值与过程值偏差过大时报警
- **设定值爬坡**：支持设定值斜坡变化
- **控制旁路**：串级副调可旁路控制
- **三种 PID 公式**：标准型、微分先行、比例微分先行
- **无扰切换**：模式切换时保持输出连续

### 构造函数

```python
plcopen.PIDA(
    kp: float = 100.0,    # 比例带（%）
    ti: float = 30.0,     # 积分时间（秒）
    td: float = 0.0,      # 微分时间（秒）
    kd: float = 1.0,      # 微分增益
    pvu: float = 100.0,   # PV量程上限
    pvl: float = 0.0,     # PV量程下限
    engu: float = 100.0,  # 输出量程上限
    engl: float = 0.0,    # 输出量程下限
    outu: float = 100.0,  # 输出上限
    outl: float = 0.0,    # 输出下限
    spu: float = 100.0,   # 设定值上限
    spl: float = 0.0,     # 设定值下限
    pidtype: int = 0,     # PID类型
    eqn: int = 0,         # PID公式
    outopt: int = 0,      # 输出方式（0=位置式，1=增量式）
    actopt: int = 1,      # 作用方式（0=正作用，1=反作用）
    cyc: float = 0.5,     # 计算周期（秒）
)
```

**参数说明：**

| 参数 | 类型 | 范围 | 说明 |
|------|------|------|------|
| kp | float | > 0 | 比例带宽度（%），值越大增益越小 |
| ti | float | ≥ 0 | 积分时间，0 禁用积分 |
| td | float | ≥ 0 | 微分时间，0 禁用微分 |
| kd | float | 0.1-10 | 微分增益，调节微分器响应 |
| pvu/pvl | float | - | 过程值量程范围 |
| engu/engl | float | - | 输出工程单位范围 |
| outu/outl | float | - | 输出限幅范围 |
| spu/spl | float | - | 设定值限幅范围 |
| pidtype | int | 0-3 | PID 类型（见常量定义） |
| eqn | int | 0-2 | PID 公式（见常量定义） |
| outopt | int | 0-1 | 0=位置式，1=增量式 |
| actopt | int | 0-1 | 0=正作用，1=反作用 |
| cyc | float | > 0 | 计算周期（秒） |

**异常：**
- `ValueError`: 参数无效

**示例：**

```python
# 温度控制 PIDA
pida = plcopen.PIDA(
    kp=100.0,      # 比例带 100%
    ti=30.0,       # 积分时间 30秒
    td=5.0,        # 微分时间 5秒
    pvu=100.0,     # 温度上限 100°C
    pvl=0.0,       # 温度下限 0°C
    outu=100.0,    # 输出上限 100%
    outl=0.0,      # 输出下限 0%
    actopt=1,      # 反作用（温度低时加热）
    cyc=0.5,       # 500ms 周期
)
```

### execute 方法

执行一步 PID 计算。

```python
def execute(
    self,
    pv: float,              # 过程值（必需）
    mout: float = 0.0,      # 手动输出设定
    sp: float = None,       # 设定值（可选）
    mode: int = None,       # 模式（可选）
    auxcomp: float = 0.0,   # 辅助输入（串级用）
    track: float = 0.0,     # 跟踪输入
    **kwargs
) -> float
```

**参数：**
- `pv`: 过程值（当前测量值）
- `mout`: 手动模式下的输出设定值
- `sp`: 设定值，None 使用当前 SP
- `mode`: 运行模式，None 使用当前模式
- `auxcomp`: 串级输入（主调输出或外给定）
- `track`: 跟踪模式下的输出跟踪值

**返回：**
- `float`: 控制输出值

**异常：**
- `ValueError`: 输入为 NaN 或无穷大

**示例：**

```python
# 手动模式
pida.mode = plcopen.PIDA_MODE_MANUAL
output = pida.execute(pv=45.0, mout=50.0)

# 自动模式
pida.mode = plcopen.PIDA_MODE_AUTO
pida.sp = 60.0
output = pida.execute(pv=45.0)
```

### reset 方法

重置控制器状态。

```python
def reset(self) -> None
```

清除积分器、历史值，恢复到初始状态。

### start_ramp 方法

启动设定值爬坡。

```python
def start_ramp(self, target: float, time_or_rate: float, rtyp: bool = True) -> None
```

**参数：**
- `target`: 目标设定值
- `time_or_rate`: 爬坡时间（分钟）或速率（单位/秒）
- `rtyp`: True=速率方式，False=时间方式

**示例：**

```python
# 速率方式：以 5%/秒 的速度爬到 70%
pida.start_ramp(target=70.0, time_or_rate=5.0, rtyp=True)

# 时间方式：10分钟内爬到 80%
pida.start_ramp(target=80.0, time_or_rate=10.0, rtyp=False)
```

### stop_ramp 方法

停止设定值爬坡。

```python
def stop_ramp(self) -> None
```

### get_state 方法

获取控制器状态（用于热重载）。

```python
def get_state(self) -> dict
```

**返回：**
```python
{
    "sp": float,          # 当前设定值
    "mode": int,          # 当前模式
    "output": float,      # 当前输出
    "error": float,       # 当前偏差
    "integral": float,    # 积分累积值
    "hhind": bool,        # 高高限报警
    "ahind": bool,        # 高限报警
    "alind": bool,        # 低限报警
    "llind": bool,        # 低低限报警
}
```

### set_state 方法

恢复控制器状态（用于热重载）。

```python
def set_state(self, state: dict) -> None
```

### 属性

| 属性 | 类型 | 读/写 | 说明 |
|------|------|-------|------|
| sp | float | R/W | 设定值 |
| mode | int | R/W | 运行模式 |
| output / out | float | R | 控制输出 |
| error / ek | float | R | 当前偏差 |
| hhind | bool | R | 高高限报警指示 |
| ahind | bool | R | 高限报警指示 |
| alind | bool | R | 低限报警指示 |
| llind | bool | R | 低低限报警指示 |
| da | bool | R | 偏差报警指示 |
| am | int | R | 报警信息字（8位） |
| ove | int | R | 输出超限状态 |
| bypass | bool | R/W | 旁路状态 |

### 常量定义

**运行模式：**
```python
plcopen.PIDA_MODE_MANUAL       # 0: 手动模式
plcopen.PIDA_MODE_AUTO         # 1: 自动模式
plcopen.PIDA_MODE_CASCADE      # 2: 串级模式
plcopen.PIDA_MODE_MANUAL_TRACK # 3: 手动跟踪模式
plcopen.PIDA_MODE_AUTO_TRACK   # 4: 自动跟踪模式
```

**PID 类型：**
```python
plcopen.PIDA_TYPE_SINGLE         # 0: 单回路
plcopen.PIDA_TYPE_CASCADE_MASTER # 1: 串级主调
plcopen.PIDA_TYPE_CASCADE_SLAVE  # 2: 串级副调
plcopen.PIDA_TYPE_EXTERNAL_SP    # 3: 外给定
```

**PID 公式：**
```python
plcopen.PIDA_EQN_STANDARD         # 0: 标准型
plcopen.PIDA_EQN_DERIVATIVE_FIRST # 1: 微分先行
plcopen.PIDA_EQN_PD_FIRST         # 2: 比例微分先行
```

### 报警信息字 (AM) 位定义

| 位 | 说明 |
|----|------|
| bit0 | LL 低低限报警 |
| bit1 | AL 低限报警 |
| bit2 | AH 高限报警 |
| bit3 | HH 高高限报警 |
| bit4 | 输出下限报警 |
| bit5 | 输出上限报警 |
| bit6 | 保留 |
| bit7 | DA 偏差报警 |

### 使用示例

**温度控制：**

```python
import plcopen

pida = plcopen.PIDA(
    kp=100.0, ti=30.0, td=5.0,
    pvu=100.0, pvl=0.0,
    outu=100.0, outl=0.0,
    actopt=1,
)

# 设置自动模式
pida.sp = 60.0
pida.mode = plcopen.PIDA_MODE_AUTO

# 控制循环
while running:
    temp = read_temperature()
    power = pida.execute(pv=temp)
    set_heater_power(power)
    
    # 检查报警
    if pida.hhind:
        trigger_high_alarm()
    time.sleep(0.5)
```

**手动/自动切换：**

```python
# 无扰切换：先将 SP 设为当前 PV
pida.sp = current_pv
pida.mode = plcopen.PIDA_MODE_AUTO
```

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
