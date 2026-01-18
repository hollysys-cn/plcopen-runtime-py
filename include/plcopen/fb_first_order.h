/**
 * @file fb_first_order.h
 * @brief 一阶惯性功能块头文件
 * @version 1.0
 * @date 2026-01-18
 *
 * 一阶惯性（一阶滞后）滤波器实现。
 * 传递函数: G(s) = K / (Ts + 1)
 * 离散化: y[n] = alpha * K * x[n] + (1-alpha) * y[n-1]
 *         alpha = dt / (T + dt)
 */

#ifndef PLCOPEN_FB_FIRST_ORDER_H
#define PLCOPEN_FB_FIRST_ORDER_H

#include "fb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 数据结构定义
 * ========================================================================== */

/**
 * @brief 一阶惯性功能块参数
 */
typedef struct {
    double k;    /**< 增益 */
    double t;    /**< 时间常数（秒），必须 > 0 */
    double dt;   /**< 采样周期（秒），必须 > 0 */
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

/* ============================================================================
 * 函数接口
 * ========================================================================== */

/**
 * @brief 获取默认参数
 * @return 默认参数结构
 */
first_order_params_t first_order_default_params(void);

/**
 * @brief 验证参数
 * @param params 参数
 * @return 错误码
 */
plcopen_error_t first_order_validate_params(const first_order_params_t* params);

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

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_FB_FIRST_ORDER_H */
