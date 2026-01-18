# PLCOpen运行时 - 数据模型

**日期**: 2026-01-18
**分支**: `001-plcopen-runtime`
**版本**: 1.0

## 实体关系图

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           Runtime (运行时环境)                            │
│  - config: RuntimeConfig                                                │
│  - state: RuntimeState                                                  │
└───────────────────────────────┬─────────────────────────────────────────┘
                                │ 1
                                │ 管理
                                ▼ 1..*
┌─────────────────────────────────────────────────────────────────────────┐
│                      ScriptManager (脚本管理器)                           │
│  - script_dir: Path                                                     │
│  - scan_interval: float                                                 │
│  - loaded_scripts: Dict[str, ScriptContext]                             │
└───────────────────────────────┬─────────────────────────────────────────┘
                                │ 1
                                │ 管理
                                ▼ 0..*
┌─────────────────────────────────────────────────────────────────────────┐
│                      ScriptContext (脚本上下文)                           │
│  - name: str                                                            │
│  - module: ModuleType                                                   │
│  - fb_instances: Dict[str, FunctionBlockInstance]  (脚本私有)             │
│  - last_modified: float                                                 │
│  - state: ScriptState                                                   │
└───────────────────────────────┬─────────────────────────────────────────┘
                                │ 1
                                │ 拥有
                                ▼ 0..*
┌─────────────────────────────────────────────────────────────────────────┐
│                 FunctionBlockInstance (功能块实例)                        │
│  - id: int                                                              │
│  - fb_type: FunctionBlockType                                           │
│  - params: Dict[str, float]                                             │
│  - state: Dict[str, float]  (内部状态)                                    │
└───────────────────────────────┬─────────────────────────────────────────┘
                                │ N
                                │ 类型引用
                                ▼ 1
┌─────────────────────────────────────────────────────────────────────────┐
│                   FunctionBlockType (功能块类型)                          │
│  - name: str                                                            │
│  - init: Callable                                                       │
│  - execute: Callable                                                    │
│  - destroy: Callable                                                    │
└─────────────────────────────────────────────────────────────────────────┘
```

## 实体详细定义

### 1. Runtime (运行时环境)

整体运行时容器，管理功能块库、Python解释器和脚本执行。

| 字段 | 类型 | 说明 | 约束 |
|------|------|------|------|
| config | RuntimeConfig | 运行时配置 | 必填 |
| state | RuntimeState | 运行状态 | 枚举 |
| script_manager | ScriptManager | 脚本管理器 | 唯一实例 |
| fb_registry | FunctionBlockRegistry | 功能块注册表 | 唯一实例 |

**状态转换**：
```
INIT → RUNNING → STOPPING → STOPPED
         ↑          │
         └──────────┘ (重启)
```

### 2. RuntimeConfig (运行时配置)

| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| script_dir | str | "scripts/" | 脚本目录路径 |
| scan_interval | float | 1.0 | 目录扫描周期（秒） |
| cycle_time | float | 0.1 | 脚本执行周期（秒） |
| debug_enabled | bool | true | 是否启用调试 |
| debug_port | int | 5678 | debugpy端口 |
| log_dir | str | "logs/" | 日志目录 |
| log_max_size | int | 10485760 | 单个日志文件最大字节数 |
| log_backup_count | int | 5 | 日志文件保留数量 |

### 3. ScriptContext (脚本上下文)

每个Python脚本的运行上下文，包含脚本模块引用和私有的功能块实例。

| 字段 | 类型 | 说明 | 约束 |
|------|------|------|------|
| name | str | 脚本名称（无.py后缀） | 唯一，匹配文件名 |
| path | Path | 脚本文件完整路径 | 必须存在 |
| module | ModuleType | Python模块对象 | 可为空（加载失败时） |
| fb_instances | Dict[str, FBInstance] | 功能块实例字典 | 脚本私有 |
| last_modified | float | 文件最后修改时间戳 | 用于热重载检测 |
| state | ScriptState | 脚本状态 | 枚举 |
| error_count | int | 连续错误次数 | 超过阈值暂停脚本 |
| last_error | str | 最后一次错误信息 | 可为空 |

**ScriptState 枚举**：
- `LOADING`: 正在加载
- `RUNNING`: 正常运行
- `ERROR`: 执行出错（可恢复）
- `DISABLED`: 已禁用
- `UNLOADING`: 正在卸载

### 4. FunctionBlockInstance (功能块实例)

功能块的运行时实例，具有独立的状态和参数。

| 字段 | 类型 | 说明 | 约束 |
|------|------|------|------|
| id | int | 实例唯一标识符 | 自增，全局唯一 |
| name | str | 实例名称 | 脚本内唯一 |
| fb_type | str | 功能块类型名称 | 必须已注册 |
| params | Dict[str, float] | 可调参数 | 类型特定 |
| state | Dict[str, float] | 内部状态 | 类型特定 |
| c_instance | void* | C侧实例指针 | 不透明句柄 |

### 5. PID功能块

位置式PID控制器。

**参数 (params)**：
| 参数 | 类型 | 默认值 | 范围 | 说明 |
|------|------|--------|------|------|
| kp | float | 1.0 | [0, ∞) | 比例增益 |
| ki | float | 0.0 | [0, ∞) | 积分增益 |
| kd | float | 0.0 | [0, ∞) | 微分增益 |
| out_min | float | -∞ | (-∞, out_max) | 输出下限 |
| out_max | float | +∞ | (out_min, ∞) | 输出上限 |
| dt | float | 0.1 | (0, ∞) | 采样周期（秒） |

**输入**：
| 输入 | 类型 | 说明 |
|------|------|------|
| setpoint | float | 设定值 |
| process_value | float | 过程值（反馈） |

**输出**：
| 输出 | 类型 | 说明 |
|------|------|------|
| output | float | 控制输出 |
| error | float | 当前偏差 |
| saturated | bool | 是否限幅 |

**内部状态 (state)**：
| 状态 | 类型 | 说明 |
|------|------|------|
| integral | float | 积分累积值 |
| prev_error | float | 上一次偏差 |
| prev_output | float | 上一次输出 |

**算法公式**：
```
error = setpoint - process_value
integral = integral + error * dt
derivative = (error - prev_error) / dt
output = kp * error + ki * integral + kd * derivative
output = clamp(output, out_min, out_max)
```

### 6. FirstOrder功能块（一阶惯性）

一阶惯性（一阶滞后）滤波器。

**参数 (params)**：
| 参数 | 类型 | 默认值 | 范围 | 说明 |
|------|------|--------|------|------|
| k | float | 1.0 | (-∞, ∞) | 增益 |
| t | float | 1.0 | (0, ∞) | 时间常数（秒） |
| dt | float | 0.1 | (0, ∞) | 采样周期（秒） |

**输入**：
| 输入 | 类型 | 说明 |
|------|------|------|
| input | float | 输入信号 |

**输出**：
| 输出 | 类型 | 说明 |
|------|------|------|
| output | float | 输出信号 |

**内部状态 (state)**：
| 状态 | 类型 | 说明 |
|------|------|------|
| prev_output | float | 上一次输出值 |

**算法公式（离散化）**：
```
alpha = dt / (t + dt)
output = alpha * k * input + (1 - alpha) * prev_output
```

### 7. FunctionBlockRegistry (功能块注册表)

管理所有已注册的功能块类型。

| 字段 | 类型 | 说明 |
|------|------|------|
| types | Dict[str, FBTypeInfo] | 类型名称到类型信息的映射 |

**FBTypeInfo结构**：
| 字段 | 类型 | 说明 |
|------|------|------|
| name | str | 类型名称 |
| create | Callable | 创建实例的工厂函数 |
| destroy | Callable | 销毁实例的清理函数 |
| execute | Callable | 执行一步计算的函数 |
| get_state | Callable | 获取内部状态（用于热重载） |
| set_state | Callable | 恢复内部状态（用于热重载） |
| param_schema | Dict | 参数模式（用于验证） |

## 验证规则

### PID功能块
1. `kp >= 0`，`ki >= 0`，`kd >= 0`
2. `out_min < out_max`
3. `dt > 0`

### FirstOrder功能块
1. `t > 0`（时间常数必须为正）
2. `dt > 0`

### 脚本约定
1. 脚本必须定义 `main()` 函数
2. 脚本文件名必须是有效的Python标识符
3. 脚本文件编码必须为UTF-8

## 状态迁移

### 脚本生命周期
```
[文件创建] → LOADING → RUNNING → [文件修改] → LOADING → RUNNING
                  ↓                                     ↓
               ERROR ←─────────────────────────────────┘
                  ↓
             DISABLED (连续错误超过阈值)
                  ↓
[文件删除] → UNLOADING → [移除]
```

### 功能块实例生命周期
```
[创建] → 活跃 → [脚本重载] → 活跃（状态保留）
           ↓
      [脚本卸载] → [销毁]
```
