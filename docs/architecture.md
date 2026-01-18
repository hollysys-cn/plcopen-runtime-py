# 架构设计文档

## 概述

PLCOpen 嵌入式运行时是一个轻量级的工业控制功能块执行环境，设计用于资源受限的嵌入式设备。它将高性能的 C 语言功能块与灵活的 Python 脚本层相结合。

## 系统架构

```
┌─────────────────────────────────────────────────────────────────┐
│                     Python 脚本层                                │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │  用户脚本 (scripts/*.py)                                   │   │
│  │  - main() 函数入口                                         │   │
│  │  - 使用 plcopen 模块                                       │   │
│  └──────────────────────────────────────────────────────────┘   │
│                              │                                   │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │  运行时管理 (runtime/)                                     │   │
│  │  - ScriptManager: 脚本加载、热重载                         │   │
│  │  - DebugServer: VSCode 远程调试                           │   │
│  │  - Config: 配置管理                                       │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                               │
                     Python C Extension API
                               │
┌─────────────────────────────────────────────────────────────────┐
│                     Python 绑定层                                │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │  plcopen 模块 (src/python/)                               │   │
│  │  - plcopen_module.c: 模块入口                             │   │
│  │  - py_pid.c: PID 类绑定                                   │   │
│  │  - py_first_order.c: FirstOrder 类绑定                    │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                               │
                        C Function Calls
                               │
┌─────────────────────────────────────────────────────────────────┐
│                     C 功能块层                                   │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │  功能块实现 (src/fb/)                                      │   │
│  │  - pid.c: 位置式 PID 算法                                  │   │
│  │  - first_order.c: 一阶惯性滤波                            │   │
│  │  - fb_registry.c: 功能块注册表                            │   │
│  └──────────────────────────────────────────────────────────┘   │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐   │
│  │  通用基础设施 (src/common/)                                │   │
│  │  - error.c: 错误处理                                       │   │
│  │  - log.c: 日志系统                                        │   │
│  └──────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

## 组件详解

### 1. Python 脚本层

用户编写的控制逻辑脚本，存放在 `scripts/` 目录。

**特性：**
- 每个 `.py` 文件是独立的控制脚本
- 必须包含 `main()` 函数作为入口
- 支持热重载（保留功能块状态）
- 模块命名空间隔离

**示例：**
```python
import plcopen

pid = plcopen.PID(kp=2.0, ki=0.1, kd=0.05)

def main():
    setpoint = 100.0
    pv = read_sensor()
    output = pid.execute(setpoint=setpoint, pv=pv)
    write_output(output)
    return output
```

### 2. 运行时管理

`runtime/` 模块提供脚本生命周期管理。

**ScriptManager:**
- 扫描脚本目录
- 加载和卸载脚本模块
- 检测文件变更（watchdog）
- 热重载（保留功能块状态）
- 错误隔离和自动禁用

**DebugServer:**
- 集成 debugpy
- 监听端口 5678
- 支持 VSCode 远程附加

**Config:**
- 环境变量读取
- 配置验证
- 目录管理

### 3. Python 绑定层

将 C 功能块暴露为 Python 类。

**特性：**
- 使用 Python C Extension API
- 静态类型定义（PyTypeObject）
- 属性读写支持
- 状态序列化（get_state/set_state）

**绑定模式：**
```c
typedef struct {
    PyObject_HEAD
    pid_instance_t instance;  // C 实例
} PIDObject;
```

### 4. C 功能块层

核心控制算法实现。

**PID 控制器：**
- 位置式算法
- 输出限幅
- 抗积分饱和

**一阶惯性滤波：**
- 离散化递推公式
- 可调时间常数

**设计原则：**
- 无动态内存分配（运行时）
- 确定性执行时间
- 线程安全（无全局状态）

### 5. 功能块注册表

支持动态注册功能块类型。

```c
typedef struct {
    const char *name;
    size_t instance_size;
    plcopen_error_t (*init)(void *inst);
    plcopen_error_t (*execute)(void *inst, void *input, void *output);
    void (*get_state)(const void *inst, void *state);
    void (*set_state)(void *inst, const void *state);
} fb_info_t;
```

## 执行模型

### 主循环

```
初始化
    │
    ▼
┌─────────────────────┐
│  加载配置           │
│  初始化脚本管理器    │
│  启动调试服务器      │
│  加载所有脚本        │
└─────────────────────┘
    │
    ▼
┌─────────────────────┐
│     主循环开始       │◄──────────────┐
└─────────────────────┘               │
    │                                  │
    ▼                                  │
┌─────────────────────┐               │
│  检查热重载         │               │
└─────────────────────┘               │
    │                                  │
    ▼                                  │
┌─────────────────────┐               │
│  执行所有脚本 main() │               │
└─────────────────────┘               │
    │                                  │
    ▼                                  │
┌─────────────────────┐               │
│  等待下一周期        │───────────────┘
└─────────────────────┘
    │
    ▼ (SIGTERM/SIGINT)
┌─────────────────────┐
│     清理资源        │
└─────────────────────┘
```

### 周期时序

```
|<────────────── 周期时间 (默认 100ms) ──────────────>|
├─────────────┬─────────────────────────────────────────┤
│  脚本执行    │              空闲等待                    │
│   (<1ms)    │                                         │
├─────────────┴─────────────────────────────────────────┤
                                                     下一周期
```

## 热重载机制

### 流程

1. **检测变更**：watchdog 监控文件系统事件
2. **保存状态**：调用所有功能块的 `get_state()`
3. **卸载模块**：从 `sys.modules` 移除
4. **重新加载**：重新导入模块
5. **恢复状态**：调用 `set_state()` 恢复

### 状态保留

```python
# 重载前
state = pid.get_state()
# {'integral': 123.45, 'prev_error': 2.5, 'prev_output': 85.0}

# 重载后
pid.set_state(state)
# 积分器等状态完整恢复
```

## 错误处理

### 分层策略

| 层级 | 策略 |
|------|------|
| C 功能块 | 返回错误码，不抛出异常 |
| Python 绑定 | 转换为 Python 异常 |
| 脚本执行 | try-except 隔离 |
| 运行时 | 错误计数 + 自动禁用 |

### 错误码

```c
typedef enum {
    PLCOPEN_OK = 0,
    PLCOPEN_ERR_NULL,      // 空指针
    PLCOPEN_ERR_PARAM,     // 参数错误
    PLCOPEN_ERR_RANGE,     // 范围错误
    PLCOPEN_ERR_NAN,       // NaN 输入
    PLCOPEN_ERR_INF,       // 无穷大输入
    PLCOPEN_ERR_MEMORY,    // 内存错误
} plcopen_error_t;
```

## 内存模型

### 实例布局

```
PIDObject (Python 对象)
├── PyObject_HEAD (16 bytes)
│   ├── ob_refcnt
│   └── ob_type
└── pid_instance_t (C 实例)
    ├── params (48 bytes)
    │   ├── kp, ki, kd
    │   ├── out_min, out_max
    │   └── dt
    ├── state (24 bytes)
    │   ├── integral
    │   ├── prev_error
    │   └── prev_output
    └── output (24 bytes)
        ├── output
        ├── error
        └── saturated
```

### 内存预算

| 组件 | 大小 |
|------|------|
| PID 实例 | < 200 bytes |
| FirstOrder 实例 | < 100 bytes |
| 脚本管理器 | ~10 KB |
| Python 解释器 | ~5 MB |

## 跨平台支持

### 构建目标

| 平台 | 架构 | 编译器 | 用途 |
|------|------|--------|------|
| Linux/Docker | x86_64 | gcc | 开发和测试 |
| ARM | Cortex-M4 | arm-none-eabi-gcc | 生产部署 |

### 条件编译

```cmake
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(PLCOPEN_TARGET_ARM ON)
    add_compile_definitions(PLCOPEN_TARGET_ARM)
else()
    set(PLCOPEN_TARGET_X86 ON)
    add_compile_definitions(PLCOPEN_TARGET_X86)
endif()
```

## 安全考虑

### 输入验证

- 所有 C 函数检查空指针
- 数值输入检查 NaN 和无穷大
- 参数范围验证

### 脚本隔离

- 每个脚本独立命名空间
- 错误不影响其他脚本
- 连续失败自动禁用

### 资源限制

- 最大脚本数量（可配置）
- 周期超时警告
- 内存使用监控（TODO）

## 扩展点

1. **新功能块**：参见 [extending.md](extending.md)
2. **自定义日志后端**：实现 `log_backend_t` 接口
3. **外部通信**：通过脚本集成（MQTT、OPC UA 等）
4. **硬件 I/O**：平台特定驱动
