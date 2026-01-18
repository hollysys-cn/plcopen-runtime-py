/**
 * @file fb_template.c
 * @brief 功能块模板
 * @version 1.0
 * @date 2026-01-18
 *
 * 复制此文件作为新功能块的起点。
 * 替换 <your_fb>、<YourFB> 为实际名称。
 */

#include "plcopen/fb_common.h"
#include <math.h>
#include <string.h>

/* ============================================================================
 * 类型定义
 * ========================================================================== */

/**
 * @brief 参数结构体
 */
typedef struct {
    double param1;      /**< 参数1 */
    double param2;      /**< 参数2 */
    double dt;          /**< 采样周期（秒） */
} template_params_t;

/**
 * @brief 状态结构体
 */
typedef struct {
    double state1;      /**< 状态变量1 */
    double prev_input;  /**< 上一次输入 */
} template_state_t;

/**
 * @brief 功能块实例
 */
typedef struct {
    template_params_t params;   /**< 参数 */
    template_state_t state;     /**< 状态 */
    double output;              /**< 输出 */
} template_instance_t;

/* ============================================================================
 * 函数实现
 * ========================================================================== */

/**
 * @brief 验证参数
 */
plcopen_error_t template_validate_params(const template_params_t *params)
{
    if (params == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    /* 采样周期必须为正 */
    if (params->dt <= 0.0) {
        return PLCOPEN_ERR_PARAM;
    }

    /* 添加其他参数验证... */

    return PLCOPEN_OK;
}

/**
 * @brief 初始化（默认参数）
 */
plcopen_error_t template_init(template_instance_t *inst)
{
    if (inst == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    template_params_t defaults = {
        .param1 = 1.0,
        .param2 = 1.0,
        .dt = 0.1
    };

    inst->params = defaults;
    memset(&inst->state, 0, sizeof(template_state_t));
    inst->output = 0.0;

    return PLCOPEN_OK;
}

/**
 * @brief 初始化（自定义参数）
 */
plcopen_error_t template_init_with_params(
    template_instance_t *inst,
    const template_params_t *params)
{
    if (inst == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    plcopen_error_t err = template_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    inst->params = *params;
    memset(&inst->state, 0, sizeof(template_state_t));
    inst->output = 0.0;

    return PLCOPEN_OK;
}

/**
 * @brief 执行一步计算
 */
plcopen_error_t template_execute(template_instance_t *inst, double input)
{
    if (inst == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    /* 输入验证 */
    if (isnan(input)) {
        return PLCOPEN_ERR_NAN;
    }
    if (isinf(input)) {
        return PLCOPEN_ERR_INF;
    }

    /* ========================================
     * TODO: 在这里实现您的算法
     * ======================================== */

    /* 示例：简单的增益 + 一阶滤波 */
    double alpha = inst->params.dt / (inst->params.param2 + inst->params.dt);
    double target = inst->params.param1 * input;
    inst->output = alpha * target + (1.0 - alpha) * inst->output;

    /* 更新状态 */
    inst->state.prev_input = input;

    return PLCOPEN_OK;
}

/**
 * @brief 重置状态
 */
void template_reset(template_instance_t *inst, double initial_value)
{
    if (inst == NULL) return;

    memset(&inst->state, 0, sizeof(template_state_t));
    inst->output = initial_value;
}

/**
 * @brief 获取状态（用于热重载）
 */
void template_get_state(const template_instance_t *inst, template_state_t *state)
{
    if (inst == NULL || state == NULL) return;
    *state = inst->state;
}

/**
 * @brief 设置状态（用于热重载）
 */
void template_set_state(template_instance_t *inst, const template_state_t *state)
{
    if (inst == NULL || state == NULL) return;
    inst->state = *state;
}

/* ============================================================================
 * 单元测试（可选）
 * ========================================================================== */

#ifdef TEMPLATE_UNIT_TEST

#include <stdio.h>
#include <assert.h>

int main(void)
{
    template_instance_t fb;
    plcopen_error_t err;

    /* 测试初始化 */
    err = template_init(&fb);
    assert(err == PLCOPEN_OK);
    printf("✓ 初始化成功\n");

    /* 测试执行 */
    err = template_execute(&fb, 10.0);
    assert(err == PLCOPEN_OK);
    printf("✓ 执行成功，输出: %f\n", fb.output);

    /* 测试 NaN 输入 */
    err = template_execute(&fb, NAN);
    assert(err == PLCOPEN_ERR_NAN);
    printf("✓ NaN 检测成功\n");

    /* 测试重置 */
    template_reset(&fb, 0.0);
    assert(fb.output == 0.0);
    printf("✓ 重置成功\n");

    printf("\n所有测试通过！\n");
    return 0;
}

#endif /* TEMPLATE_UNIT_TEST */
