# Feature Specification: PIDA功能块 - 带过程值报警的PID控制器

**Feature Branch**: `002-pida-function-block`  
**Created**: 2026-01-20  
**Status**: Draft  
**Input**: User description: "为PLCOpen运行时添加PIDA功能块，这是一个带过程值报警的PID控制器算法块"

## Overview

PIDA（PID with Alarm）功能块是一个工业级PID控制器，在标准PID功能的基础上增加了过程值报警处理功能。该功能块源自IEC61131-3标准，已有成熟的ST语言实现（PIDA.xml）和对应的C语言转换代码（H_PIDA.c/h），需要按照本项目的PLCOpen运行时架构进行重新封装和集成。

## Implementation Constraints *(mandatory)*

### 算法实现约束

- **IC-001**: PIDA算法块的实现**必须**完整按照 `IEC61131-1/PIDA/PIDA.xml` 中的ST语言组态逻辑实现，不得简化或省略任何功能分支
- **IC-002**: 所有算法逻辑（报警处理、模式切换、爬坡功能、PID计算、输出限幅等）必须与ST源码保持一致
- **IC-003**: 参数边界检查和自动修正逻辑必须与ST源码完全一致

### 接口约束

- **IC-004**: PIDA功能块对外暴露的接口**必须**与 `PIDA.xml` 中的变量声明（VarsData）完全一致
- **IC-005**: 所有INPUT、OUTPUT、INOUT、TEMP类型的变量必须按照原定义提供
- **IC-006**: 变量名称、数据类型、默认值必须与ST源码定义一致

### 示例脚本约束

- **IC-007**: 必须提供Python调用示例脚本，参照现有 `scripts/demo.py` 的编写方式
- **IC-008**: 示例脚本需要演示PIDA的核心功能：创建实例、配置参数、模式切换、报警监控

## User Scenarios & Testing *(mandatory)*

### User Story 1 - 使用PIDA进行带报警的PID控制 (Priority: P1)

作为一名控制系统工程师，我需要使用PIDA功能块实现带过程值报警功能的PID控制，以便在一个功能块中同时完成闭环控制和过程监控。

**Why this priority**: PIDA是工业控制中常用的高级PID功能块，集成了报警功能可以减少工程配置工作量，是控制系统的核心需求。

**Independent Test**: 可以通过Python脚本创建PIDA实例，配置PID参数和报警限值，验证控制输出正确且报警功能正常触发。

**Acceptance Scenarios**:

1. **Given** 运行时环境已启动且PIDA功能块可用，**When** Python脚本创建PIDA实例并设置KP=100（比例带）、TI=30（积分时间）、KD=1（微分增益），**Then** PIDA实例成功创建并返回有效句柄
2. **Given** PIDA实例已创建并设置报警高限AH=90、报警低限AL=10，**When** 过程值PV超过报警高限，**Then** 高限报警标志AHIND被设置且报警信息AM相应位被置位
3. **Given** PIDA实例在自动模式运行，**When** 脚本调用执行方法传入设定值SP=50和过程值PV=40，**Then** 返回合理的控制输出值OUT

---

### User Story 2 - 支持多种运行模式切换 (Priority: P1)

作为一名控制系统工程师，我需要PIDA支持手动、自动、串级等多种运行模式，并能够在运行时平滑切换，以满足不同的控制场景需求。

**Why this priority**: 多模式切换是工业PID控制器的标准功能，直接影响控制系统的可操作性和安全性。

**Independent Test**: 可以在Python脚本中切换PIDA运行模式，验证模式切换无扰动且各模式功能正确。

**Acceptance Scenarios**:

1. **Given** PIDA实例处于手动模式(MODE=0)，**When** 操作员通过脚本将MODE设置为1（自动），**Then** PIDA无扰切换到自动模式，输出平滑过渡
2. **Given** PIDA作为串级副调(PIDTYPE=2)运行在串级模式(MODE=2)，**When** 主调输出变化，**Then** 副调设定值跟随主调输出变化
3. **Given** PIDA处于跟踪模式(MODE=3或4)，**When** 跟踪开关TRKSW关闭且TRKMODE=1，**Then** PIDA回到跟踪前的工作状态

---

### User Story 3 - 支持设定值爬坡功能 (Priority: P2)

作为一名控制系统工程师，我需要PIDA支持设定值爬坡功能，以便实现平稳的设定值变化，避免过程扰动。

**Why this priority**: 设定值爬坡是工业控制中常用的平滑过渡功能，可以有效减少工艺扰动。

**Independent Test**: 可以设置爬坡参数并启动爬坡命令，验证设定值按照设定的速率或时间逐步变化。

**Acceptance Scenarios**:

1. **Given** PIDA实例处于自动模式，**When** 设置爬坡目标值RSPTV=80、爬坡时间RTIMESP=10分钟，并启动爬坡命令RCMD=1，**Then** 设定值SP以恒定速率向目标值爬升
2. **Given** 爬坡过程正在进行，**When** 设置RCMD=0停止爬坡，**Then** 设定值停止在当前值
3. **Given** 使用速率爬坡方式(RTYP=1)，**When** 设置爬坡速率RRATSP=5（工程量/分钟），**Then** 设定值按照设定速率变化

---

### User Story 4 - 支持四级过程值报警 (Priority: P2)

作为一名控制系统工程师，我需要PIDA支持高高限(HH)、高限(AH)、低限(AL)、低低限(LL)四级报警，以满足工艺安全监控需求。

**Why this priority**: 四级报警是工业过程控制的标准配置，对工艺安全至关重要。

**Independent Test**: 可以配置各级报警限值和报警级别，验证过程值越限时正确触发相应级别的报警。

**Acceptance Scenarios**:

1. **Given** PIDA实例已配置报警限值HH=95、AH=90、AL=10、LL=5，**When** 过程值PV从50逐渐上升超过95，**Then** 依次触发AHIND和HHIND报警
2. **Given** 报警抑制功能已启用(如INHH1=TRUE)，**When** 过程值超过对应报警限，**Then** 该级别报警被抑制不触发
3. **Given** 报警死区ALMDB=2%，**When** 过程值在报警限值附近波动，**Then** 报警状态不会频繁切换

---

### User Story 5 - 支持偏差报警 (Priority: P2)

作为一名控制系统工程师，我需要PIDA支持偏差报警功能，当设定值与过程值偏差过大时能够发出警报。

**Why this priority**: 偏差报警能够及时发现控制异常，是控制质量监控的重要手段。

**Independent Test**: 可以配置偏差报警限值，验证偏差超限时触发报警。

**Acceptance Scenarios**:

1. **Given** PIDA实例已配置偏差报警限DAL=30%，**When** 设定值SP与过程值PV的偏差超过30%量程，**Then** 偏差报警标志DA被设置
2. **Given** 偏差报警抑制已启用(INHDAL=TRUE)，**When** 偏差超限，**Then** 偏差报警不触发
3. **Given** 偏差报警级DALLV=0，**When** 偏差超限，**Then** 偏差报警不触发（级别为0表示禁用）

---

### User Story 6 - 支持控制旁路功能 (Priority: P3)

作为一名控制系统工程师，我需要PIDA（作为串级副调时）支持控制旁路功能，以便在必要时直接将主调输出传递到执行机构。

**Why this priority**: 控制旁路是串级控制系统中重要的应急功能，可以在副调故障时维持控制。

**Independent Test**: 可以在串级副调模式下启用旁路，验证主调输出直接传递到副调输出。

**Acceptance Scenarios**:

1. **Given** PIDA作为串级副调(PIDTYPE=2)运行，**When** 设置CTRBP=1启用旁路，**Then** 控制计算被旁路，输出直接跟随AUXCOMP
2. **Given** 旁路模式已启用，**When** 设置CTRBP=0退出旁路，**Then** PIDA切换到手动模式并平滑过渡

---

### User Story 7 - 报警切手动功能 (Priority: P3)

作为一名控制系统工程师，我需要PIDA在发生报警或测量通道故障时自动切换到手动模式，以防止控制系统失控。

**Why this priority**: 报警切手动是工业安全控制的重要保护机制，可在异常情况下保护设备安全。

**Independent Test**: 可以配置报警切手动掩码MANCUT，触发报警后验证PIDA自动切换到手动模式。

**Acceptance Scenarios**:

1. **Given** PIDA实例处于自动模式且MANCUT位掩码已配置，**When** 发生相应级别的报警，**Then** PIDA自动切换到手动模式
2. **Given** PIDA实例处于自动模式，**When** 测量通道质量字Q指示故障，**Then** PIDA自动切换到手动模式
3. **Given** 报警切手动已触发，**When** 报警恢复正常，**Then** PIDA保持手动模式，需操作员手动切换回自动

---

### Edge Cases

- 当PVU≤PVL（过程值量程上下限配置错误）时，系统自动修正为默认值PVU=100、PVL=0
- 当KP≤0（比例带配置无效）时，系统自动修正为默认值KP=100
- 当OUTU≤OUTL（输出上下限配置错误）时，系统自动修正为默认值OUTU=100、OUTL=0
- 当TI<0（积分时间为负）时，系统自动修正为TI=0（纯比例控制）
- 当模式值MODE>4（无效模式）时，系统自动回退到当前实际运行模式nowRM

## Requirements *(mandatory)*

### Functional Requirements

- **FR-001**: 系统必须提供PIDA功能块，实现带过程值报警的PID控制算法
- **FR-002**: PIDA必须支持五种运行模式：手动(0)、自动(1)、串级(2)、手动跟踪(3)、自动跟踪(4)
- **FR-003**: PIDA必须支持四种PID回路类型：单回路(0)、串级主调(1)、串级副调(2)、单回路外给定(3)
- **FR-004**: PIDA必须支持位置式和增量式两种输出方式(OUTOPT)
- **FR-005**: PIDA必须支持正作用和反作用两种控制方式(ACTOPT)
- **FR-006**: PIDA必须支持四级过程值报警（高高限HH、高限AH、低限AL、低低限LL）
- **FR-007**: PIDA必须支持偏差报警功能(DA)
- **FR-008**: PIDA必须支持各级报警的独立抑制功能(INHH2、INHH1、INHL1、INHL2、INHDAL)
- **FR-009**: PIDA必须支持报警死区功能(ALMDB)，防止报警状态频繁切换
- **FR-010**: PIDA必须支持设定值爬坡功能，支持时间方式和速率方式两种爬坡模式(RTYP)
- **FR-011**: PIDA必须支持手动输出快速/慢速增减功能(MANMODE)
- **FR-012**: PIDA必须支持设定值快速/慢速增减功能(SPMODE)
- **FR-013**: PIDA必须支持输出限幅功能(OUTU、OUTL)
- **FR-014**: PIDA必须支持输入补偿(INCOMP)和输出补偿(OUTCOMP)功能
- **FR-015**: PIDA作为串级副调时必须支持控制旁路功能(CTRBP)
- **FR-016**: PIDA必须支持积分分离功能(INTEDB)，防止积分饱和
- **FR-017**: PIDA必须支持输入死区功能(DVDB)，减少不必要的控制动作
- **FR-018**: PIDA必须提供Python接口，可在Python脚本中创建和操作PIDA实例
- **FR-019**: PIDA必须与现有PID功能块保持一致的API设计风格，包括：函数命名规范（pida_前缀）、参数顺序（instance指针在前）、返回值约定（0成功/-1失败）、Python属性命名（小写下划线风格）
- **FR-020**: PIDA必须支持运行周期自动获取(CYC)，默认值为0.5秒
- **FR-021**: PIDA必须支持报警切手动功能，当报警触发或测量通道故障时可根据MANCUT位掩码配置自动切换到手动模式

### Key Entities

以下接口定义**必须**与 `PIDA.xml` 中的 VarsData 完全一致：

#### INPUT 变量（输入）

| 变量名 | 类型 | 默认值 | 描述 |
|--------|------|--------|------|
| PV | REAL | 0 | 测量值（过程值） |
| INCOMP | REAL | 0 | 输入补偿 |
| OUTCOMP | REAL | 0 | 输出补偿 |
| TRKVAL | REAL | 0 | 跟踪点值 |
| TRKSW | BOOL | FALSE | 跟踪开关：0-不跟踪，1-跟踪 |
| PIDTYPE | UINT | 0 | PID回路类型：0-单回路，1-串级主调，2-串级副调，3-单回路外给定 |
| AUXMODE | UINT | 0 | 副调运行方式 |
| AUXCOMP | REAL | 0 | 副调PV-INCOMP |
| AUXOVE | BYTE | 0 | 副调节器输出是否超限 |
| TD | REAL | 0 | 微分时间 |
| Q | WORD | 0 | 测量值质量 |
| ALMOPT | BOOL | TRUE | 过程报警开关：0-关，1-开 |
| ORSTS | BYTE | 0 | 超驰反馈输入状态 |
| ORFB | REAL | 0 | 超驰反馈输入值 |
| LOCK | BOOL | FALSE | 是否锁定操作面板 |
| DEV_OWNER | STRING | "" | 占用ID |

#### OUTPUT 变量（输出）

| 变量名 | 类型 | 默认值 | 描述 |
|--------|------|--------|------|
| OUT | REAL | 0 | 输出值 |

#### INOUT 变量（输入/输出）

| 变量名 | 类型 | 默认值 | 描述 |
|--------|------|--------|------|
| SP | REAL | 0 | 设定值 |
| CYC | REAL | 0.5 | 计算周期（秒） |
| MODE | UINT | 0 | 运行模式：0-手动，1-自动，2-串级，3-手动跟踪，4-自动跟踪 |
| KP | REAL | 100 | 比例带，百分数(%) |
| TI | REAL | 30 | 积分时间 |
| KD | REAL | 1 | 微分增益 |
| OUTU | REAL | 100 | 输出上限值 |
| OUTL | REAL | 0 | 输出下限值 |
| RTIMESP | REAL | 0 | 爬坡时间设定（分钟） |
| RRATSP | REAL | 0 | 爬坡速率设定（工程量/分钟） |
| RCMD | BYTE | 0 | 爬坡命令：0=停止，1=启动 |
| RSPTV | REAL | 0 | 爬坡目标值 |
| PMSW | BOOL | FALSE | 手动输出源：0=人工操作，1=程序控制 |
| PMOUT | REAL | 0 | 手动模式下的输出值 |

#### TEMP 变量（内部/配置）- 关键参数

| 变量名 | 类型 | 默认值 | 描述 |
|--------|------|--------|------|
| ENGU | REAL | 100 | 输出量程上限 |
| ENGL | REAL | 0 | 输出量程下限 |
| PVU | REAL | 100 | PV量程上限 |
| PVL | REAL | 0 | PV量程下限 |
| INTEDB | REAL | 100 | 积分分离值/反向限(%) |
| DAL | REAL | 30 | 偏差报警限，百分数(%) |
| DVDB | REAL | 0.2 | 输入死区/全开关限 |
| OUTRAT | REAL | 5 | 输出变化率（%/s） |
| GIVERAT | REAL | 10 | SP变化率（%/s） |
| MANF | REAL | 1.5 | 手动输出快速变化率 |
| MANS | REAL | 0.5 | 手动输出慢速变化率 |
| SPFRAT | REAL | 5 | SP快速变化率 |
| SPSRAT | REAL | 1 | SP慢速变化率 |
| L2 | BYTE | 0 | 低低限报警级 |
| L1 | BYTE | 0 | 低限报警级 |
| H1 | BYTE | 0 | 高限报警级 |
| H2 | BYTE | 0 | 高高限报警级 |
| LL | REAL | 0 | 报警低低限 |
| AL | REAL | 0 | 报警低限 |
| AH | REAL | 0 | 报警高限 |
| HH | REAL | 0 | 报警高高限 |
| ALMDB | REAL | 2 | 限值报警死区 |
| INHH2 | BOOL | FALSE | 高高限报警抑制 |
| INHH1 | BOOL | FALSE | 高限报警抑制 |
| INHL1 | BOOL | FALSE | 低限报警抑制 |
| INHL2 | BOOL | FALSE | 低低限报警抑制 |
| DALLV | BYTE | 0 | 偏差报警级 |
| INHDAL | BOOL | FALSE | 偏差报警抑制 |
| OUTOPT | BOOL | FALSE | 输出方式：0-位置式，1-增量式 |
| ACTOPT | BOOL | TRUE | 作用方式：0-正作用，1-反作用 |
| TRKOPT | BOOL | TRUE | SP跟踪PV开关 |
| MANMODE | BYTE | 0 | 手动输出模式：1-快增，2-快减，3-慢增，4-慢减 |
| TRKEN | BOOL | TRUE | 跟踪允许开关 |
| MANCUT | WORD | 1920 | 测量值报警是否切手动（按位设置） |
| PK | BYTE | 0 | PID类型：0-普通，1-智能 |
| OMANOPT | BOOL | FALSE | 手动输出单步变化方式：0-百分比，1-工程量 |
| SPMODE | BYTE | 0 | SP变化方式：1-快增，2-快减，3-慢增，4-慢减 |
| SMANOPT | BOOL | FALSE | SP单步变化方式：0-百分比，1-工程量 |
| INTERSP | REAL | 0 | 内给定值 |
| TRKMODE | BOOL | FALSE | 退出跟踪后模式选择 |
| CTRBP | BOOL | FALSE | 控制旁路：0=投用，1=旁路 |
| SPU | REAL | 100 | SP上限值 |
| SPL | REAL | 0 | SP下限值 |
| MOLSW | BOOL | TRUE | 手动输出是否限幅 |
| EQN | BYTE | 0 | PID公式：0=标准型，1=微分先行，2=比例微分先行 |
| OCTYP | BYTE | 0 | 输出补偿方式：0=加法，1=乘法 |
| RTYP | BOOL | FALSE | 爬坡方式：0=时间方式，1=速率方式 |
| SATDB | REAL | 0 | 饱和区间(OUTU/OUTL的百分比) |
| ROVEP | BOOL | FALSE | 输出超限时是否暂停爬坡 |
| LMBLS | BOOL | FALSE | 输出限幅无扰开关 |
| SIMU | BOOL | FALSE | 仿真模式 |

#### TEMP 变量（内部状态）- 只读

| 变量名 | 类型 | 描述 |
|--------|------|------|
| AM | WORD | 测量值报警信息（按位表示） |
| HHIND | BOOL | 高高限报警指示 |
| AHIND | BOOL | 高限报警指示 |
| ALIND | BOOL | 低限报警指示 |
| LLIND | BOOL | 低低限报警指示 |
| DA | BOOL | 偏差报警状态 |
| OVE | BYTE | 输出超限状态（按位表示） |
| COMP | REAL | 过程输入值补偿（副调专用） |
| DK | REAL | 本周期微分计算值 |
| D1 | REAL | 上周期微分计算值 |
| U1 | REAL | 上一周期的位置输出 |
| I1 | REAL | 上一周期的增量输出 |
| EK | REAL | 本周期偏差值 |
| EK_1 | REAL | 上周期偏差值 |
| EK_2 | REAL | 上两周期偏差值 |
| RRAT | REAL | 爬坡实际速率 |
| RTIME | REAL | 爬坡完成倒计时 |
| nowRM | UINT | 当前实际运行模式 |
| SPCAL | REAL | 滤波后设定值 |

## Success Criteria *(mandatory)*

### Measurable Outcomes

- **SC-001**: PIDA功能块能够在自动模式下稳定运行，控制输出符合PID算法预期
- **SC-002**: 模式切换（手动↔自动↔串级）实现无扰切换，输出波动在1%量程以内
- **SC-003**: 报警功能在过程值越限后1个计算周期内触发
- **SC-004**: 设定值爬坡功能实现平滑过渡，实际爬坡速率与设定速率偏差在5%以内
- **SC-005**: PIDA功能块单次执行时间满足实时性要求，单次执行<100μs（X86平台）
- **SC-006**: Python接口易用性达到与现有PID功能块相同的水平
- **SC-007**: 所有参数边界条件处理正确，无异常或崩溃
- **SC-008**: 单元测试覆盖所有核心功能，覆盖率达到80%以上

## Assumptions

- 现有的PLCOpen运行时架构和构建系统可以直接复用
- 提供的ST语言源码（PIDA.xml）中的算法逻辑**必须完整实现**，不得简化
- 提供的C语言转换代码（H_PIDA.c/h）可作为C语言实现参考
- PIDA功能块将遵循现有PID功能块的代码结构和命名规范
- PIDA所依赖的辅助函数（如AI_ALM、B_GET、B_WRITE、GetIECInterval等）需要一并实现或适配
- Python接口将复用现有的Python绑定机制

## Deliverables *(mandatory)*

### 必须交付的文件

1. **C语言实现**
   - `include/plcopen/fb_pida.h` - PIDA功能块头文件
   - `src/fb/pida.c` - PIDA功能块实现
   - `src/common/` - 辅助函数（AI_ALM、B_GET、B_WRITE等）

2. **Python绑定**
   - `src/python/py_pida.c` - PIDA Python绑定实现

3. **测试文件**
   - `tests/unit/c/test_pida.c` - C语言单元测试
   - `tests/unit/python/test_pida.py` - Python单元测试

4. **示例脚本**
   - `scripts/demo_pida.py` - PIDA功能块调用示例脚本
     - 演示单回路PID控制
     - 演示手动/自动模式切换
     - 演示四级报警功能
     - 演示设定值爬坡功能

### 示例脚本参考结构

```python
# scripts/demo_pida.py 预期结构
"""
PIDA带报警PID控制示例脚本

演示如何使用 PLCOpen PIDA 功能块进行带报警的PID控制。
"""

try:
    import plcopen
    PIDA = plcopen.PIDA
except ImportError:
    # 模拟 PIDA 实现（用于测试）
    class PIDA:
        def __init__(self, **kwargs):
            # 初始化所有参数
            self.kp = kwargs.get('kp', 100)  # 比例带
            self.ti = kwargs.get('ti', 30)   # 积分时间
            self.kd = kwargs.get('kd', 1)    # 微分增益
            # ... 其他参数
            
        def execute(self, pv, sp=None):
            # 执行PIDA算法
            pass
            
        @property
        def out(self):
            # 获取输出值
            pass
            
        @property  
        def mode(self):
            # 获取/设置运行模式
            pass
            
        def get_alarms(self):
            # 获取报警状态
            return {
                'hhind': self._hhind,
                'ahind': self._ahind,
                'alind': self._alind,
                'llind': self._llind,
                'da': self._da,
                'am': self._am
            }

# 使用示例
if __name__ == '__main__':
    # 1. 创建PIDA实例
    pida = PIDA(
        kp=100,      # 比例带 100%
        ti=30,       # 积分时间 30s
        kd=1,        # 微分增益
        pvu=100,     # PV量程上限
        pvl=0,       # PV量程下限
        outu=100,    # 输出上限
        outl=0,      # 输出下限
        hh=95,       # 高高限报警
        ah=90,       # 高限报警
        al=10,       # 低限报警
        ll=5,        # 低低限报警
        h2=1,        # 高高限报警级别
        h1=1,        # 高限报警级别
        l1=1,        # 低限报警级别
        l2=1         # 低低限报警级别
    )
    
    # 2. 设置自动模式
    pida.mode = 1  # 自动模式
    
    # 3. 执行控制循环
    setpoint = 50
    for i in range(100):
        pv = get_process_value()  # 获取过程值
        pida.execute(pv, setpoint)
        
        # 检查报警
        alarms = pida.get_alarms()
        if alarms['ahind']:
            print(f"高限报警! PV={pv}")
            
        # 输出控制量
        output = pida.out
        set_actuator(output)
```

## Technical Reference (Implementation Guidance)

以下信息供实现阶段参考，不属于功能规范范围：

- 参考实现：IEC61131-1/PIDA 目录包含原始ST语言和C语言实现
- 现有功能块实现：可参考 src/fb/pid.c 和 include/plcopen/fb_pid.h
