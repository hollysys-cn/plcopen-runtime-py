/**
 * @file pid.c
 * @brief PID功能块实现
 * @version 1.0
 * @date 2026-01-18
 *
 * 位置式PID控制器算法实现。
 */

#include "plcopen/fb_pid.h"
#include "common/error.h"
#include "common/log.h"
#include <math.h>
#include <string.h>

/* ============================================================================
 * 默认参数
 * ========================================================================== */

pid_params_t pid_default_params(void)
{
    return (pid_params_t){
        .kp = 1.0,
        .ki = 0.0,
        .kd = 0.0,
        .out_min = -INFINITY,
        .out_max = INFINITY,
        .dt = 0.1
    };
}

/* ============================================================================
 * 参数验证
 * ========================================================================== */

plcopen_error_t pid_validate_params(const pid_params_t* params)
{
    if (params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    /* kp, ki, kd 必须 >= 0 */
    if (params->kp < 0.0) {
        LOG_ERROR("PID参数无效: kp=%f < 0", params->kp);
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    if (params->ki < 0.0) {
        LOG_ERROR("PID参数无效: ki=%f < 0", params->ki);
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    if (params->kd < 0.0) {
        LOG_ERROR("PID参数无效: kd=%f < 0", params->kd);
        return PLCOPEN_ERR_INVALID_PARAM;
    }

    /* dt 必须 > 0 */
    if (params->dt <= 0.0) {
        LOG_ERROR("PID参数无效: dt=%f <= 0", params->dt);
        return PLCOPEN_ERR_INVALID_PARAM;
    }

    /* out_min 必须 < out_max */
    if (params->out_min >= params->out_max) {
        LOG_ERROR("PID参数无效: out_min=%f >= out_max=%f", params->out_min, params->out_max);
        return PLCOPEN_ERR_INVALID_PARAM;
    }

    return PLCOPEN_OK;
}

/* ============================================================================
 * 初始化
 * ========================================================================== */

plcopen_error_t pid_init(pid_instance_t* pid)
{
    if (pid == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    pid->params = pid_default_params();
    memset(&pid->state, 0, sizeof(pid_state_t));
    memset(&pid->output, 0, sizeof(pid_output_t));

    LOG_DEBUG("PID实例初始化完成（默认参数）");
    return PLCOPEN_OK;
}

plcopen_error_t pid_init_with_params(pid_instance_t* pid, const pid_params_t* params)
{
    if (pid == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    plcopen_error_t err = pid_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    pid->params = *params;
    memset(&pid->state, 0, sizeof(pid_state_t));
    memset(&pid->output, 0, sizeof(pid_output_t));

    LOG_DEBUG("PID实例初始化完成: Kp=%f, Ki=%f, Kd=%f", params->kp, params->ki, params->kd);
    return PLCOPEN_OK;
}

/* ============================================================================
 * 执行计算
 * ========================================================================== */

plcopen_error_t pid_execute(pid_instance_t* pid, const pid_input_t* input)
{
    if (pid == NULL || input == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    /* 检查输入值有效性 */
    if (PLCOPEN_IS_NAN(input->setpoint) || PLCOPEN_IS_NAN(input->pv)) {
        LOG_WARN("PID输入包含NaN值");
        return PLCOPEN_ERR_NAN;
    }
    if (PLCOPEN_IS_INF(input->setpoint) || PLCOPEN_IS_INF(input->pv)) {
        LOG_WARN("PID输入包含无穷值");
        return PLCOPEN_ERR_INF;
    }

    const pid_params_t* p = &pid->params;
    pid_state_t* s = &pid->state;

    /* 计算偏差 */
    double error = input->setpoint - input->pv;

    /* 积分项 */
    s->integral += error * p->dt;

    /* 微分项 */
    double derivative = (error - s->prev_error) / p->dt;

    /* PID输出 */
    double output = p->kp * error + p->ki * s->integral + p->kd * derivative;

    /* 输出限幅 */
    bool saturated = false;
    if (output > p->out_max) {
        output = p->out_max;
        saturated = true;
    } else if (output < p->out_min) {
        output = p->out_min;
        saturated = true;
    }

    /* 更新状态 */
    s->prev_error = error;
    s->prev_output = output;

    /* 更新输出 */
    pid->output.output = output;
    pid->output.error = error;
    pid->output.saturated = saturated;

    return PLCOPEN_OK;
}

/* ============================================================================
 * 重置
 * ========================================================================== */

void pid_reset(pid_instance_t* pid)
{
    if (pid == NULL) {
        return;
    }

    memset(&pid->state, 0, sizeof(pid_state_t));
    memset(&pid->output, 0, sizeof(pid_output_t));

    LOG_DEBUG("PID实例已重置");
}

/* ============================================================================
 * 输出获取
 * ========================================================================== */

void pid_get_output(const pid_instance_t* pid, pid_output_t* output)
{
    if (pid == NULL || output == NULL) {
        return;
    }
    *output = pid->output;
}

/* ============================================================================
 * 参数设置
 * ========================================================================== */

plcopen_error_t pid_set_params(pid_instance_t* pid, const pid_params_t* params)
{
    if (pid == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    plcopen_error_t err = pid_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    pid->params = *params;
    LOG_DEBUG("PID参数已更新: Kp=%f, Ki=%f, Kd=%f", params->kp, params->ki, params->kd);
    return PLCOPEN_OK;
}

/* ============================================================================
 * 状态保存/恢复（热重载支持）
 * ========================================================================== */

void pid_get_state(const pid_instance_t* pid, pid_state_t* state)
{
    if (pid == NULL || state == NULL) {
        return;
    }
    *state = pid->state;
}

void pid_set_state(pid_instance_t* pid, const pid_state_t* state)
{
    if (pid == NULL || state == NULL) {
        return;
    }
    pid->state = *state;
    LOG_DEBUG("PID状态已恢复: integral=%f, prev_error=%f", state->integral, state->prev_error);
}
