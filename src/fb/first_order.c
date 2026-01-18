/**
 * @file first_order.c
 * @brief 一阶惯性功能块实现
 * @version 1.0
 * @date 2026-01-18
 *
 * 一阶惯性（一阶滞后）滤波器算法实现。
 * 传递函数: G(s) = K / (Ts + 1)
 */

#include "plcopen/fb_first_order.h"
#include "common/error.h"
#include "common/log.h"
#include <math.h>
#include <string.h>

/* ============================================================================
 * 默认参数
 * ========================================================================== */

first_order_params_t first_order_default_params(void)
{
    return (first_order_params_t){
        .k = 1.0,
        .t = 1.0,
        .dt = 0.1
    };
}

/* ============================================================================
 * 参数验证
 * ========================================================================== */

plcopen_error_t first_order_validate_params(const first_order_params_t* params)
{
    if (params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    /* t 必须 > 0 */
    if (params->t <= 0.0) {
        LOG_ERROR("一阶惯性参数无效: t=%f <= 0", params->t);
        return PLCOPEN_ERR_INVALID_PARAM;
    }

    /* dt 必须 > 0 */
    if (params->dt <= 0.0) {
        LOG_ERROR("一阶惯性参数无效: dt=%f <= 0", params->dt);
        return PLCOPEN_ERR_INVALID_PARAM;
    }

    return PLCOPEN_OK;
}

/* ============================================================================
 * 初始化
 * ========================================================================== */

plcopen_error_t first_order_init(first_order_instance_t* fo)
{
    if (fo == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    fo->params = first_order_default_params();
    memset(&fo->state, 0, sizeof(first_order_state_t));
    fo->output = 0.0;

    LOG_DEBUG("一阶惯性实例初始化完成（默认参数）");
    return PLCOPEN_OK;
}

plcopen_error_t first_order_init_with_params(
    first_order_instance_t* fo,
    const first_order_params_t* params)
{
    if (fo == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    plcopen_error_t err = first_order_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    fo->params = *params;
    memset(&fo->state, 0, sizeof(first_order_state_t));
    fo->output = 0.0;

    LOG_DEBUG("一阶惯性实例初始化完成: K=%f, T=%f", params->k, params->t);
    return PLCOPEN_OK;
}

/* ============================================================================
 * 执行计算
 * ========================================================================== */

plcopen_error_t first_order_execute(first_order_instance_t* fo, double input)
{
    if (fo == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    /* 检查输入值有效性 */
    if (PLCOPEN_IS_NAN(input)) {
        LOG_WARN("一阶惯性输入包含NaN值");
        return PLCOPEN_ERR_NAN;
    }
    if (PLCOPEN_IS_INF(input)) {
        LOG_WARN("一阶惯性输入包含无穷值");
        return PLCOPEN_ERR_INF;
    }

    const first_order_params_t* p = &fo->params;
    first_order_state_t* s = &fo->state;

    /* 离散化计算
     * alpha = dt / (T + dt)
     * output = alpha * K * input + (1 - alpha) * prev_output
     */
    double alpha = p->dt / (p->t + p->dt);
    double output = alpha * p->k * input + (1.0 - alpha) * s->prev_output;

    /* 更新状态 */
    s->prev_output = output;
    fo->output = output;

    return PLCOPEN_OK;
}

/* ============================================================================
 * 重置
 * ========================================================================== */

void first_order_reset(first_order_instance_t* fo, double initial_value)
{
    if (fo == NULL) {
        return;
    }

    fo->state.prev_output = initial_value;
    fo->output = initial_value;

    LOG_DEBUG("一阶惯性实例已重置: 初始值=%f", initial_value);
}

/* ============================================================================
 * 输出获取
 * ========================================================================== */

double first_order_get_output(const first_order_instance_t* fo)
{
    if (fo == NULL) {
        return 0.0;
    }
    return fo->output;
}

/* ============================================================================
 * 参数设置
 * ========================================================================== */

plcopen_error_t first_order_set_params(
    first_order_instance_t* fo,
    const first_order_params_t* params)
{
    if (fo == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }

    plcopen_error_t err = first_order_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    fo->params = *params;
    LOG_DEBUG("一阶惯性参数已更新: K=%f, T=%f", params->k, params->t);
    return PLCOPEN_OK;
}

/* ============================================================================
 * 状态保存/恢复（热重载支持）
 * ========================================================================== */

void first_order_get_state(
    const first_order_instance_t* fo,
    first_order_state_t* state)
{
    if (fo == NULL || state == NULL) {
        return;
    }
    *state = fo->state;
}

void first_order_set_state(
    first_order_instance_t* fo,
    const first_order_state_t* state)
{
    if (fo == NULL || state == NULL) {
        return;
    }
    fo->state = *state;
    fo->output = state->prev_output;
    LOG_DEBUG("一阶惯性状态已恢复: prev_output=%f", state->prev_output);
}
