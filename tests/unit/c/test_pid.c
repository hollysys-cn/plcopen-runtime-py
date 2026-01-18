/**
 * @file test_pid.c
 * @brief PID功能块C单元测试
 * @version 1.0
 * @date 2026-01-18
 *
 * 使用Unity测试框架
 */

#include "unity.h"
#include "plcopen/fb_pid.h"
#include <math.h>

/* ============================================================================
 * 测试夹具
 * ========================================================================== */

static pid_instance_t pid;

void setUp(void)
{
    /* 每个测试前重新初始化 */
    pid_init(&pid);
}

void tearDown(void)
{
    /* 测试后清理（如需要） */
}

/* ============================================================================
 * 默认参数测试
 * ========================================================================== */

void test_pid_default_params(void)
{
    pid_params_t params = pid_default_params();

    TEST_ASSERT_EQUAL_DOUBLE(1.0, params.kp);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, params.ki);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, params.kd);
    TEST_ASSERT_EQUAL_DOUBLE(0.1, params.dt);
    TEST_ASSERT_TRUE(isinf(params.out_min) && params.out_min < 0);
    TEST_ASSERT_TRUE(isinf(params.out_max) && params.out_max > 0);
}

void test_pid_init_with_default_params(void)
{
    TEST_ASSERT_EQUAL(PLCOPEN_OK, pid_init(&pid));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, pid.params.kp);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.integral);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.prev_error);
}

/* ============================================================================
 * 参数验证测试
 * ========================================================================== */

void test_pid_validate_params_negative_kp(void)
{
    pid_params_t params = pid_default_params();
    params.kp = -1.0;

    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, pid_validate_params(&params));
}

void test_pid_validate_params_negative_ki(void)
{
    pid_params_t params = pid_default_params();
    params.ki = -0.1;

    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, pid_validate_params(&params));
}

void test_pid_validate_params_negative_kd(void)
{
    pid_params_t params = pid_default_params();
    params.kd = -0.1;

    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, pid_validate_params(&params));
}

void test_pid_validate_params_zero_dt(void)
{
    pid_params_t params = pid_default_params();
    params.dt = 0.0;

    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, pid_validate_params(&params));
}

void test_pid_validate_params_invalid_limits(void)
{
    pid_params_t params = pid_default_params();
    params.out_min = 100.0;
    params.out_max = 50.0;  /* min > max */

    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, pid_validate_params(&params));
}

void test_pid_validate_params_valid(void)
{
    pid_params_t params = {
        .kp = 2.0,
        .ki = 0.5,
        .kd = 0.1,
        .out_min = 0.0,
        .out_max = 100.0,
        .dt = 0.1
    };

    TEST_ASSERT_EQUAL(PLCOPEN_OK, pid_validate_params(&params));
}

/* ============================================================================
 * 执行测试 - 比例控制
 * ========================================================================== */

void test_pid_execute_proportional_only(void)
{
    pid_params_t params = {
        .kp = 2.0,
        .ki = 0.0,
        .kd = 0.0,
        .out_min = -INFINITY,
        .out_max = INFINITY,
        .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    pid_input_t input = {.setpoint = 100.0, .pv = 80.0};
    TEST_ASSERT_EQUAL(PLCOPEN_OK, pid_execute(&pid, &input));

    /* error = 100 - 80 = 20, output = 2.0 * 20 = 40 */
    TEST_ASSERT_EQUAL_DOUBLE(20.0, pid.output.error);
    TEST_ASSERT_EQUAL_DOUBLE(40.0, pid.output.output);
    TEST_ASSERT_FALSE(pid.output.saturated);
}

/* ============================================================================
 * 执行测试 - 积分控制
 * ========================================================================== */

void test_pid_execute_integral_accumulation(void)
{
    pid_params_t params = {
        .kp = 0.0,
        .ki = 1.0,
        .kd = 0.0,
        .out_min = -INFINITY,
        .out_max = INFINITY,
        .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    pid_input_t input = {.setpoint = 100.0, .pv = 80.0};

    /* 第一次执行: integral = 20 * 0.1 = 2, output = 1.0 * 2 = 2 */
    pid_execute(&pid, &input);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 2.0, pid.output.output);

    /* 第二次执行: integral = 2 + 20 * 0.1 = 4, output = 4 */
    pid_execute(&pid, &input);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 4.0, pid.output.output);

    /* 第三次执行: integral = 4 + 20 * 0.1 = 6, output = 6 */
    pid_execute(&pid, &input);
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 6.0, pid.output.output);
}

/* ============================================================================
 * 执行测试 - 微分控制
 * ========================================================================== */

void test_pid_execute_derivative(void)
{
    pid_params_t params = {
        .kp = 0.0,
        .ki = 0.0,
        .kd = 1.0,
        .out_min = -INFINITY,
        .out_max = INFINITY,
        .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    /* 第一次执行: prev_error = 0, error = 20 */
    pid_input_t input1 = {.setpoint = 100.0, .pv = 80.0};
    pid_execute(&pid, &input1);
    /* derivative = (20 - 0) / 0.1 = 200, output = 1.0 * 200 = 200 */
    TEST_ASSERT_DOUBLE_WITHIN(0.001, 200.0, pid.output.output);

    /* 第二次执行: prev_error = 20, error = 10 */
    pid_input_t input2 = {.setpoint = 100.0, .pv = 90.0};
    pid_execute(&pid, &input2);
    /* derivative = (10 - 20) / 0.1 = -100, output = 1.0 * -100 = -100 */
    TEST_ASSERT_DOUBLE_WITHIN(0.001, -100.0, pid.output.output);
}

/* ============================================================================
 * 执行测试 - 输出限幅
 * ========================================================================== */

void test_pid_execute_output_saturation_high(void)
{
    pid_params_t params = {
        .kp = 10.0,
        .ki = 0.0,
        .kd = 0.0,
        .out_min = 0.0,
        .out_max = 100.0,
        .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    /* error = 50, output = 10 * 50 = 500, 但限幅到100 */
    pid_input_t input = {.setpoint = 100.0, .pv = 50.0};
    pid_execute(&pid, &input);

    TEST_ASSERT_EQUAL_DOUBLE(100.0, pid.output.output);
    TEST_ASSERT_TRUE(pid.output.saturated);
}

void test_pid_execute_output_saturation_low(void)
{
    pid_params_t params = {
        .kp = 10.0,
        .ki = 0.0,
        .kd = 0.0,
        .out_min = 0.0,
        .out_max = 100.0,
        .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    /* error = -50, output = 10 * -50 = -500, 但限幅到0 */
    pid_input_t input = {.setpoint = 50.0, .pv = 100.0};
    pid_execute(&pid, &input);

    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.output.output);
    TEST_ASSERT_TRUE(pid.output.saturated);
}

/* ============================================================================
 * 执行测试 - NaN/Inf检测
 * ========================================================================== */

void test_pid_execute_nan_input(void)
{
    pid_input_t input = {.setpoint = NAN, .pv = 80.0};
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NAN, pid_execute(&pid, &input));
}

void test_pid_execute_inf_input(void)
{
    pid_input_t input = {.setpoint = INFINITY, .pv = 80.0};
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INF, pid_execute(&pid, &input));
}

/* ============================================================================
 * 重置测试
 * ========================================================================== */

void test_pid_reset(void)
{
    pid_input_t input = {.setpoint = 100.0, .pv = 80.0};

    /* 执行几次累积状态 */
    pid_execute(&pid, &input);
    pid_execute(&pid, &input);
    pid_execute(&pid, &input);

    TEST_ASSERT_TRUE(pid.state.integral != 0.0);

    /* 重置 */
    pid_reset(&pid);

    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.integral);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.prev_error);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.prev_output);
}

/* ============================================================================
 * 状态保存/恢复测试（热重载）
 * ========================================================================== */

void test_pid_get_set_state(void)
{
    pid_input_t input = {.setpoint = 100.0, .pv = 80.0};

    /* 执行几次累积状态 */
    pid_execute(&pid, &input);
    pid_execute(&pid, &input);

    /* 保存状态 */
    pid_state_t saved_state;
    pid_get_state(&pid, &saved_state);

    /* 重置 */
    pid_reset(&pid);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, pid.state.integral);

    /* 恢复状态 */
    pid_set_state(&pid, &saved_state);
    TEST_ASSERT_EQUAL_DOUBLE(saved_state.integral, pid.state.integral);
    TEST_ASSERT_EQUAL_DOUBLE(saved_state.prev_error, pid.state.prev_error);
}

/* ============================================================================
 * 空指针测试
 * ========================================================================== */

void test_pid_init_null_ptr(void)
{
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, pid_init(NULL));
}

void test_pid_execute_null_ptr(void)
{
    pid_input_t input = {.setpoint = 100.0, .pv = 80.0};
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, pid_execute(NULL, &input));
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, pid_execute(&pid, NULL));
}

/* ============================================================================
 * 主函数
 * ========================================================================== */

int main(void)
{
    UNITY_BEGIN();

    /* 默认参数测试 */
    RUN_TEST(test_pid_default_params);
    RUN_TEST(test_pid_init_with_default_params);

    /* 参数验证测试 */
    RUN_TEST(test_pid_validate_params_negative_kp);
    RUN_TEST(test_pid_validate_params_negative_ki);
    RUN_TEST(test_pid_validate_params_negative_kd);
    RUN_TEST(test_pid_validate_params_zero_dt);
    RUN_TEST(test_pid_validate_params_invalid_limits);
    RUN_TEST(test_pid_validate_params_valid);

    /* 执行测试 */
    RUN_TEST(test_pid_execute_proportional_only);
    RUN_TEST(test_pid_execute_integral_accumulation);
    RUN_TEST(test_pid_execute_derivative);
    RUN_TEST(test_pid_execute_output_saturation_high);
    RUN_TEST(test_pid_execute_output_saturation_low);
    RUN_TEST(test_pid_execute_nan_input);
    RUN_TEST(test_pid_execute_inf_input);

    /* 重置测试 */
    RUN_TEST(test_pid_reset);

    /* 状态保存/恢复测试 */
    RUN_TEST(test_pid_get_set_state);

    /* 空指针测试 */
    RUN_TEST(test_pid_init_null_ptr);
    RUN_TEST(test_pid_execute_null_ptr);

    return UNITY_END();
}
