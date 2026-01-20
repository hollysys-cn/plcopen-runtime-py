# PIDA Python API契约

**版本**: 1.0  
**日期**: 2026-01-20  
**文件**: `src/python/py_pida.c`, `plcopen/__init__.py`

## 1. 概述

本文档定义PIDA功能块的Python绑定API规范，遵循现有PLCOpen运行时的Python绑定模式（参考`py_pid.c`）。

## 2. 模块结构

```python
# plcopen/__init__.py
from ._plcopen import PIDA, PIDAMode, PIDAType, PIDAEquation
```

## 3. 类定义

### 3.1 PIDA类

```python
class PIDA:
    """
    带过程值报警的PID控制器功能块。
    
    基于IEC61131-3标准实现，支持五种运行模式、四级过程值报警、
    设定值爬坡、串级控制和控制旁路等工业级控制功能。
    
    示例:
        >>> from plcopen import PIDA
        >>> pida = PIDA(kp=100.0, ti=30.0, cyc=0.5)
        >>> pida.execute(pv=50.0, sp=60.0)
        >>> print(f"输出: {pida.output:.2f}")
    
    属性:
        output (float): 控制输出值（只读）
        sp (float): 当前设定值
        mode (int): 当前运行模式
        hhind (bool): 高高限报警指示（只读）
        ahind (bool): 高限报警指示（只读）
        alind (bool): 低限报警指示（只读）
        llind (bool): 低低限报警指示（只读）
        da (bool): 偏差报警指示（只读）
        ove (int): 输出超限状态（只读）
        error (float): 当前偏差值（只读）
    """
    
    def __init__(
        self,
        # PID参数
        kp: float = 100.0,
        ti: float = 30.0,
        td: float = 0.0,
        kd: float = 1.0,
        # 量程
        pvu: float = 100.0,
        pvl: float = 0.0,
        engu: float = 100.0,
        engl: float = 0.0,
        outu: float = 100.0,
        outl: float = 0.0,
        spu: float = 100.0,
        spl: float = 0.0,
        # 控制选项
        pidtype: int = 0,
        eqn: int = 0,
        octyp: int = 0,
        outopt: bool = False,
        actopt: bool = True,
        # 扫描周期
        cyc: float = 0.5,
        # 报警限值
        hh: float = 100.0,
        ah: float = 90.0,
        al: float = 10.0,
        ll: float = 0.0,
        almdb: float = 2.0,
        dal: float = 30.0,
        # 报警级别
        h2: int = 0,
        h1: int = 0,
        l1: int = 0,
        l2: int = 0,
        dallv: int = 0,
        # 其他选项
        almopt: bool = True,
        **kwargs
    ):
        """
        初始化PIDA功能块实例。
        
        参数:
            kp: 比例带，百分数(%)，默认100
            ti: 积分时间（秒），默认30
            td: 微分时间（秒），默认0
            kd: 微分增益，默认1
            pvu: PV量程上限，默认100
            pvl: PV量程下限，默认0
            engu: 输出量程上限，默认100
            engl: 输出量程下限，默认0
            outu: 输出上限值，默认100
            outl: 输出下限值，默认0
            spu: SP上限值，默认100
            spl: SP下限值，默认0
            pidtype: PID回路类型（0=单回路,1=串级主调,2=串级副调,3=外给定）
            eqn: PID公式（0=标准型,1=微分先行,2=比例微分先行）
            octyp: 输出补偿方式（0=加法,1=乘法）
            outopt: 输出方式（False=位置式,True=增量式）
            actopt: 作用方式（False=正作用,True=反作用）
            cyc: 计算周期（秒），默认0.5
            hh: 报警高高限
            ah: 报警高限
            al: 报警低限
            ll: 报警低低限
            almdb: 限值报警死区(%)
            dal: 偏差报警限(%)
            h2: 高高限报警级（0=禁用）
            h1: 高限报警级（0=禁用）
            l1: 低限报警级（0=禁用）
            l2: 低低限报警级（0=禁用）
            dallv: 偏差报警级（0=禁用）
            almopt: 过程报警开关
            **kwargs: 其他参数（见data-model.md）
        
        异常:
            ValueError: 参数值无效
        """
        ...
```

### 3.2 执行方法

```python
    def execute(
        self,
        pv: float,
        sp: float | None = None,
        mode: int | None = None,
        *,
        incomp: float = 0.0,
        outcomp: float = 0.0,
        trkval: float = 0.0,
        trksw: bool = False,
        auxmode: int = 0,
        auxcomp: float = 0.0,
        auxove: int = 0,
        q: int = 0,
        orsts: int = 0,
        orfb: float = 0.0,
        manmode: int = 0,
        spmode: int = 0,
        rcmd: int = 0,
        rtyp: bool = False,
        rtimesp: float = 0.0,
        rratsp: float = 0.0,
        rsptv: float = 0.0,
        pmsw: bool = False,
        pmout: float = 0.0,
        ctrbp: bool = False,
    ) -> float:
        """
        执行一步PIDA计算。
        
        参数:
            pv: 测量值（过程变量）
            sp: 设定值（None表示保持当前值）
            mode: 运行模式（None表示保持当前模式）
            incomp: 输入补偿
            outcomp: 输出补偿
            trkval: 跟踪点值
            trksw: 跟踪开关
            auxmode: 副调运行方式（串级主调使用）
            auxcomp: 副调补偿值（串级主调使用）
            auxove: 副调超限状态（串级主调使用）
            q: 测量值质量字
            orsts: 超驰反馈状态
            orfb: 超驰反馈值
            manmode: 手动输出模式（1=快增,2=快减,3=慢增,4=慢减）
            spmode: SP变化模式（1=快增,2=快减,3=慢增,4=慢减）
            rcmd: 爬坡命令（0=停止,1=启动）
            rtyp: 爬坡方式（False=时间,True=速率）
            rtimesp: 爬坡时间设定（分钟）
            rratsp: 爬坡速率设定（工程量/分钟）
            rsptv: 爬坡目标值
            pmsw: 手动输出源（False=人工,True=程序）
            pmout: 程控手动输出值
            ctrbp: 控制旁路
        
        返回:
            float: 控制输出值
        
        异常:
            ValueError: 输入值无效（NaN或无穷）
            RuntimeError: 内部计算错误
        
        示例:
            >>> output = pida.execute(pv=50.0, sp=60.0)
            >>> print(f"输出: {output:.2f}")
        """
        ...
```

### 3.3 只读属性

```python
    @property
    def output(self) -> float:
        """控制输出值。"""
        ...
    
    @property
    def error(self) -> float:
        """当前偏差值（SP - PV）。"""
        ...
    
    @property
    def hhind(self) -> bool:
        """高高限报警指示。"""
        ...
    
    @property
    def ahind(self) -> bool:
        """高限报警指示。"""
        ...
    
    @property
    def alind(self) -> bool:
        """低限报警指示。"""
        ...
    
    @property
    def llind(self) -> bool:
        """低低限报警指示。"""
        ...
    
    @property
    def da(self) -> bool:
        """偏差报警指示。"""
        ...
    
    @property
    def am(self) -> int:
        """报警信息字。"""
        ...
    
    @property
    def ove(self) -> int:
        """
        输出超限状态。
        
        位定义:
            bit0: 输出超上限
            bit1: 输出超下限
            bit2: 正作用(1)/反作用(0)
            bit3: 旁路状态
        """
        ...
    
    @property
    def comp(self) -> float:
        """补偿输出（串级时为内给定值）。"""
        ...
    
    @property
    def rtime(self) -> float:
        """爬坡剩余时间（分钟）。"""
        ...
    
    @property
    def rrat(self) -> float:
        """实际爬坡速率。"""
        ...
    
    @property
    def is_ramping(self) -> bool:
        """爬坡是否进行中。"""
        ...
```

### 3.4 可读写属性

```python
    @property
    def sp(self) -> float:
        """当前设定值。"""
        ...
    
    @sp.setter
    def sp(self, value: float):
        """设置设定值（范围限制在[SPL, SPU]）。"""
        ...
    
    @property
    def mode(self) -> int:
        """
        当前运行模式。
        
        值:
            0: 手动
            1: 自动
            2: 串级
            3: 手动跟踪
            4: 自动跟踪
        """
        ...
    
    @mode.setter
    def mode(self, value: int):
        """
        设置运行模式。
        
        异常:
            ValueError: 模式值无效
            RuntimeError: 当前状态不允许切换
        """
        ...
    
    @property
    def bypass(self) -> bool:
        """控制旁路状态。"""
        ...
    
    @bypass.setter
    def bypass(self, value: bool):
        """
        设置控制旁路。
        
        异常:
            RuntimeError: 当前状态不支持旁路
        """
        ...
```

### 3.5 方法

```python
    def reset(self) -> None:
        """
        重置内部状态。
        
        保留参数配置，清除内部状态和输出。
        重置后处于手动模式，输出为0。
        """
        ...
    
    def set_params(self, **kwargs) -> None:
        """
        批量设置参数。
        
        参数:
            **kwargs: 参数名=值 键值对
        
        异常:
            ValueError: 参数名不存在或值无效
        
        示例:
            >>> pida.set_params(kp=150.0, ti=20.0)
        """
        ...
    
    def get_params(self) -> dict:
        """
        获取所有参数。
        
        返回:
            dict: 参数名到值的映射
        """
        ...
    
    def start_ramp(
        self,
        target: float,
        by_rate: bool = False,
        value: float = 1.0
    ) -> None:
        """
        启动设定值爬坡。
        
        参数:
            target: 目标设定值
            by_rate: False=按时间爬坡, True=按速率爬坡
            value: 时间（分钟）或速率（工程量/分钟）
        
        异常:
            RuntimeError: 非自动模式
            ValueError: 参数无效
        
        示例:
            # 时间爬坡：5分钟内从当前SP爬到80
            >>> pida.start_ramp(target=80.0, by_rate=False, value=5.0)
            
            # 速率爬坡：以2单位/分钟的速度爬到80
            >>> pida.start_ramp(target=80.0, by_rate=True, value=2.0)
        """
        ...
    
    def stop_ramp(self) -> None:
        """停止设定值爬坡。"""
        ...
    
    def manual_adjust(self, fast: bool = False, increase: bool = True) -> None:
        """
        手动模式增减输出。
        
        参数:
            fast: True=快速调整, False=慢速调整
            increase: True=增加, False=减少
        
        异常:
            RuntimeError: 非手动模式
        """
        ...
    
    def sp_adjust(self, fast: bool = False, increase: bool = True) -> None:
        """
        调整设定值。
        
        参数:
            fast: True=快速调整, False=慢速调整
            increase: True=增加, False=减少
        """
        ...
    
    def get_state(self) -> dict:
        """
        获取内部状态（用于热重载）。
        
        返回:
            dict: 状态变量映射
        """
        ...
    
    def set_state(self, state: dict) -> None:
        """
        恢复内部状态（用于热重载）。
        
        参数:
            state: 状态变量映射（来自get_state）
        """
        ...
```

## 4. 枚举类型

```python
class PIDAMode:
    """PIDA运行模式常量。"""
    MANUAL = 0        # 手动
    AUTO = 1          # 自动
    CASCADE = 2       # 串级
    MANUAL_TRACK = 3  # 手动跟踪
    AUTO_TRACK = 4    # 自动跟踪

class PIDAType:
    """PID回路类型常量。"""
    SINGLE = 0          # 单回路
    CASCADE_MASTER = 1  # 串级主调
    CASCADE_SLAVE = 2   # 串级副调
    EXTERNAL_SP = 3     # 外给定单回路

class PIDAEquation:
    """PID公式类型常量。"""
    STANDARD = 0          # 标准型
    DERIVATIVE_FIRST = 1  # 微分先行
    PD_FIRST = 2          # 比例微分先行
```

## 5. 异常

```python
# 使用标准Python异常
ValueError   # 参数值无效
TypeError    # 参数类型错误
RuntimeError # 运行时错误（状态不允许操作）
```

## 6. 使用示例

### 6.1 基本使用

```python
from plcopen import PIDA, PIDAMode

# 创建实例
pida = PIDA(
    kp=100.0,
    ti=30.0,
    td=0.0,
    cyc=0.5,
    outu=100.0,
    outl=0.0
)

# 切换到自动模式
pida.mode = PIDAMode.AUTO

# 设置设定值
pida.sp = 50.0

# 执行控制循环
for _ in range(100):
    pv = read_sensor()  # 读取传感器
    output = pida.execute(pv=pv)
    write_output(output)  # 写入执行器
```

### 6.2 报警处理

```python
# 配置报警
pida = PIDA(
    hh=95.0, ah=90.0, al=10.0, ll=5.0,
    h2=1, h1=1, l1=1, l2=1,  # 启用所有报警级别
    almopt=True
)

# 执行后检查报警
pida.execute(pv=92.0, sp=50.0)

if pida.hhind:
    print("高高限报警!")
elif pida.ahind:
    print("高限报警!")
    
if pida.da:
    print("偏差报警!")
```

### 6.3 设定值爬坡

```python
# 时间爬坡：10分钟内从50爬到80
pida.mode = PIDAMode.AUTO
pida.sp = 50.0
pida.start_ramp(target=80.0, by_rate=False, value=10.0)

# 监控爬坡进度
while pida.is_ramping:
    pv = read_sensor()
    pida.execute(pv=pv)
    print(f"SP={pida.sp:.1f}, 剩余时间={pida.rtime:.1f}分钟")
    time.sleep(pida.cyc)
```

### 6.4 串级控制

```python
# 主调
master = PIDA(pidtype=PIDAType.CASCADE_MASTER, ...)

# 副调
slave = PIDA(pidtype=PIDAType.CASCADE_SLAVE, ...)

# 串级运行
master.mode = PIDAMode.AUTO
slave.mode = PIDAMode.CASCADE

while True:
    pv_master = read_master_pv()
    pv_slave = read_slave_pv()
    
    # 主调计算
    master.execute(
        pv=pv_master, 
        auxmode=slave.mode,
        auxcomp=slave.comp,
        auxove=slave.ove
    )
    
    # 副调计算（接收主调输出作为SP）
    slave.execute(
        pv=pv_slave,
        sp=master.comp  # 主调COMP作为副调SP
    )
    
    write_output(slave.output)
```

## 7. 与C API的对应关系

| Python | C |
|--------|---|
| `PIDA.__init__` | `pida_init_with_params` |
| `PIDA.execute` | `pida_execute` |
| `PIDA.reset` | `pida_reset` |
| `PIDA.output` | `pida->output.out` |
| `PIDA.mode` getter | `pida_get_mode` |
| `PIDA.mode` setter | `pida_set_mode` |
| `PIDA.start_ramp` | `pida_start_ramp` |
| `PIDA.stop_ramp` | `pida_stop_ramp` |
| `PIDA.get_state` | `pida_get_state` |
| `PIDA.set_state` | `pida_set_state` |

---

**文档版本**: 1.0  
**最后更新**: 2026-01-20
