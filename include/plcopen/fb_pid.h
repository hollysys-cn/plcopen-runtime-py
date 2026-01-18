/**
 * @file fb_pid.h
 * @brief PID功能块头文件
 * @version 1.0
 * @date 2026-01-18
 *
 * 位置式PID控制器实现。
 * 算法: output = Kp * error + Ki * ∫error + Kd * d(error)/dt
 */

#ifndef PLCOPEN_FB_PID_H
#define PLCOPEN_FB_PID_H

#include "fb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 数据结构定义
 * ========================================================================== */

/**
 * @brief PID功能块参数
 */
typedef struct {
    double kp;        /**< 比例增益，必须 >= 0 */
    double ki;        /**< 积分增益，必须 >= 0 */
    double kd;        /**< 微分增益，必须 >= 0 */
    double out_min;   /**< 输出下限 */
    double out_max;   /**< 输出上限，必须 > out_min */
    double dt;        /**< 采样周期（秒），必须 > 0 */
} pid_params_t;

/**
 * @brief PID功能块输入
 */
typedef struct {
    double setpoint;  /**< 设定值 */
    double pv;        /**< 过程值（反馈） */
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

/* ============================================================================
 * 函数接口
 * ========================================================================== */

/**
 * @brief 获取默认PID参数
 * @return 默认参数结构
 */
pid_params_t pid_default_params(void);

/**
 * @brief 验证PID参数
 * @param params 参数
 * @return 错误码
 */
plcopen_error_t pid_validate_params(const pid_params_t* params);

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

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_FB_PID_H */
