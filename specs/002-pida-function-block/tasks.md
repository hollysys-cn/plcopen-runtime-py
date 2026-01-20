# Tasks: PIDA功能块 - 带过程值报警的PID控制器

**Input**: Design documents from `/specs/002-pida-function-block/`
**Prerequisites**: plan.md ✓, spec.md ✓, research.md ✓, data-model.md ✓, contracts/ ✓, quickstart.md ✓

**Tests**: 本项目需要测试任务，spec.md 明确要求单元测试覆盖率达到80%以上（SC-008）。

**Organization**: 任务按用户故事组织，支持独立实现和测试。

## Format: `[ID] [P?] [Story?] Description`

- **[P]**: 可并行执行（不同文件，无依赖）
- **[Story]**: 所属用户故事（US1, US2, US3...）
- 描述中包含确切的文件路径

## Path Conventions

本项目使用 Single Project 结构：
- C头文件: `include/plcopen/`
- C实现: `src/fb/`
- Python绑定: `src/python/`
- C测试: `tests/unit/c/`
- Python测试: `tests/unit/python/`
- 示例脚本: `scripts/`

---

## Phase 1: Setup (项目初始化)

**Purpose**: 创建PIDA功能块的基础文件结构

- [ ] T001 创建 include/plcopen/fb_pida.h 头文件骨架，包含预处理保护和基本包含
- [ ] T002 [P] 创建 src/fb/pida.c 实现文件骨架，包含头文件引用
- [ ] T003 [P] 更新 CMakeLists.txt 添加 pida.c 到编译目标
- [ ] T004 [P] 创建 src/python/py_pida.c Python绑定文件骨架

---

## Phase 2: Foundational (基础设施 - 阻塞性前置任务)

**Purpose**: 所有用户故事依赖的核心基础设施

**⚠️ CRITICAL**: 用户故事实现必须等待本阶段完成

- [ ] T005 [P] 在 include/plcopen/fb_pida.h 中定义 pida_params_t 结构体（配置参数，参见 data-model.md）
- [ ] T006 [P] 在 include/plcopen/fb_pida.h 中定义 pida_input_t 结构体（运行时输入，参见 data-model.md）
- [ ] T007 [P] 在 include/plcopen/fb_pida.h 中定义 pida_state_t 结构体（内部状态，参见 data-model.md）
- [ ] T008 [P] 在 include/plcopen/fb_pida.h 中定义 pida_output_t 结构体（输出结果，参见 data-model.md）
- [ ] T009 [P] 在 include/plcopen/fb_pida.h 中定义 pida_instance_t 容器结构体
- [ ] T010 [P] 在 include/plcopen/fb_pida.h 中定义枚举类型（pida_mode_t, pida_type_t, pida_eqn_t）
- [ ] T011 [P] 在 include/plcopen/fb_pida.h 中定义位操作宏（PIDA_B_GET, PIDA_B_WRITE, PIDA_OVE_*, PIDA_AM_*）
- [ ] T012 在 src/fb/pida.c 中实现 pida_default_params() 函数
- [ ] T013 在 src/fb/pida.c 中实现 pida_validate_params() 函数
- [ ] T014 在 src/fb/pida.c 中实现 pida_init() 和 pida_init_with_params() 函数
- [ ] T015 在 src/fb/pida.c 中实现 pida_reset() 函数
- [ ] T016 在 src/fb/pida.c 中实现 pida_get_output() 函数
- [ ] T017 在 src/fb/pida.c 中实现 pida_get_state() 和 pida_set_state() 函数

**Checkpoint**: 基础设施完成 - 用户故事实现可以开始

---

## Phase 3: User Story 1 - 带报警的PID控制 (Priority: P1) 🎯 MVP

**Goal**: 实现核心PID控制算法，支持手动和自动模式

**Independent Test**: Python脚本创建PIDA实例，配置PID参数，验证自动模式下控制输出正确

### Tests for User Story 1

- [ ] T018 [P] [US1] 创建 tests/unit/c/test_pida.c 测试框架，添加参数验证测试用例
- [ ] T019 [P] [US1] 在 tests/unit/c/test_pida.c 中添加初始化和默认参数测试
- [ ] T020 [P] [US1] 创建 tests/unit/python/test_pida.py 测试框架

### Implementation for User Story 1

- [ ] T021 [US1] 在 src/fb/pida.c 中实现数据准备逻辑（参数边界修正），对应ST代码"1.数据准备"段落
- [ ] T022 [US1] 在 src/fb/pida.c 中实现PID计算核心算法（标准型EQN=0），对应ST代码"PID calculate"段落
- [ ] T023 [US1] 在 src/fb/pida.c 中实现微分项计算（DK, D1, dudd），支持三种PID公式（EQN=0,1,2）
- [ ] T024 [US1] 在 src/fb/pida.c 中实现积分分离逻辑（si, SV1, INTEDB）
- [ ] T025 [US1] 在 src/fb/pida.c 中实现死区处理逻辑（DD, DeadInterval, DVDB）
- [ ] T026 [US1] 在 src/fb/pida.c 中实现位置式输出计算（OUTOPT=0, ukout）
- [ ] T027 [US1] 在 src/fb/pida.c 中实现增量式输出计算（OUTOPT=1, duout）
- [ ] T028 [US1] 在 src/fb/pida.c 中实现输出限幅逻辑（OUTU, OUTL, OVE）
- [ ] T029 [US1] 在 src/fb/pida.c 中实现输出变化率限制（OUTRAT, RealOutRat）
- [ ] T030 [US1] 在 src/fb/pida.c 中实现输出补偿计算（OUTCOMP, OCTYP加法/乘法）
- [ ] T031 [US1] 在 src/fb/pida.c 中实现正反作用切换（ACTOPT）
- [ ] T032 [US1] 在 src/fb/pida.c 中实现 pida_execute() 主函数框架，整合上述逻辑
- [ ] T033 [P] [US1] 在 tests/unit/c/test_pida.c 中添加PID计算正确性测试（自动模式稳态）
- [ ] T034 [P] [US1] 在 tests/unit/c/test_pida.c 中添加输出限幅测试

**Checkpoint**: User Story 1 完成 - 核心PID控制功能可用

---

## Phase 4: User Story 2 - 多种运行模式切换 (Priority: P1)

**Goal**: 实现五种运行模式及无扰切换

**Independent Test**: 在Python脚本中切换PIDA运行模式，验证模式切换无扰动

### Tests for User Story 2

- [ ] T035 [P] [US2] 在 tests/unit/c/test_pida.c 中添加模式切换测试（手动↔自动）
- [ ] T036 [P] [US2] 在 tests/unit/c/test_pida.c 中添加无扰切换测试（输出波动<1%）

### Implementation for User Story 2

- [ ] T037 [US2] 在 src/fb/pida.c 中实现手动模式（MODE=0）处理逻辑，包括MANMODE快慢增减
- [ ] T038 [US2] 在 src/fb/pida.c 中实现自动模式（MODE=1）处理逻辑
- [ ] T039 [US2] 在 src/fb/pida.c 中实现串级模式（MODE=2）处理逻辑，包括AUXCOMP接收
- [ ] T040 [US2] 在 src/fb/pida.c 中实现手动跟踪模式（MODE=3）处理逻辑
- [ ] T041 [US2] 在 src/fb/pida.c 中实现自动跟踪模式（MODE=4）处理逻辑
- [ ] T042 [US2] 在 src/fb/pida.c 中实现跟踪开关处理（TRKSW, TRKVAL, TRKOPT, TRKMODE）
- [ ] T043 [US2] 在 src/fb/pida.c 中实现模式切换无扰逻辑（SP跟踪PV, 输出保持）
- [ ] T044 [US2] 在 src/fb/pida.c 中实现 pida_set_mode() 和 pida_get_mode() 函数
- [ ] T045 [US2] 在 src/fb/pida.c 中实现手动输出限幅无扰逻辑（LMBLS, MOFLAG）
- [ ] T046 [US2] 在 src/fb/pida.c 中实现模式值保护（MODE>4时回退到nowRM）

**Checkpoint**: User Story 2 完成 - 五种运行模式及切换功能可用

---

## Phase 5: User Story 3 - 设定值爬坡功能 (Priority: P2)

**Goal**: 实现按时间或速率平滑改变设定值

**Independent Test**: 设置爬坡参数并启动爬坡命令，验证设定值按照设定的速率或时间逐步变化

### Tests for User Story 3

- [ ] T047 [P] [US3] 在 tests/unit/c/test_pida.c 中添加时间爬坡测试（RTYP=0）
- [ ] T048 [P] [US3] 在 tests/unit/c/test_pida.c 中添加速率爬坡测试（RTYP=1）

### Implementation for User Story 3

- [ ] T049 [US3] 在 src/fb/pida.c 中实现时间爬坡逻辑（RTYP=0, RTIMESP）
- [ ] T050 [US3] 在 src/fb/pida.c 中实现速率爬坡逻辑（RTYP=1, RRATSP）
- [ ] T051 [US3] 在 src/fb/pida.c 中实现爬坡命令处理（RCMD启动/停止）
- [ ] T052 [US3] 在 src/fb/pida.c 中实现爬坡目标值和剩余时间计算（RSPTV, RTIME, RRAT）
- [ ] T053 [US3] 在 src/fb/pida.c 中实现爬坡暂停逻辑（ROVEP, 输出超限时暂停）
- [ ] T054 [US3] 在 src/fb/pida.c 中实现爬坡防篡改逻辑（preRTYP, preRTIMESP, preRRATSP, preRSPTV）
- [ ] T055 [US3] 在 src/fb/pida.c 中实现 pida_start_ramp() 和 pida_stop_ramp() 函数
- [ ] T056 [US3] 在 src/fb/pida.c 中实现 pida_get_ramp_status() 函数

**Checkpoint**: User Story 3 完成 - 设定值爬坡功能可用

---

## Phase 6: User Story 4 - 四级过程值报警 (Priority: P2)

**Goal**: 实现HH/AH/AL/LL四级报警功能

**Independent Test**: 配置各级报警限值，验证过程值越限时正确触发相应级别的报警

### Tests for User Story 4

- [ ] T057 [P] [US4] 在 tests/unit/c/test_pida.c 中添加高限报警测试（AH, AHIND）
- [ ] T058 [P] [US4] 在 tests/unit/c/test_pida.c 中添加低限报警测试（AL, ALIND）
- [ ] T059 [P] [US4] 在 tests/unit/c/test_pida.c 中添加报警死区测试（ALMDB）

### Implementation for User Story 4

- [ ] T060 [US4] 在 src/fb/pida.c 中实现 ai_alm() 辅助函数（报警检测带死区）
- [ ] T061 [US4] 在 src/fb/pida.c 中实现高高限报警逻辑（HH, HHIND, H2, INHH2）
- [ ] T062 [US4] 在 src/fb/pida.c 中实现高限报警逻辑（AH, AHIND, H1, INHH1）
- [ ] T063 [US4] 在 src/fb/pida.c 中实现低限报警逻辑（AL, ALIND, L1, INHL1）
- [ ] T064 [US4] 在 src/fb/pida.c 中实现低低限报警逻辑（LL, LLIND, L2, INHL2）
- [ ] T065 [US4] 在 src/fb/pida.c 中实现报警信息字更新（AM按位写入）
- [ ] T066 [US4] 在 src/fb/pida.c 中实现报警死区计算（RALALMDB）
- [ ] T067 [US4] 在 src/fb/pida.c 中实现报警级别检查（H1/H2/L1/L2>0时启用）
- [ ] T068 [US4] 在 src/fb/pida.c 中实现报警总开关（ALMOPT）
- [ ] T069 [US4] 在 src/fb/pida.c 中实现 pida_get_alarms() 和 pida_get_alarm_word() 函数

**Checkpoint**: User Story 4 完成 - 四级过程值报警功能可用

---

## Phase 7: User Story 5 - 偏差报警 (Priority: P2)

**Goal**: 实现设定值与过程值偏差过大时的报警功能

**Independent Test**: 配置偏差报警限值，验证偏差超限时触发报警

### Tests for User Story 5

- [ ] T070 [P] [US5] 在 tests/unit/c/test_pida.c 中添加偏差报警触发测试
- [ ] T071 [P] [US5] 在 tests/unit/c/test_pida.c 中添加偏差报警抑制测试（INHDAL）

### Implementation for User Story 5

- [ ] T072 [US5] 在 src/fb/pida.c 中实现偏差报警限计算（DevalmLimit, DAL）
- [ ] T073 [US5] 在 src/fb/pida.c 中实现偏差报警检测逻辑（DA, almerror）
- [ ] T074 [US5] 在 src/fb/pida.c 中实现偏差报警抑制（INHDAL）
- [ ] T075 [US5] 在 src/fb/pida.c 中实现偏差报警级别检查（DALLV>0时启用）
- [ ] T076 [US5] 在 src/fb/pida.c 中更新报警信息字偏差位（AM.bit7）

**Checkpoint**: User Story 5 完成 - 偏差报警功能可用

---

## Phase 8: User Story 6 - 控制旁路功能 (Priority: P3)

**Goal**: 实现串级副调的控制旁路功能

**Independent Test**: 在串级副调模式下启用旁路，验证主调输出直接传递到副调输出

### Tests for User Story 6

- [ ] T077 [P] [US6] 在 tests/unit/c/test_pida.c 中添加旁路切入测试
- [ ] T078 [P] [US6] 在 tests/unit/c/test_pida.c 中添加旁路切出测试

### Implementation for User Story 6

- [ ] T079 [US6] 在 src/fb/pida.c 中实现旁路模式检测（CTRBP, PIDTYPE=2）
- [ ] T080 [US6] 在 src/fb/pida.c 中实现旁路模式下的输出跟踪（OUT=AUXCOMP）
- [ ] T081 [US6] 在 src/fb/pida.c 中实现旁路退出时的U1反推计算
- [ ] T082 [US6] 在 src/fb/pida.c 中实现旁路状态更新（OVE.bit3, preCTRBP）
- [ ] T083 [US6] 在 src/fb/pida.c 中实现旁路退出时自动切手动
- [ ] T084 [US6] 在 src/fb/pida.c 中实现 pida_set_bypass() 函数

**Checkpoint**: User Story 6 完成 - 控制旁路功能可用

---

## Phase 9: User Story 7 - 报警切手动功能 (Priority: P3)

**Goal**: 实现报警或通道故障时自动切换到手动模式

**Independent Test**: 触发报警后验证PIDA自动切换到手动模式

### Tests for User Story 7

- [ ] T085 [P] [US7] 在 tests/unit/c/test_pida.c 中添加报警切手动测试

### Implementation for User Story 7

- [ ] T086 [US7] 在 src/fb/pida.c 中实现限值报警切手动逻辑（MANCUT位掩码）
- [ ] T087 [US7] 在 src/fb/pida.c 中实现通道故障切手动逻辑（Q质量字检测）
- [ ] T088 [US7] 在 src/fb/pida.c 中实现偶校验故障计数（EVENFAULT）

**Checkpoint**: User Story 7 完成 - 报警切手动功能可用

---

## Phase 10: Python Binding (Python绑定)

**Purpose**: 实现Python接口，使PIDA可在Python脚本中使用

### Implementation

- [ ] T089 在 src/python/py_pida.c 中定义 PyPIDA 类型对象结构
- [ ] T090 在 src/python/py_pida.c 中实现 PyPIDA_new() 和 PyPIDA_init() 方法
- [ ] T091 在 src/python/py_pida.c 中实现 PyPIDA_execute() 方法
- [ ] T092 在 src/python/py_pida.c 中实现 PyPIDA_reset() 方法
- [ ] T093 在 src/python/py_pida.c 中实现属性 getter（output, error, hhind, ahind, alind, llind, da, am, ove）
- [ ] T094 在 src/python/py_pida.c 中实现属性 getter/setter（sp, mode, bypass）
- [ ] T095 在 src/python/py_pida.c 中实现 start_ramp(), stop_ramp() 方法
- [ ] T096 在 src/python/py_pida.c 中实现 manual_adjust(), sp_adjust() 方法
- [ ] T097 在 src/python/py_pida.c 中实现 get_state(), set_state() 方法
- [ ] T098 在 src/python/py_pida.c 中实现 set_params(), get_params() 方法
- [ ] T099 在 src/python/plcopen_module.c 中注册 PIDA 类型和枚举常量
- [ ] T100 更新 plcopen/__init__.py 导出 PIDA, PIDAMode, PIDAType, PIDAEquation

### Tests

- [ ] T101 [P] 在 tests/unit/python/test_pida.py 中添加实例创建测试
- [ ] T102 [P] 在 tests/unit/python/test_pida.py 中添加execute方法测试
- [ ] T103 [P] 在 tests/unit/python/test_pida.py 中添加模式切换测试
- [ ] T104 [P] 在 tests/unit/python/test_pida.py 中添加报警功能测试
- [ ] T105 [P] 在 tests/unit/python/test_pida.py 中添加爬坡功能测试

**Checkpoint**: Python绑定完成 - PIDA可在Python中使用

---

## Phase 11: Demo Script & Polish (示例脚本与收尾)

**Purpose**: 创建示例脚本，完成文档和代码清理

### Demo Script (IC-007, IC-008)

- [ ] T106 创建 scripts/demo_pida.py 演示脚本框架
- [ ] T107 在 scripts/demo_pida.py 中添加单回路PID控制示例
- [ ] T108 在 scripts/demo_pida.py 中添加手动/自动模式切换示例
- [ ] T109 在 scripts/demo_pida.py 中添加四级报警功能示例
- [ ] T110 在 scripts/demo_pida.py 中添加设定值爬坡功能示例

### Documentation & Cleanup

- [ ] T111 [P] 更新 docs/api-reference.md 添加PIDA API文档
- [ ] T112 [P] 更新 README.md 添加PIDA功能块说明
- [ ] T113 代码审查和注释完善（确保中文注释）
- [ ] T114 运行 quickstart.md 验证，确保示例可执行
- [ ] T115 运行完整测试套件，确保覆盖率≥80%
- [ ] T116 验证 pida.c 实现与 PIDA.xml ST源码逻辑一致性（对比核心算法分支，确保 IC-001/IC-002 合规）

**Checkpoint**: 项目完成 - PIDA功能块已就绪

---

## Dependencies & Execution Order

### Phase Dependencies

- **Setup (Phase 1)**: 无依赖 - 可立即开始
- **Foundational (Phase 2)**: 依赖 Setup 完成 - **阻塞所有用户故事**
- **User Stories (Phase 3-9)**: 全部依赖 Foundational 完成
  - US1 (P1) 和 US2 (P1) 可并行开始
  - US3, US4, US5 (P2) 在 US1 完成后可并行开始
  - US6, US7 (P3) 在 P2 故事完成后开始
- **Python Binding (Phase 10)**: 依赖 US1-US7 核心功能完成
- **Demo & Polish (Phase 11)**: 依赖 Python 绑定完成

### User Story Dependencies

| 用户故事 | 依赖 | 可并行 |
|----------|------|--------|
| US1 (P1) | Foundational | 是（与US2） |
| US2 (P1) | Foundational | 是（与US1） |
| US3 (P2) | US1 (需要PID计算基础) | 是（与US4,US5） |
| US4 (P2) | Foundational | 是（与US3,US5） |
| US5 (P2) | US4 (共享报警基础设施) | 是（与US3） |
| US6 (P3) | US2 (需要模式切换) | 是（与US7） |
| US7 (P3) | US4 (需要报警检测) | 是（与US6） |

### Parallel Opportunities

- Phase 1: T001 完成后 T002, T003, T004 可并行
- Phase 2: T005-T011（头文件定义）可并行，T012-T017（实现）依序进行
- Each US: Tests [P] 可并行，Implementation 按依赖顺序
- Phase 10: T101-T105（Python测试）可并行
- Phase 11: T111-T112（文档）可并行

---

## Parallel Example: User Story 1

```bash
# 并行执行 US1 测试框架创建:
Task T018: "创建 tests/unit/c/test_pida.c 测试框架"
Task T019: "在 tests/unit/c/test_pida.c 中添加初始化和默认参数测试"
Task T020: "创建 tests/unit/python/test_pida.py 测试框架"

# 串行执行核心算法实现:
Task T021 → T022 → T023 → ... → T032

# 并行执行验证测试:
Task T033: "添加PID计算正确性测试"
Task T034: "添加输出限幅测试"
```

---

## Implementation Strategy

### MVP First (仅完成 User Story 1 + 2)

1. 完成 Phase 1: Setup
2. 完成 Phase 2: Foundational (**关键** - 阻塞所有故事)
3. 完成 Phase 3: User Story 1 (核心PID控制)
4. 完成 Phase 4: User Story 2 (模式切换)
5. **停止并验证**: 独立测试 US1 + US2
6. 如果就绪可部署/演示 MVP

### Incremental Delivery

1. Setup + Foundational → 基础就绪
2. 添加 US1 (PID控制) → 测试 → MVP!
3. 添加 US2 (模式切换) → 测试 → 增强版
4. 添加 US3-US5 (爬坡+报警) → 测试 → 功能完整版
5. 添加 US6-US7 (旁路+报警切手动) → 测试 → 完整版
6. 添加 Python 绑定 + Demo → 最终交付

### Task Statistics

| 阶段 | 任务数 | 说明 |
|------|--------|------|
| Phase 1: Setup | 4 | 项目初始化 |
| Phase 2: Foundational | 13 | 基础设施 |
| Phase 3: US1 | 17 | 核心PID控制 |
| Phase 4: US2 | 12 | 模式切换 |
| Phase 5: US3 | 10 | 设定值爬坡 |
| Phase 6: US4 | 13 | 四级报警 |
| Phase 7: US5 | 7 | 偏差报警 |
| Phase 8: US6 | 8 | 控制旁路 |
| Phase 9: US7 | 4 | 报警切手动 |
| Phase 10: Python | 17 | Python绑定 |
| Phase 11: Demo | 11 | 示例与收尾 + ST验证 |
| **Total** | **116** | |

---

## Notes

- [P] 任务 = 不同文件，无依赖
- [Story] 标签将任务映射到特定用户故事以便追踪
- 每个用户故事应可独立完成和测试
- 实现前验证测试失败
- 每个任务或逻辑组完成后提交
- 在任何检查点停止以独立验证故事
- 避免：模糊任务、同一文件冲突、破坏独立性的跨故事依赖
