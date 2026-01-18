# Implementation Plan: PLCOpen嵌入式运行时环境

**Branch**: `001-plcopen-runtime` | **Date**: 2026-01-18 | **Spec**: [spec.md](spec.md)
**Input**: Feature specification from `/specs/001-plcopen-runtime/spec.md`

**Note**: This template is filled in by the `/speckit.plan` command. See `.specify/templates/commands/plan.md` for the execution workflow.

## Summary

构建一个嵌入式PLCOpen运行时环境，使用C11实现核心功能块（PID、一阶惯性），通过Python C扩展提供脚本化控制能力。支持ARM Cortex-M4目标架构和X86开发模拟环境，使用Docker容器化开发环境，支持VSCode远程调试Python脚本。

## Technical Context

**Language/Version**: C11（运行时核心）+ Python 3.11（脚本层）
**Primary Dependencies**:
- CPython 嵌入式API（Python C扩展）
- CMake 3.20+（构建系统）
- arm-none-eabi-gcc（ARM交叉编译）
- debugpy（远程调试）
**Storage**: 文件系统（脚本目录、日志文件）
**Testing**: pytest（Python层）+ Unity/CMocka（C层单元测试）
**Target Platform**: ARM Cortex-M4（生产）+ X86 Linux（开发/模拟）
**Project Type**: 嵌入式运行时 + Python扩展模块（混合项目）
**Performance Goals**:
- PID单次执行 < 1ms
- 支持10+并发脚本
- 功能块实例内存 < 1KB
**Constraints**:
- 国内镜像源加速
- 热重载保留状态
- 脚本隔离执行
**Scale/Scope**: 初始2个功能块，可扩展架构

## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

根据项目章程检查以下关键点：

- **✓ 本地化优先：** 所有文档使用简体中文，代码注释使用简体中文，日志输出使用简体中文（技术术语保留英文）
- **✓ SOLID 原则：** 功能块采用统一接口设计（OCP），脚本管理器与运行时核心职责分离（SRP），功能块通过注册机制扩展（DIP）
- **✓ 架构约束：** 新建项目，目录结构遵循嵌入式+Python扩展混合项目惯例
- **✓ 环境隔离：** 使用Docker容器化开发环境，Python依赖通过venv隔离，配置文件置于项目目录
- **✓ 依赖管理：** 使用阿里云/清华镜像加速，CPython为PSF许可（类BSD），debugpy为MIT许可
- **✓ 代码质量：** 设计包含单元测试（Unity/pytest），功能块接口有中文文档，圈复杂度控制
- **✓ 跨平台：** 支持ARM/X86双平台，CMake跨平台构建，Docker支持Windows/Linux/Mac

**违规判定：** 无违规，设计符合章程要求。

## Project Structure

### Documentation (this feature)

```text
specs/001-plcopen-runtime/
├── plan.md              # 实现计划（本文件）
├── research.md          # 技术研究报告
├── data-model.md        # 数据模型
├── quickstart.md        # 快速入门指南
├── contracts/           # API契约
│   ├── python-api.md    # Python API契约
│   └── c-api.md         # C API契约
└── tasks.md             # 任务清单（由 /speckit.tasks 生成）
```

### Source Code (repository root)

```text
plcopen-runtime-py/
├── src/                          # C源代码
│   ├── fb/                       # 功能块实现
│   │   ├── pid.c                 # PID功能块
│   │   ├── pid.h
│   │   ├── first_order.c         # 一阶惯性功能块
│   │   └── first_order.h
│   ├── runtime/                  # 运行时核心
│   │   ├── runtime.c             # 运行时主逻辑
│   │   ├── runtime.h
│   │   ├── script_loader.c       # 脚本加载器
│   │   └── script_loader.h
│   ├── python/                   # Python C扩展
│   │   ├── plcopen_module.c      # 模块入口
│   │   ├── py_pid.c              # PID Python绑定
│   │   └── py_first_order.c      # 一阶惯性Python绑定
│   └── common/                   # 公共工具
│       ├── error.c               # 错误处理
│       ├── error.h
│       ├── log.c                 # 日志系统
│       └── log.h
│
├── include/                      # 公共头文件
│   └── plcopen/
│       ├── plcopen.h             # 主头文件
│       └── fb_common.h           # 功能块通用定义
│
├── runtime/                      # Python运行时模块
│   ├── __init__.py
│   ├── main.py                   # 入口点
│   ├── script_manager.py         # 脚本管理器
│   ├── config.py                 # 配置管理
│   └── debug.py                  # 调试服务
│
├── scripts/                      # 用户脚本目录（热加载）
│   └── .gitkeep
│
├── tests/                        # 测试代码
│   ├── unit/                     # 单元测试
│   │   ├── c/                    # C单元测试（Unity框架）
│   │   │   ├── test_pid.c
│   │   │   └── test_first_order.c
│   │   └── python/               # Python单元测试（pytest）
│   │       ├── test_pid.py
│   │       └── test_first_order.py
│   └── integration/              # 集成测试
│       └── test_runtime.py
│
├── docker/                       # Docker配置
│   ├── Dockerfile.dev            # 开发环境镜像
│   └── Dockerfile.arm            # ARM交叉编译镜像
│
├── cmake/                        # CMake配置
│   ├── toolchain-arm.cmake       # ARM工具链
│   └── FindPython.cmake          # Python查找脚本
│
├── .vscode/                      # VSCode配置
│   ├── launch.json               # 调试配置
│   └── tasks.json                # 任务配置
│
├── logs/                         # 日志目录
│   └── .gitkeep
│
├── docker-compose.yml            # Docker Compose配置
├── CMakeLists.txt                # 主CMake配置
├── pyproject.toml                # Python项目配置
├── requirements.txt              # Python依赖
└── README.md                     # 项目说明
```

**Structure Decision**: 采用嵌入式运行时+Python扩展混合项目结构。C代码按功能模块组织（功能块、运行时核心、Python绑定），Python代码提供运行时管理和脚本调度功能。用户脚本与系统代码分离，支持热加载。

## Complexity Tracking

> 无违规项，无需记录复杂性理由。
