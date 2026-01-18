# PLCOpen运行时 - C API契约

**日期**: 2026-01-18
**版本**: 1.0

## 头文件结构

```
include/
├── plcopen/
│   ├── plcopen.h         # 主头文件
│   ├── fb_common.h       # 功能块通用定义
│   ├── fb_pid.h          # PID功能块
│   ├── fb_first_order.h  # 一阶惯性功能块
│   ├── runtime.h         # 运行时管理
│   └── error.h           # 错误码定义
```

## 错误码定义 (error.h)

```c
#ifndef PLCOPEN_ERROR_H
#define PLCOPEN_ERROR_H

/**
 * @brief PLCOpen错误码
 */
typedef enum {
    PLCOPEN_OK = 0,              /**< 成功 */
    PLCOPEN_ERR_INVALID_PARAM,   /**< 参数无效 */
    PLCOPEN_ERR_NULL_PTR,        /**< 空指针 */
    PLCOPEN_ERR_OUT_OF_MEMORY,   /**< 内存不足 */
    PLCOPEN_ERR_INVALID_STATE,   /**< 状态无效 */
    PLCOPEN_ERR_NOT_FOUND,       /**< 未找到 */
    PLCOPEN_ERR_ALREADY_EXISTS,  /**< 已存在 */
    PLCOPEN_ERR_OVERFLOW,        /**< 溢出 */
    PLCOPEN_ERR_UNDERFLOW,       /**< 下溢 */
    PLCOPEN_ERR_NAN,             /**< NaN值 */
    PLCOPEN_ERR_INF,             /**< 无穷值 */
} plcopen_error_t;

/**
 * @brief 获取错误描述
 * @param err 错误码
 * @return 错误描述字符串（简体中文）
 */
const char* plcopen_strerror(plcopen_error_t err);

#endif /* PLCOPEN_ERROR_H */
```

## 功能块通用接口 (fb_common.h)

```c
#ifndef PLCOPEN_FB_COMMON_H
#define PLCOPEN_FB_COMMON_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 功能块实例句柄
 */
typedef struct fb_instance* fb_handle_t;

/**
 * @brief 功能块类型信息
 */
typedef struct {
    const char* name;           /**< 类型名称 */
    size_t instance_size;       /**< 实例大小 */

    /**
     * @brief 初始化函数指针
     * @param handle 实例句柄
     * @return 错误码
     */
    plcopen_error_t (*init)(fb_handle_t handle);

    /**
     * @brief 销毁函数指针
     * @param handle 实例句柄
     */
    void (*destroy)(fb_handle_t handle);

    /**
     * @brief 重置函数指针
     * @param handle 实例句柄
     */
    void (*reset)(fb_handle_t handle);

} fb_type_info_t;

/**
 * @brief 注册功能块类型
 * @param type_info 类型信息
 * @return 错误码
 */
plcopen_error_t fb_register_type(const fb_type_info_t* type_info);

/**
 * @brief 创建功能块实例
 * @param type_name 类型名称
 * @param[out] handle 输出实例句柄
 * @return 错误码
 */
plcopen_error_t fb_create(const char* type_name, fb_handle_t* handle);

/**
 * @brief 销毁功能块实例
 * @param handle 实例句柄
 */
void fb_destroy(fb_handle_t handle);

#endif /* PLCOPEN_FB_COMMON_H */
```

## PID功能块 (fb_pid.h)

```c
#ifndef PLCOPEN_FB_PID_H
#define PLCOPEN_FB_PID_H

#include "fb_common.h"
#include "error.h"

/**
 * @brief PID功能块参数
 */
typedef struct {
    double kp;        /**< 比例增益 */
    double ki;        /**< 积分增益 */
    double kd;        /**< 微分增益 */
    double out_min;   /**< 输出下限 */
    double out_max;   /**< 输出上限 */
    double dt;        /**< 采样周期（秒） */
} pid_params_t;

/**
 * @brief PID功能块输入
 */
typedef struct {
    double setpoint;  /**< 设定值 */
    double pv;        /**< 过程值 */
} pid_input_t;

/**
 * @brief PID功能块输出
 */
typedef struct {
    double output;    /**< 控制输出 */
    double error;     /**< 当前偏差 */
    bool saturated;   /**< 是否限幅 */
} pid_output_t;

/**
 * @brief PID功能块内部状态
 */
typedef struct {
    double integral;     /**< 积分累积 */
    double prev_error;   /**< 上一次偏差 */
    double prev_output;  /**< 上一次输出 */
} pid_state_t;

/**
 * @brief PID功能块实例
 */
typedef struct {
    pid_params_t params;  /**< 参数 */
    pid_state_t state;    /**< 内部状态 */
    pid_output_t output;  /**< 输出 */
} pid_instance_t;

/**
 * @brief 初始化PID实例（使用默认参数）
 * @param pid PID实例指针
 * @return 错误码
 */
plcopen_error_t pid_init(pid_instance_t* pid);

/**
 * @brief 使用指定参数初始化PID实例
 * @param pid PID实例指针
 * @param params 参数
 * @return 错误码
 */
plcopen_error_t pid_init_with_params(pid_instance_t* pid, const pid_params_t* params);

/**
 * @brief 执行一步PID计算
 * @param pid PID实例指针
 * @param input 输入
 * @return 错误码
 */
plcopen_error_t pid_execute(pid_instance_t* pid, const pid_input_t* input);

/**
 * @brief 重置PID内部状态
 * @param pid PID实例指针
 */
void pid_reset(pid_instance_t* pid);

/**
 * @brief 获取PID输出
 * @param pid PID实例指针
 * @param[out] output 输出结构
 */
void pid_get_output(const pid_instance_t* pid, pid_output_t* output);

/**
 * @brief 设置PID参数
 * @param pid PID实例指针
 * @param params 新参数
 * @return 错误码
 */
plcopen_error_t pid_set_params(pid_instance_t* pid, const pid_params_t* params);

/**
 * @brief 获取PID状态（用于热重载）
 * @param pid PID实例指针
 * @param[out] state 状态结构
 */
void pid_get_state(const pid_instance_t* pid, pid_state_t* state);

/**
 * @brief 恢复PID状态（用于热重载）
 * @param pid PID实例指针
 * @param state 状态结构
 */
void pid_set_state(pid_instance_t* pid, const pid_state_t* state);

/**
 * @brief 获取默认PID参数
 * @return 默认参数结构
 */
pid_params_t pid_default_params(void);

#endif /* PLCOPEN_FB_PID_H */
```

## 一阶惯性功能块 (fb_first_order.h)

```c
#ifndef PLCOPEN_FB_FIRST_ORDER_H
#define PLCOPEN_FB_FIRST_ORDER_H

#include "fb_common.h"
#include "error.h"

/**
 * @brief 一阶惯性功能块参数
 */
typedef struct {
    double k;    /**< 增益 */
    double t;    /**< 时间常数（秒） */
    double dt;   /**< 采样周期（秒） */
} first_order_params_t;

/**
 * @brief 一阶惯性功能块状态
 */
typedef struct {
    double prev_output;  /**< 上一次输出 */
} first_order_state_t;

/**
 * @brief 一阶惯性功能块实例
 */
typedef struct {
    first_order_params_t params;  /**< 参数 */
    first_order_state_t state;    /**< 内部状态 */
    double output;                /**< 当前输出 */
} first_order_instance_t;

/**
 * @brief 初始化一阶惯性实例
 * @param fo 实例指针
 * @return 错误码
 */
plcopen_error_t first_order_init(first_order_instance_t* fo);

/**
 * @brief 使用指定参数初始化一阶惯性实例
 * @param fo 实例指针
 * @param params 参数
 * @return 错误码
 */
plcopen_error_t first_order_init_with_params(
    first_order_instance_t* fo,
    const first_order_params_t* params
);

/**
 * @brief 执行一步滤波计算
 * @param fo 实例指针
 * @param input 输入值
 * @return 错误码
 */
plcopen_error_t first_order_execute(first_order_instance_t* fo, double input);

/**
 * @brief 重置一阶惯性内部状态
 * @param fo 实例指针
 * @param initial_value 初始输出值
 */
void first_order_reset(first_order_instance_t* fo, double initial_value);

/**
 * @brief 获取一阶惯性输出
 * @param fo 实例指针
 * @return 当前输出值
 */
double first_order_get_output(const first_order_instance_t* fo);

/**
 * @brief 设置参数
 * @param fo 实例指针
 * @param params 新参数
 * @return 错误码
 */
plcopen_error_t first_order_set_params(
    first_order_instance_t* fo,
    const first_order_params_t* params
);

/**
 * @brief 获取状态（用于热重载）
 * @param fo 实例指针
 * @param[out] state 状态结构
 */
void first_order_get_state(
    const first_order_instance_t* fo,
    first_order_state_t* state
);

/**
 * @brief 恢复状态（用于热重载）
 * @param fo 实例指针
 * @param state 状态结构
 */
void first_order_set_state(
    first_order_instance_t* fo,
    const first_order_state_t* state
);

/**
 * @brief 获取默认参数
 * @return 默认参数结构
 */
first_order_params_t first_order_default_params(void);

#endif /* PLCOPEN_FB_FIRST_ORDER_H */
```

## 运行时API (runtime.h)

```c
#ifndef PLCOPEN_RUNTIME_H
#define PLCOPEN_RUNTIME_H

#include "error.h"
#include <stdbool.h>

/**
 * @brief 运行时配置
 */
typedef struct {
    const char* script_dir;    /**< 脚本目录 */
    double scan_interval;      /**< 目录扫描周期（秒） */
    double cycle_time;         /**< 脚本执行周期（秒） */
    bool debug_enabled;        /**< 是否启用调试 */
    int debug_port;            /**< 调试端口 */
    const char* log_dir;       /**< 日志目录 */
} runtime_config_t;

/**
 * @brief 运行时状态
 */
typedef enum {
    RUNTIME_STATE_INIT,      /**< 初始化中 */
    RUNTIME_STATE_RUNNING,   /**< 运行中 */
    RUNTIME_STATE_STOPPING,  /**< 停止中 */
    RUNTIME_STATE_STOPPED,   /**< 已停止 */
} runtime_state_t;

/**
 * @brief 初始化运行时
 * @param config 配置（NULL使用默认配置）
 * @return 错误码
 */
plcopen_error_t runtime_init(const runtime_config_t* config);

/**
 * @brief 启动运行时
 * @return 错误码
 */
plcopen_error_t runtime_start(void);

/**
 * @brief 停止运行时
 * @return 错误码
 */
plcopen_error_t runtime_stop(void);

/**
 * @brief 清理运行时
 */
void runtime_cleanup(void);

/**
 * @brief 获取运行时状态
 * @return 当前状态
 */
runtime_state_t runtime_get_state(void);

/**
 * @brief 获取默认配置
 * @return 默认配置结构
 */
runtime_config_t runtime_default_config(void);

/**
 * @brief 运行一个执行周期（用于集成到外部主循环）
 * @return 错误码
 */
plcopen_error_t runtime_tick(void);

#endif /* PLCOPEN_RUNTIME_H */
```

## 使用示例

```c
#include <plcopen/plcopen.h>
#include <stdio.h>

int main(void) {
    // 初始化运行时
    runtime_config_t config = runtime_default_config();
    config.script_dir = "./scripts";
    config.cycle_time = 0.1;  // 100ms

    plcopen_error_t err = runtime_init(&config);
    if (err != PLCOPEN_OK) {
        printf("运行时初始化失败: %s\n", plcopen_strerror(err));
        return 1;
    }

    // 启动运行时
    err = runtime_start();
    if (err != PLCOPEN_OK) {
        printf("运行时启动失败: %s\n", plcopen_strerror(err));
        runtime_cleanup();
        return 1;
    }

    printf("运行时已启动，按Ctrl+C退出...\n");

    // 主循环（或使用runtime_tick集成到外部循环）
    while (runtime_get_state() == RUNTIME_STATE_RUNNING) {
        // 运行时内部处理脚本执行
        // 这里可以添加其他应用逻辑
    }

    // 清理
    runtime_cleanup();
    return 0;
}
```
