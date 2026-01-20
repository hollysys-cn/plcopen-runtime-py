# PIDA功能块快速入门

**版本**: 1.0  
**日期**: 2026-01-20

## 1. 概述

PIDA（带过程值报警的PID控制器）是一个工业级的闭环控制功能块，具备以下核心功能：

- **五种运行模式**: 手动、自动、串级、手动跟踪、自动跟踪
- **四级过程值报警**: 高高限(HH)、高限(AH)、低限(AL)、低低限(LL)
- **偏差报警**: 设定值与测量值偏差过大时触发
- **设定值爬坡**: 按时间或速率平滑改变设定值
- **串级控制**: 支持主调-副调串级回路
- **控制旁路**: 副调回路可旁路

## 2. 安装

```bash
# 安装PLCOpen运行时
pip install plcopen-runtime
```

## 3. 基本使用

### 3.1 创建PIDA实例

```python
from plcopen import PIDA

# 使用默认参数创建
pida = PIDA()

# 使用自定义参数创建
pida = PIDA(
    kp=100.0,      # 比例带 100%
    ti=30.0,       # 积分时间 30秒
    td=0.0,        # 微分时间 0秒
    cyc=0.5,       # 扫描周期 0.5秒
    outu=100.0,    # 输出上限 100%
    outl=0.0       # 输出下限 0%
)
```

### 3.2 手动模式

```python
# 默认为手动模式
pida.execute(pv=50.0)

# 手动设置输出
pida.sp = 50.0  # 先设置设定值

# 手动增减输出
pida.manual_adjust(fast=True, increase=True)   # 快增
pida.manual_adjust(fast=False, increase=False) # 慢减
```

### 3.3 自动模式

```python
from plcopen import PIDAMode

# 切换到自动模式
pida.mode = PIDAMode.AUTO

# 设置设定值
pida.sp = 60.0

# 控制循环
import time
while True:
    pv = read_sensor()  # 读取传感器值
    output = pida.execute(pv=pv)
    write_actuator(output)  # 写入执行器
    time.sleep(0.5)  # 等待一个扫描周期
```

## 4. 报警功能

### 4.1 配置报警

```python
pida = PIDA(
    # 报警限值
    hh=95.0,   # 高高限
    ah=90.0,   # 高限
    al=10.0,   # 低限
    ll=5.0,    # 低低限
    
    # 报警级别（0=禁用，>0=启用）
    h2=1,      # 启用高高限报警
    h1=1,      # 启用高限报警
    l1=1,      # 启用低限报警
    l2=1,      # 启用低低限报警
    
    # 偏差报警
    dal=30.0,  # 偏差报警限 30%
    dallv=1,   # 启用偏差报警
    
    # 报警死区
    almdb=2.0, # 2% 死区
    
    # 总开关
    almopt=True
)
```

### 4.2 检查报警状态

```python
pida.execute(pv=92.0, sp=50.0)

# 检查各级报警
if pida.hhind:
    print("⚠️ 高高限报警!")
if pida.ahind:
    print("⚠️ 高限报警!")
if pida.alind:
    print("⚠️ 低限报警!")
if pida.llind:
    print("⚠️ 低低限报警!")
if pida.da:
    print("⚠️ 偏差报警!")

# 获取报警信息字
am = pida.am
print(f"报警字: 0x{am:04X}")
```

## 5. 设定值爬坡

### 5.1 时间爬坡

```python
# 切换到自动模式
pida.mode = PIDAMode.AUTO
pida.sp = 50.0

# 10分钟内从50爬到80
pida.start_ramp(target=80.0, by_rate=False, value=10.0)

# 监控爬坡进度
while pida.is_ramping:
    pv = read_sensor()
    pida.execute(pv=pv)
    print(f"SP={pida.sp:.1f}, 剩余={pida.rtime:.1f}分钟")
    time.sleep(0.5)

print("爬坡完成!")
```

### 5.2 速率爬坡

```python
# 以2单位/分钟的速度爬坡
pida.start_ramp(target=80.0, by_rate=True, value=2.0)
```

### 5.3 停止爬坡

```python
pida.stop_ramp()
```

## 6. 串级控制

### 6.1 架构说明

```
       ┌─────────┐        ┌─────────┐
SP1 ──▶│  主调   │─COMP──▶│  副调   │──OUT──▶ 执行器
       │ (MASTER)│        │ (SLAVE) │
       └────┬────┘        └────┬────┘
            │                   │
            │                   │
       ◀────┴──── PV1     ◀────┴──── PV2
         (主测量值)         (副测量值)
```

### 6.2 创建串级回路

```python
from plcopen import PIDA, PIDAType, PIDAMode

# 主调
master = PIDA(
    pidtype=PIDAType.CASCADE_MASTER,
    kp=100.0,
    ti=60.0,
    cyc=0.5
)

# 副调
slave = PIDA(
    pidtype=PIDAType.CASCADE_SLAVE,
    kp=50.0,
    ti=10.0,
    cyc=0.5
)

# 设置模式
master.mode = PIDAMode.AUTO
slave.mode = PIDAMode.CASCADE  # 副调设为串级模式

# 串级控制循环
while True:
    pv1 = read_master_pv()
    pv2 = read_slave_pv()
    
    # 先计算主调
    master.execute(
        pv=pv1,
        auxmode=slave.mode,
        auxcomp=slave.comp,
        auxove=slave.ove
    )
    
    # 再计算副调（主调COMP作为副调SP）
    slave.execute(
        pv=pv2,
        sp=master.comp
    )
    
    # 输出副调结果
    write_actuator(slave.output)
    time.sleep(0.5)
```

## 7. 控制旁路

```python
# 仅串级副调支持旁路
slave = PIDA(pidtype=PIDAType.CASCADE_SLAVE)
slave.mode = PIDAMode.CASCADE

# 切入旁路
slave.bypass = True

# 旁路状态下，副调输出由外部控制
# slave.execute() 仍需调用，但输出保持不变

# 退出旁路
slave.bypass = False  # 自动切回手动模式
```

## 8. 热重载支持

```python
# 保存状态
state = pida.get_state()

# ... 程序重启 ...

# 恢复状态
new_pida = PIDA(**old_params)
new_pida.set_state(state)
```

## 9. 常见问题

### 9.1 输出不变化？

检查以下项：
1. 是否在自动模式？`pida.mode == PIDAMode.AUTO`
2. 设定值是否正确？`print(pida.sp)`
3. 是否调用了execute？每个周期需调用一次

### 9.2 报警不触发？

检查以下项：
1. 报警开关是否打开？`almopt=True`
2. 报警级别是否设置？`h1 > 0`, `h2 > 0` 等
3. 报警限值是否合理？

### 9.3 爬坡不工作？

检查以下项：
1. 是否在自动模式？爬坡仅在自动模式生效
2. 目标值是否在[SPL, SPU]范围内？
3. 时间/速率值是否大于0？

## 10. 完整示例

```python
#!/usr/bin/env python3
"""PIDA功能块使用示例"""

import time
from plcopen import PIDA, PIDAMode

def main():
    # 创建PIDA实例
    pida = PIDA(
        kp=100.0,
        ti=30.0,
        cyc=0.5,
        hh=95.0, ah=90.0, al=10.0, ll=5.0,
        h2=1, h1=1, l1=1, l2=1,
        almopt=True
    )
    
    # 初始设定值
    pida.sp = 50.0
    
    # 切换到自动模式
    pida.mode = PIDAMode.AUTO
    
    # 模拟过程变量（一阶惯性环节）
    pv = 30.0
    tau = 10.0  # 时间常数
    
    print("PIDA控制器启动")
    print("-" * 50)
    
    for i in range(100):
        # 模拟过程响应
        output = pida.execute(pv=pv)
        pv = pv + (output - pv) * pida.params.cyc / tau
        
        # 打印状态
        if i % 10 == 0:
            alarm_str = ""
            if pida.ahind: alarm_str += "[AH]"
            if pida.da: alarm_str += "[DA]"
            
            print(f"周期{i:3d}: PV={pv:6.2f} SP={pida.sp:6.2f} "
                  f"OUT={output:6.2f} ERR={pida.error:6.2f} {alarm_str}")
        
        time.sleep(0.5)
    
    print("-" * 50)
    print("PIDA控制器停止")

if __name__ == "__main__":
    main()
```

---

**更多信息**:
- [C API文档](contracts/c-api.md)
- [Python API文档](contracts/python-api.md)
- [数据模型](data-model.md)
- [技术研究](research.md)
