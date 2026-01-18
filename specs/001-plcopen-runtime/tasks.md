# Tasks: PLCOpen嵌入式运行时环境

**Input**: Design documents from `/specs/001-plcopen-runtime/`
**Prerequisites**: plan.md ✅, spec.md ✅, research.md ✅, data-model.md ✅, contracts/ ✅, quickstart.md ✅

**Tests**: 本任务清单包含测试任务，采用TDD方式开发核心功能块。

**Organization**: 任务按用户故事分组，支持独立实现和测试每个故事。

## Format: `[ID] [P?] [Story?] Description`

- **[P]**: 可并行执行（不同文件，无依赖）
- **[Story]**: 所属用户故事（US1, US2, US3等）
- 描述中包含精确文件路径

---

## Phase 1: Setup (项目初始化)

**Purpose**: 创建项目基础结构和构建系统

- [X] T001 创建项目目录结构（src/, include/, runtime/, tests/, docker/, cmake/, scripts/, logs/）
- [X] T002 [P] 创建 CMakeLists.txt 主构建配置
- [X] T003 [P] 创建 pyproject.toml Python项目配置
- [X] T004 [P] 创建 requirements.txt Python依赖（debugpy, watchdog, pytest）
- [X] T005 [P] 创建 .gitignore 文件
- [X] T006 [P] 创建 README.md 项目说明

---

## Phase 2: Foundational (基础设施)

**Purpose**: 所有用户故事依赖的核心基础设施

**⚠️ CRITICAL**: 用户故事实现必须等待本阶段完成

### Docker开发环境

- [X] T007 创建 docker/Dockerfile.dev 开发环境镜像（配置阿里云镜像源）
- [X] T008 创建 docker-compose.yml Docker Compose配置
- [X] T009 [P] 创建 cmake/toolchain-arm.cmake ARM交叉编译工具链配置

### C基础设施

- [X] T010 [P] 创建 include/plcopen/plcopen.h 主头文件
- [X] T011 [P] 创建 include/plcopen/fb_common.h 功能块通用定义
- [X] T012 [P] 创建 src/common/error.h 和 src/common/error.c 错误处理
- [X] T013 [P] 创建 src/common/log.h 和 src/common/log.c 日志系统（控制台+文件轮转）

### Python运行时基础

- [X] T014 创建 runtime/__init__.py 模块初始化
- [X] T015 [P] 创建 runtime/config.py 配置管理（脚本目录、周期、调试端口等）

### 测试框架

- [X] T016 [P] 配置 CMakeLists.txt 集成Unity测试框架
- [X] T017 [P] 创建 tests/unit/c/unity_config.h Unity配置
- [X] T018 [P] 配置 pytest.ini Python测试配置

### ARM交叉编译（早期验证）

- [X] T018a 创建 docker/Dockerfile.arm ARM交叉编译镜像（验证工具链可用性）

**Checkpoint**: 基础设施就绪，用户故事实现可以开始

---

## Phase 3: User Story 1 - 运行PID控制功能块 (Priority: P1) 🎯 MVP

**Goal**: Python脚本可以创建PID实例、执行计算、动态调参

**Independent Test**: 运行 `python -c "import plcopen; pid = plcopen.PID(); print(pid.execute(100, 80))"`

### Tests for User Story 1

- [X] T019 [P] [US1] 创建 tests/unit/c/test_pid.c PID功能块C单元测试
- [X] T020 [P] [US1] 创建 tests/unit/python/test_pid.py PID Python绑定单元测试

### Implementation for User Story 1

- [X] T021 [P] [US1] 创建 src/fb/pid.h PID功能块头文件（参数、输入、输出、状态结构体）
- [X] T022 [US1] 实现 src/fb/pid.c PID功能块核心算法（位置式PID + 输出限幅）
- [X] T023 [US1] 创建 src/python/py_pid.c PID Python绑定（类定义、方法、属性）
- [X] T024 [US1] 更新 src/python/plcopen_module.c 注册PID类型到模块

**Checkpoint**: PID功能块可独立使用，`import plcopen; plcopen.PID()` 可工作

---

## Phase 4: User Story 2 - 运行一阶惯性功能块 (Priority: P1)

**Goal**: Python脚本可以创建一阶惯性实例进行信号滤波

**Independent Test**: 运行 `python -c "import plcopen; fo = plcopen.FirstOrder(); print(fo.execute(100))"`

### Tests for User Story 2

- [X] T025 [P] [US2] 创建 tests/unit/c/test_first_order.c 一阶惯性C单元测试
- [X] T026 [P] [US2] 创建 tests/unit/python/test_first_order.py 一阶惯性Python绑定单元测试

### Implementation for User Story 2

- [X] T027 [P] [US2] 创建 src/fb/first_order.h 一阶惯性头文件
- [X] T028 [US2] 实现 src/fb/first_order.c 一阶惯性核心算法（离散化递推）
- [X] T029 [US2] 创建 src/python/py_first_order.c 一阶惯性Python绑定
- [X] T030 [US2] 更新 src/python/plcopen_module.c 注册FirstOrder类型到模块

**Checkpoint**: 一阶惯性功能块可独立使用

---

## Phase 5: User Story 3 - Python脚本热加载管理 (Priority: P2)

**Goal**: 运行时自动检测脚本变更并热重载（保留功能块状态）

**Independent Test**: 启动运行时后，修改scripts/目录下的脚本文件，观察日志确认重新加载

### Tests for User Story 3

- [X] T031 [P] [US3] 创建 tests/unit/python/test_script_manager.py 脚本管理器单元测试

### Implementation for User Story 3

- [X] T032 [US3] 创建 runtime/script_manager.py 脚本管理器（watchdog监控、热重载）
- [X] T033 [US3] 实现脚本加载逻辑（检测main函数、模块命名空间隔离、错误隔离）
- [X] T033a [US3] 实现脚本执行错误隔离（try-except包装、错误计数、连续失败自动禁用）
- [X] T034 [US3] 实现热重载逻辑（importlib.reload + 状态保留回调）
- [X] T035 [US3] 实现脚本卸载逻辑（删除检测、资源释放）
- [X] T036 [US3] 添加 src/python/py_pid.c 中 get_state/set_state 方法（状态序列化）
- [X] T037 [US3] 添加 src/python/py_first_order.c 中 get_state/set_state 方法

**Checkpoint**: 脚本热重载功能可独立使用

---

## Phase 6: User Story 4 - VSCode远程调试 (Priority: P2)

**Goal**: 使用VSCode连接到运行时容器调试Python脚本

**Independent Test**: 在VSCode中附加到运行时进程，设置断点，验证脚本在断点处暂停

### Tests for User Story 4

- [X] T038 [US4] 创建 tests/integration/test_debug.py 调试功能集成测试

### Implementation for User Story 4

- [X] T039 [US4] 创建 runtime/debug.py debugpy集成（监听端口5678）
- [X] T040 [US4] 更新 docker-compose.yml 暴露调试端口5678
- [X] T041 [P] [US4] 创建 .vscode/launch.json 调试配置（附加模式）
- [X] T042 [P] [US4] 创建 .vscode/tasks.json 任务配置（构建、运行）

**Checkpoint**: VSCode调试功能可独立使用

---

## Phase 7: User Story 5 - X86开发模拟环境 (Priority: P2)

**Goal**: 在X86 Docker容器中编译运行运行时，行为与ARM一致

**Independent Test**: 运行 `docker compose up --build` 成功启动并执行示例脚本

### Tests for User Story 5

- [X] T043 [US5] 创建 tests/integration/test_runtime.py 运行时集成测试

### Implementation for User Story 5

- [X] T044 [US5] 创建 runtime/main.py 运行时入口（初始化、主循环、信号处理）
- [X] T045 [US5] 更新 CMakeLists.txt 添加X86/ARM条件编译
- [X] T046 [US5] 实现 Python解释器嵌入初始化（PyConfig配置）
- [X] T047 [US5] 实现主循环逻辑（周期调用脚本main函数）
- [X] T048 [P] [US5] 创建 scripts/demo.py 示例脚本（PID温度控制演示）

**Checkpoint**: X86开发环境完全可用，docker compose up 可运行

---

## Phase 8: User Story 6 - 功能块扩展机制 (Priority: P3)

**Goal**: 开发人员可按规范添加新功能块类型

**Independent Test**: 按文档步骤添加一个空功能块，编译后在Python中调用

### Implementation for User Story 6

- [X] T049 [US6] 创建 docs/extending.md 功能块扩展开发指南
- [X] T050 [US6] 创建 src/fb/fb_registry.h 和 src/fb/fb_registry.c 功能块注册表
- [X] T051 [US6] 重构 plcopen_module.c 使用注册表动态注册功能块
- [X] T052 [US6] 创建 templates/fb_template.c 功能块模板文件

**Checkpoint**: 功能块扩展机制可用

---

## Phase 9: Polish & Cross-Cutting Concerns

**Purpose**: 文档完善、代码优化、最终验证

- [X] T053 [P] 更新 README.md 添加完整的快速入门指南
- [X] T054 [P] 创建 docs/architecture.md 架构设计文档
- [X] T055 [P] 创建 docs/api-reference.md API参考文档
- [X] T056 代码审查和重构（圈复杂度检查）
- [X] T057 性能基准测试套件：
  - [X] T057a 创建 tests/benchmark/bench_pid.c PID执行时间基准测试（目标<1ms）
  - [X] T057b 创建 tests/benchmark/bench_first_order.c 一阶惯性执行时间基准测试
  - [X] T057c 创建 tests/benchmark/bench_memory.c 功能块实例内存占用测试（目标<1KB）
  - [X] T057d 运行基准测试并记录结果到 docs/benchmark-results.md
- [X] T058 运行 quickstart.md 全流程验证

---

## Dependencies & Execution Order

### Phase Dependencies

```
Phase 1 (Setup)
    ↓
Phase 2 (Foundational) ← BLOCKS all user stories
    ↓
┌───────────────────────────────────────────────────┐
│  Phase 3 (US1: PID) ← MVP                         │
│  Phase 4 (US2: FirstOrder) ← 可与US1并行          │
└───────────────────────────────────────────────────┘
    ↓
┌───────────────────────────────────────────────────┐
│  Phase 5 (US3: 热加载) ← 依赖US1/US2的get_state   │
│  Phase 6 (US4: 调试)   ← 可与US3并行              │
│  Phase 7 (US5: X86环境) ← 依赖US1-US4             │
└───────────────────────────────────────────────────┘
    ↓
Phase 8 (US6: 扩展机制)
    ↓
Phase 9 (Polish)
```

### User Story Dependencies

- **User Story 1 (P1)**: 依赖Phase 2完成，无其他故事依赖
- **User Story 2 (P1)**: 依赖Phase 2完成，可与US1并行
- **User Story 3 (P2)**: 依赖US1/US2的get_state/set_state方法
- **User Story 4 (P2)**: 依赖Phase 2完成，可与US3并行
- **User Story 5 (P2)**: 依赖US1-US4完成（需要完整运行时）
- **User Story 6 (P3)**: 依赖US1/US2完成（需要现有功能块作为参考）

### Parallel Opportunities

Phase 2（基础设施）内部：
```
T010 ─┬─ T011 ─┬─ T012 ─┬─ T013  (C基础设施，可并行)
      │        │        │
T016 ─┴─ T017 ─┴─ T018           (测试框架，可并行)
```

Phase 3 + Phase 4（US1 + US2，可并行）：
```
Phase 3: T019 ─┬─ T020  →  T021 ─┬─ T022 → T023 → T024
               │                 │
Phase 4: T025 ─┴─ T026  →  T027 ─┴─ T028 → T029 → T030
```

---

## Implementation Strategy

### MVP First (User Story 1 Only)

1. ✅ Phase 1: Setup
2. ✅ Phase 2: Foundational
3. ✅ Phase 3: User Story 1 (PID)
4. **STOP and VALIDATE**: 测试 `import plcopen; pid = plcopen.PID()`
5. 可部署/演示 MVP

### Incremental Delivery

1. Setup + Foundational → 基础就绪
2. + US1 (PID) → 测试 → **MVP Release**
3. + US2 (FirstOrder) → 测试 → 功能块完整
4. + US3 (热加载) → 测试 → 开发体验提升
5. + US4 (调试) → 测试 → 调试能力就绪
6. + US5 (X86环境) → 测试 → 完整开发环境
7. + US6 (扩展) → 测试 → 可扩展版本

### Task Count Summary

| Phase | 任务数 | 并行任务数 |
|-------|--------|-----------|
| Phase 1: Setup | 6 | 5 |
| Phase 2: Foundational | 13 | 9 |
| Phase 3: US1 PID | 6 | 2 |
| Phase 4: US2 FirstOrder | 6 | 2 |
| Phase 5: US3 热加载 | 8 | 1 |
| Phase 6: US4 调试 | 5 | 2 |
| Phase 7: US5 X86环境 | 6 | 1 |
| Phase 8: US6 扩展 | 4 | 0 |
| Phase 9: Polish | 10 | 3 |
| **Total** | **64** | **25** |

---

## Notes

- [P] 任务 = 不同文件，无依赖，可并行
- [Story] 标签将任务映射到特定用户故事以便追踪
- 每个用户故事可独立完成和测试
- 先写测试，确认测试失败后再实现
- 每个任务或逻辑组完成后提交
- 在任意检查点可停止并独立验证故事
- 避免：模糊任务、同文件冲突、破坏独立性的跨故事依赖
