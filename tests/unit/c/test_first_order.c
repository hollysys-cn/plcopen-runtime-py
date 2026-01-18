/**
 * @file test_first_order.c
 * @brief 一阶惯性功能块单元测试
 * @version 1.0
 * @date 2026-01-18
 */

#include "unity.h"
#include "plcopen/fb_first_order.h"
#include <math.h>

static first_order_instance_t fo;

void setUp(void)
{
    memset(&fo, 0, sizeof(fo));
}

void tearDown(void)
{
    /* Nothing to clean up */
}

/* ============================================================================
 * 参数验证测试
 * ========================================================================== */

void test_default_params(void)
{
    first_order_params_t params = {
        .k = 1.0,
        .t = 1.0,
        .dt = 0.1
    };

    plcopen_error_t err = first_order_init_with_params(&fo, &params);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, fo.params.k);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 1.0, fo.params.t);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.1, fo.params.dt);
}

void test_invalid_time_constant_zero(void)
{
    first_order_params_t params = {.k = 1.0, .t = 0.0, .dt = 0.1};
    plcopen_error_t err = first_order_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_PARAM, err);
}

void test_invalid_time_constant_negative(void)
{
    first_order_params_t params = {.k = 1.0, .t = -1.0, .dt = 0.1};
    plcopen_error_t err = first_order_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_PARAM, err);
}

void test_invalid_dt_zero(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.0};
    plcopen_error_t err = first_order_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_PARAM, err);
}

void test_invalid_dt_negative(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = -0.1};
    plcopen_error_t err = first_order_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_PARAM, err);
}

void test_valid_negative_gain(void)
{
    first_order_params_t params = {.k = -2.0, .t = 1.0, .dt = 0.1};
    plcopen_error_t err = first_order_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err); /* 负增益是允许的 */
}

/* ============================================================================
 * 基本滤波测试
 * ========================================================================== */

void test_step_response_converges(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 阶跃输入 100，运行足够多步使其收敛 */
    double input = 100.0;
    for (int i = 0; i < 100; i++) {
        first_order_execute(&fo, input);
    }

    /* 应该收敛到 K * input = 1.0 * 100 = 100 */
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 100.0, fo.output);
}

void test_step_response_time_constant(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 阶跃输入，在t=T时应该达到63.2%的稳态值 */
    double input = 100.0;
    int steps_to_T = (int)(params.t / params.dt);  /* 10步 */

    for (int i = 0; i < steps_to_T; i++) {
        first_order_execute(&fo, input);
    }

    /* 理论上应该达到 63.2% = 63.2 */
    /* 由于离散化，可能有一些偏差 */
    TEST_ASSERT_DOUBLE_WITHIN(5.0, 63.2, fo.output);
}

void test_gain_scaling(void)
{
    first_order_params_t params = {.k = 2.5, .t = 0.5, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 阶跃输入 40，收敛到 K * 40 = 100 */
    for (int i = 0; i < 100; i++) {
        first_order_execute(&fo, 40.0);
    }

    TEST_ASSERT_DOUBLE_WITHIN(0.1, 100.0, fo.output);
}

void test_zero_input(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    first_order_execute(&fo, 0.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, fo.output);
}

void test_negative_input(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    for (int i = 0; i < 100; i++) {
        first_order_execute(&fo, -50.0);
    }

    TEST_ASSERT_DOUBLE_WITHIN(0.1, -50.0, fo.output);
}

/* ============================================================================
 * 边界条件测试
 * ========================================================================== */

void test_small_time_constant(void)
{
    /* 小时间常数应该快速响应 */
    first_order_params_t params = {.k = 1.0, .t = 0.01, .dt = 0.01};
    first_order_init_with_params(&fo, &params);

    first_order_execute(&fo, 100.0);
    /* alpha = dt/(t+dt) = 0.01/(0.01+0.01) = 0.5 */
    /* output = 0.5 * 1.0 * 100 + 0.5 * 0 = 50 */
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 50.0, fo.output);

    first_order_execute(&fo, 100.0);
    /* output = 0.5 * 100 + 0.5 * 50 = 75 */
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 75.0, fo.output);
}

void test_large_time_constant(void)
{
    /* 大时间常数应该缓慢响应 */
    first_order_params_t params = {.k = 1.0, .t = 100.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    first_order_execute(&fo, 100.0);
    /* alpha = 0.1 / (100 + 0.1) ≈ 0.001 */
    /* output ≈ 0.001 * 100 ≈ 0.1 */
    TEST_ASSERT_TRUE(fo.output < 1.0);
}

void test_nan_input_returns_error(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    plcopen_error_t err = first_order_execute(&fo, NAN);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NAN, err);
}

void test_inf_input_returns_error(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    plcopen_error_t err = first_order_execute(&fo, INFINITY);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INF, err);
}

/* ============================================================================
 * 重置和状态测试
 * ========================================================================== */

void test_reset_to_zero(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 运行几步 */
    for (int i = 0; i < 10; i++) {
        first_order_execute(&fo, 100.0);
    }
    TEST_ASSERT_TRUE(fo.output > 0);

    /* 重置 */
    first_order_reset(&fo, 0.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, fo.output);
}

void test_reset_to_initial_value(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    first_order_reset(&fo, 50.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 50.0, fo.output);

    /* 继续执行应该从50开始滤波 */
    first_order_execute(&fo, 100.0);
    TEST_ASSERT_TRUE(fo.output > 50.0);
    TEST_ASSERT_TRUE(fo.output < 100.0);
}

void test_state_save_restore(void)
{
    first_order_params_t params = {.k = 1.0, .t = 1.0, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 运行几步 */
    for (int i = 0; i < 5; i++) {
        first_order_execute(&fo, 100.0);
    }

    /* 保存状态 */
    first_order_state_t state;
    first_order_get_state(&fo, &state);

    double saved_output = fo.output;

    /* 继续运行 */
    for (int i = 0; i < 5; i++) {
        first_order_execute(&fo, 100.0);
    }

    /* 恢复状态 */
    first_order_set_state(&fo, &state);

    TEST_ASSERT_DOUBLE_WITHIN(0.0001, saved_output, fo.output);
}

/* ============================================================================
 * 连续输入测试
 * ========================================================================== */

void test_varying_input(void)
{
    first_order_params_t params = {.k = 1.0, .t = 0.5, .dt = 0.1};
    first_order_init_with_params(&fo, &params);

    /* 正弦波输入 */
    for (int i = 0; i < 100; i++) {
        double input = 50.0 * sin(0.1 * i) + 50.0;
        first_order_execute(&fo, input);
        /* 输出应该始终有效 */
        TEST_ASSERT_FALSE(isnan(fo.output));
        TEST_ASSERT_FALSE(isinf(fo.output));
    }
}

/* ============================================================================
 * Main
 * ========================================================================== */

int main(void)
{
    UNITY_BEGIN();

    /* 参数验证 */
    RUN_TEST(test_default_params);
    RUN_TEST(test_invalid_time_constant_zero);
    RUN_TEST(test_invalid_time_constant_negative);
    RUN_TEST(test_invalid_dt_zero);
    RUN_TEST(test_invalid_dt_negative);
    RUN_TEST(test_valid_negative_gain);

    /* 基本滤波 */
    RUN_TEST(test_step_response_converges);
    RUN_TEST(test_step_response_time_constant);
    RUN_TEST(test_gain_scaling);
    RUN_TEST(test_zero_input);
    RUN_TEST(test_negative_input);

    /* 边界条件 */
    RUN_TEST(test_small_time_constant);
    RUN_TEST(test_large_time_constant);
    RUN_TEST(test_nan_input_returns_error);
    RUN_TEST(test_inf_input_returns_error);

    /* 重置和状态 */
    RUN_TEST(test_reset_to_zero);
    RUN_TEST(test_reset_to_initial_value);
    RUN_TEST(test_state_save_restore);

    /* 连续输入 */
    RUN_TEST(test_varying_input);

    return UNITY_END();
}
