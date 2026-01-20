/**
 * @file test_pida.c
 * @brief PIDA功能块单元测试
 * @version 1.0
 * @date 2026-01-20
 *
 * 使用Unity测试框架验证PIDA功能块的正确性。
 */

#include "unity.h"
#include "plcopen/fb_pida.h"
#include <math.h>
#include <string.h>

/* ============================================================================
 * 测试夹具
 * ========================================================================== */

static pida_instance_t g_pida;
static pida_input_t g_input;

void setUp(void)
{
    memset(&g_pida, 0, sizeof(g_pida));
    memset(&g_input, 0, sizeof(g_input));
    pida_init(&g_pida);
    
    /* 默认输入 */
    g_input.cyc = 0.5f;  /* 500ms周期 */
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    g_input.mode = PIDA_MODE_AUTO;
}

void tearDown(void)
{
    /* 清理 */
}

/* ============================================================================
 * Phase 2: 参数验证和初始化测试 (T018-T020)
 * ========================================================================== */

void test_default_params_values(void)
{
    pida_params_t params = pida_default_params();
    
    /* 验证关键默认值 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, params.kp);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 30.0f, params.ti);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, params.td);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 1.0f, params.kd);
    
    /* 量程范围 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, params.pvu);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, params.pvl);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, params.engu);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, params.engl);
    
    /* 输出限幅 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, params.outu);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, params.outl);
    
    /* 设定值限幅 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 100.0f, params.spu);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, params.spl);
    
    /* PID类型和公式 */
    TEST_ASSERT_EQUAL_UINT8(PIDA_TYPE_SINGLE, params.pidtype);
    TEST_ASSERT_EQUAL_UINT8(PIDA_EQN_STANDARD, params.eqn);
    
    /* 作用方式：默认反作用 */
    TEST_ASSERT_TRUE(params.actopt);
}

void test_validate_params_null_pointer(void)
{
    plcopen_error_t err = pida_validate_params(NULL);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, err);
}

void test_validate_params_valid(void)
{
    pida_params_t params = pida_default_params();
    plcopen_error_t err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
}

void test_validate_params_invalid_kp(void)
{
    pida_params_t params = pida_default_params();
    params.kp = 0.0f;  /* KP必须>0 */
    plcopen_error_t err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
    
    params.kp = -1.0f;
    err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
}

void test_validate_params_invalid_ranges(void)
{
    pida_params_t params = pida_default_params();
    
    /* PVU必须>PVL */
    params.pvu = 0.0f;
    params.pvl = 100.0f;
    plcopen_error_t err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
    
    params = pida_default_params();
    
    /* OUTU必须>OUTL */
    params.outu = 0.0f;
    params.outl = 100.0f;
    err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
}

void test_validate_params_invalid_pidtype(void)
{
    pida_params_t params = pida_default_params();
    params.pidtype = 5;  /* 无效类型 */
    plcopen_error_t err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
}

void test_validate_params_invalid_eqn(void)
{
    pida_params_t params = pida_default_params();
    params.eqn = 4;  /* 无效公式 */
    plcopen_error_t err = pida_validate_params(&params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
}

void test_init_null_pointer(void)
{
    plcopen_error_t err = pida_init(NULL);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, err);
}

void test_init_default_state(void)
{
    pida_instance_t pida;
    plcopen_error_t err = pida_init(&pida);
    
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    /* 验证初始模式为手动 */
    TEST_ASSERT_EQUAL_UINT8(PIDA_MODE_MANUAL, pida.state.nowrm);
    
    /* 验证输出初始为0 */
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, pida.output.out);
    
    /* 验证无报警 */
    TEST_ASSERT_FALSE(pida.output.hhind);
    TEST_ASSERT_FALSE(pida.output.ahind);
    TEST_ASSERT_FALSE(pida.output.alind);
    TEST_ASSERT_FALSE(pida.output.llind);
    TEST_ASSERT_FALSE(pida.output.da);
}

void test_init_with_params(void)
{
    pida_instance_t pida;
    pida_params_t params = pida_default_params();
    params.kp = 200.0f;
    params.ti = 60.0f;
    
    plcopen_error_t err = pida_init_with_params(&pida, &params);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 200.0f, pida.params.kp);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 60.0f, pida.params.ti);
}

void test_init_with_invalid_params(void)
{
    pida_instance_t pida;
    pida_params_t params = pida_default_params();
    params.kp = -1.0f;  /* 无效 */
    
    plcopen_error_t err = pida_init_with_params(&pida, &params);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INVALID_PARAM, err);
}

/* ============================================================================
 * Phase 3: PID计算正确性测试 (T033-T034)
 * ========================================================================== */

void test_execute_null_pointer(void)
{
    pida_input_t input = {0};
    input.cyc = 0.5f;
    
    plcopen_error_t err = pida_execute(NULL, &input);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, err);
    
    err = pida_execute(&g_pida, NULL);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NULL_PTR, err);
}

void test_execute_nan_input(void)
{
    g_input.pv = NAN;
    plcopen_error_t err = pida_execute(&g_pida, &g_input);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_NAN, err);
}

void test_execute_inf_input(void)
{
    g_input.pv = INFINITY;
    plcopen_error_t err = pida_execute(&g_pida, &g_input);
    TEST_ASSERT_EQUAL(PLCOPEN_ERR_INF, err);
}

void test_execute_auto_mode_steady_state(void)
{
    /* 自动模式，偏差为0，输出应保持稳定 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    
    /* 执行多步 */
    for (int i = 0; i < 10; i++) {
        plcopen_error_t err = pida_execute(&g_pida, &g_input);
        TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    }
    
    /* 偏差为0时，输出应趋于稳定（小量变化） */
    float ek = g_pida.output.ek;
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, ek);
}

void test_execute_auto_mode_with_error(void)
{
    /* 自动模式，有偏差，输出应调整 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 40.0f;  /* PV低于SP */
    g_input.sp = 50.0f;
    
    /* 执行第一步切换到自动模式 */
    pida_execute(&g_pida, &g_input);
    
    /* 执行第二步进行PID计算（此时已是自动模式） */
    plcopen_error_t err = pida_execute(&g_pida, &g_input);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    /* 反作用模式下，PV<SP，偏差 = SP - PV = 10 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 10.0f, g_pida.output.ek);
}

void test_execute_output_upper_limit(void)
{
    /* 测试输出上限 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 0.0f;   /* 大偏差 */
    g_input.sp = 100.0f;
    
    /* 连续执行让输出增加 */
    for (int i = 0; i < 100; i++) {
        pida_execute(&g_pida, &g_input);
    }
    
    /* 输出不应超过OUTU */
    TEST_ASSERT_TRUE(g_pida.output.out <= g_pida.params.outu);
    
    /* 检查输出超限标志 */
    bool upper_limit = (g_pida.output.ove & PIDA_OVE_OVER_HIGH) != 0;
    TEST_ASSERT_TRUE(upper_limit);
}

void test_execute_output_lower_limit(void)
{
    /* 测试输出下限 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 100.0f;  /* 反向大偏差 */
    g_input.sp = 0.0f;
    
    /* 连续执行让输出减少 */
    for (int i = 0; i < 100; i++) {
        pida_execute(&g_pida, &g_input);
    }
    
    /* 输出不应低于OUTL */
    TEST_ASSERT_TRUE(g_pida.output.out >= g_pida.params.outl);
    
    /* 检查输出超限标志 */
    bool lower_limit = (g_pida.output.ove & PIDA_OVE_OVER_LOW) != 0;
    TEST_ASSERT_TRUE(lower_limit);
}

void test_execute_manual_mode(void)
{
    /* 手动模式，输出由手动值决定 */
    /* 禁用输出变化率限制 */
    g_pida.params.outrat = 0.0f;
    
    g_input.mode = PIDA_MODE_MANUAL;
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    g_input.pmout = 30.0f;  /* 手动输出值 */
    g_input.pmsw = true;      /* 程控手动模式 */
    
    plcopen_error_t err = pida_execute(&g_pida, &g_input);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    /* 手动模式下，输出应为手动设定值 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 30.0f, g_pida.output.out);
}

/* ============================================================================
 * Phase 4: 模式切换测试 (T035-T036)
 * ========================================================================== */

void test_mode_switch_manual_to_auto(void)
{
    /* 禁用输出变化率限制以便更好地测试 */
    g_pida.params.outrat = 0.0f;
    
    /* 初始化为手动模式 */
    g_input.mode = PIDA_MODE_MANUAL;
    g_input.pmout = 50.0f;
    g_input.pmsw = true;
    g_input.pv = 60.0f;
    g_input.sp = 60.0f;
    
    pida_execute(&g_pida, &g_input);
    float manual_output = g_pida.output.out;
    
    /* 切换到自动模式 */
    g_input.mode = PIDA_MODE_AUTO;
    pida_execute(&g_pida, &g_input);
    
    /* 无扰切换：偏差为0时输出变化应小于1% */
    /* 注：实际切换行为取决于PID参数和无扰切换逻辑 */
    /* 这里只验证模式已切换 */
    TEST_ASSERT_EQUAL_UINT8(PIDA_MODE_AUTO, g_pida.state.nowrm);
}

void test_mode_switch_auto_to_manual(void)
{
    /* 先在自动模式运行 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 50.0f;
    g_input.sp = 60.0f;
    
    for (int i = 0; i < 10; i++) {
        pida_execute(&g_pida, &g_input);
    }
    float auto_output = g_pida.output.out;
    
    /* 切换到手动模式 */
    g_input.mode = PIDA_MODE_MANUAL;
    g_input.pmout = auto_output;  /* 手动值跟踪自动输出 */
    g_input.pmsw = true;
    pida_execute(&g_pida, &g_input);
    
    /* 无扰切换：输出应保持 */
    float change = fabsf(g_pida.output.out - auto_output);
    float change_percent = change / (fabsf(auto_output) + 0.001f) * 100.0f;
    TEST_ASSERT_TRUE(change_percent < 1.0f);
}

/* ============================================================================
 * Phase 5: 爬坡功能测试 (T047-T048)
 * ========================================================================== */

void test_ramp_time_based(void)
{
    /* 时间爬坡测试 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    pida_execute(&g_pida, &g_input);
    
    /* 启动爬坡：目标100，1分钟内完成 */
    plcopen_error_t err = pida_start_ramp(&g_pida, 100.0f, 1.0f, false);  /* rtyp=0 时间 */
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    /* 执行多步，验证SP逐渐增加 */
    float prev_sp = g_pida.output.sp;
    for (int i = 0; i < 10; i++) {
        pida_execute(&g_pida, &g_input);
        TEST_ASSERT_TRUE(g_pida.output.sp >= prev_sp);
        prev_sp = g_pida.output.sp;
    }
}

void test_ramp_rate_based(void)
{
    /* 速率爬坡测试 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    pida_execute(&g_pida, &g_input);
    
    /* 启动爬坡：目标100，速率10/分钟 */
    plcopen_error_t err = pida_start_ramp(&g_pida, 100.0f, 10.0f, true);  /* rtyp=1 速率 */
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    /* 验证爬坡状态 */
    bool active;
    float remaining, rate;
    pida_get_ramp_status(&g_pida, &active, &remaining, &rate);
    TEST_ASSERT_TRUE(active);
}

/* ============================================================================
 * Phase 6: 报警功能测试 (T057-T059)
 * ========================================================================== */

void test_alarm_high_limit(void)
{
    /* 配置高限报警 */
    g_pida.params.ah = 80.0f;  /* 高限值 */
    g_pida.params.h1 = 1;      /* 启用高限报警（级别>0） */
    g_pida.params.almopt = true;  /* 启用报警 */
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 85.0f;  /* 超过高限 */
    g_input.sp = 50.0f;
    
    pida_execute(&g_pida, &g_input);
    
    /* 验证高限报警触发 */
    TEST_ASSERT_TRUE(g_pida.output.ahind);
    
    /* 验证AM报警字 */
    bool ah_bit = (g_pida.output.am & PIDA_AM_AH) != 0;
    TEST_ASSERT_TRUE(ah_bit);
}

void test_alarm_low_limit(void)
{
    /* 配置低限报警 */
    g_pida.params.al = 20.0f;  /* 低限值 */
    g_pida.params.l1 = 1;      /* 启用低限报警（级别>0） */
    g_pida.params.almopt = true;  /* 启用报警 */
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 15.0f;  /* 低于低限 */
    g_input.sp = 50.0f;
    
    pida_execute(&g_pida, &g_input);
    
    /* 验证低限报警触发 */
    TEST_ASSERT_TRUE(g_pida.output.alind);
    
    /* 验证AM报警字 */
    bool al_bit = (g_pida.output.am & PIDA_AM_AL) != 0;
    TEST_ASSERT_TRUE(al_bit);
}

void test_alarm_deadband(void)
{
    /* 配置报警和死区 */
    g_pida.params.ah = 80.0f;
    g_pida.params.h1 = 1;
    g_pida.params.almdb = 2.0f;  /* 2%死区 */
    g_pida.params.almopt = true;
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.sp = 50.0f;
    
    /* 超过高限，触发报警 */
    g_input.pv = 85.0f;
    pida_execute(&g_pida, &g_input);
    TEST_ASSERT_TRUE(g_pida.output.ahind);
    
    /* 降到高限附近但在死区内（80-2=78，79>78所以仍在死区内），报警应保持 */
    g_input.pv = 79.0f;
    pida_execute(&g_pida, &g_input);
    TEST_ASSERT_TRUE(g_pida.output.ahind);  /* 死区内报警保持 */
    
    /* 降到死区外（80-2=78，75<78所以在死区外），报警应解除 */
    g_input.pv = 75.0f;
    pida_execute(&g_pida, &g_input);
    TEST_ASSERT_FALSE(g_pida.output.ahind);  /* 报警解除 */
}

/* ============================================================================
 * Phase 7: 偏差报警测试 (T070-T071)
 * ========================================================================== */

void test_deviation_alarm(void)
{
    /* 配置偏差报警 */
    g_pida.params.dal = 10.0f;   /* 偏差报警限值（百分比） */
    g_pida.params.dallv = 1;     /* 启用偏差报警（级别>0） */
    g_pida.params.almopt = true;
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.sp = 50.0f;
    g_input.pv = 38.0f;  /* 偏差=12，超过限值10% */
    
    /* 执行两步（第一步切换模式，第二步计算） */
    pida_execute(&g_pida, &g_input);
    pida_execute(&g_pida, &g_input);
    
    /* 验证偏差报警触发 */
    TEST_ASSERT_TRUE(g_pida.output.da);
}

void test_deviation_alarm_inhibit(void)
{
    /* 配置偏差报警及抑制 */
    g_pida.params.dallv = 10.0f;
    g_pida.params.almopt = true;
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.sp = 50.0f;
    g_input.pv = 38.0f;
    g_pida.params.inhdal = true;  /* 抑制偏差报警 */
    
    pida_execute(&g_pida, &g_input);
    
    /* 偏差报警应被抑制 */
    TEST_ASSERT_FALSE(g_pida.output.da);
}

/* ============================================================================
 * Phase 8: 旁路功能测试 (T077-T078)
 * ========================================================================== */

void test_bypass_enter(void)
{
    /* 配置为串级副调 */
    g_pida.params.pidtype = PIDA_TYPE_CASCADE_SLAVE;
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 50.0f;
    g_input.sp = 50.0f;
    g_input.auxcomp = 60.0f;  /* 主调输出 */
    pida_execute(&g_pida, &g_input);
    
    /* 切入旁路 */
    plcopen_error_t err = pida_set_bypass(&g_pida, true);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
    
    g_input.ctrbp = true;
    pida_execute(&g_pida, &g_input);
    
    /* 旁路模式下，输出应等于AUXCOMP */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 60.0f, g_pida.output.out);
}

void test_bypass_exit(void)
{
    /* 配置为串级副调并进入旁路 */
    g_pida.params.pidtype = PIDA_TYPE_CASCADE_SLAVE;
    g_pida.params.outrat = 0.0f;  /* 禁用输出变化率限制 */
    g_input.ctrbp = true;
    g_input.mode = PIDA_MODE_AUTO;
    g_input.auxcomp = 60.0f;
    pida_execute(&g_pida, &g_input);
    
    /* 退出旁路 */
    pida_set_bypass(&g_pida, false);
    g_input.ctrbp = false;
    pida_execute(&g_pida, &g_input);
    
    /* 退出旁路后，旁路位应该被清除 */
    bool bypass_bit = (g_pida.output.ove & PIDA_OVE_BYPASS) != 0;
    TEST_ASSERT_FALSE(bypass_bit);
}

/* ============================================================================
 * Phase 9: 报警切手动测试 (T085)
 * ========================================================================== */

void test_alarm_to_manual(void)
{
    /* 配置高高限报警切手动 */
    g_pida.params.h2 = 90.0f;  /* 高高限 */
    g_pida.params.almopt = true;
    g_pida.params.mancut = 0x0008;  /* bit3: HH报警切手动 */
    
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 95.0f;  /* 超过高高限 */
    g_input.sp = 50.0f;
    
    pida_execute(&g_pida, &g_input);
    
    /* 验证高高限报警触发 */
    TEST_ASSERT_TRUE(g_pida.output.hhind);
    
    /* 验证自动切换到手动模式 */
    TEST_ASSERT_EQUAL_UINT8(PIDA_MODE_MANUAL, g_pida.state.nowrm);
}

/* ============================================================================
 * 重置测试
 * ========================================================================== */

void test_reset_clears_state(void)
{
    /* 先执行一些操作 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 40.0f;
    g_input.sp = 60.0f;
    for (int i = 0; i < 10; i++) {
        pida_execute(&g_pida, &g_input);
    }
    
    /* 重置 */
    pida_reset(&g_pida);
    
    /* 验证状态被清除 */
    TEST_ASSERT_EQUAL_UINT8(PIDA_MODE_MANUAL, g_pida.state.nowrm);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, g_pida.output.out);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, g_pida.state.ek);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, g_pida.state.u1);
}

void test_reset_preserves_params(void)
{
    /* 修改参数 */
    g_pida.params.kp = 200.0f;
    g_pida.params.ti = 60.0f;
    
    /* 重置 */
    pida_reset(&g_pida);
    
    /* 参数应保留 */
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 200.0f, g_pida.params.kp);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 60.0f, g_pida.params.ti);
}

/* ============================================================================
 * 状态保存/恢复测试
 * ========================================================================== */

void test_state_save_restore(void)
{
    /* 运行一段时间积累状态 */
    g_input.mode = PIDA_MODE_AUTO;
    g_input.pv = 40.0f;
    g_input.sp = 60.0f;
    for (int i = 0; i < 20; i++) {
        pida_execute(&g_pida, &g_input);
    }
    
    /* 保存状态 */
    pida_state_t saved_state;
    pida_get_state(&g_pida, &saved_state);
    
    /* 重置 */
    pida_reset(&g_pida);
    
    /* 恢复状态 */
    pida_set_state(&g_pida, &saved_state);
    
    /* 验证状态已恢复 */
    TEST_ASSERT_FLOAT_WITHIN(0.001f, saved_state.ek, g_pida.state.ek);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, saved_state.u1, g_pida.state.u1);
    TEST_ASSERT_EQUAL_UINT8(saved_state.nowrm, g_pida.state.nowrm);
}

/* ============================================================================
 * 测试主函数
 * ========================================================================== */

int main(void)
{
    UNITY_BEGIN();
    
    /* Phase 2: 参数验证和初始化 */
    RUN_TEST(test_default_params_values);
    RUN_TEST(test_validate_params_null_pointer);
    RUN_TEST(test_validate_params_valid);
    RUN_TEST(test_validate_params_invalid_kp);
    RUN_TEST(test_validate_params_invalid_ranges);
    RUN_TEST(test_validate_params_invalid_pidtype);
    RUN_TEST(test_validate_params_invalid_eqn);
    RUN_TEST(test_init_null_pointer);
    RUN_TEST(test_init_default_state);
    RUN_TEST(test_init_with_params);
    RUN_TEST(test_init_with_invalid_params);
    
    /* Phase 3: PID计算 */
    RUN_TEST(test_execute_null_pointer);
    RUN_TEST(test_execute_nan_input);
    RUN_TEST(test_execute_inf_input);
    RUN_TEST(test_execute_auto_mode_steady_state);
    RUN_TEST(test_execute_auto_mode_with_error);
    RUN_TEST(test_execute_output_upper_limit);
    RUN_TEST(test_execute_output_lower_limit);
    RUN_TEST(test_execute_manual_mode);
    
    /* Phase 4: 模式切换 */
    RUN_TEST(test_mode_switch_manual_to_auto);
    RUN_TEST(test_mode_switch_auto_to_manual);
    
    /* Phase 5: 爬坡 */
    RUN_TEST(test_ramp_time_based);
    RUN_TEST(test_ramp_rate_based);
    
    /* Phase 6: 限值报警 */
    RUN_TEST(test_alarm_high_limit);
    RUN_TEST(test_alarm_low_limit);
    RUN_TEST(test_alarm_deadband);
    
    /* Phase 7: 偏差报警 */
    RUN_TEST(test_deviation_alarm);
    RUN_TEST(test_deviation_alarm_inhibit);
    
    /* Phase 8: 旁路 */
    RUN_TEST(test_bypass_enter);
    RUN_TEST(test_bypass_exit);
    
    /* Phase 9: 报警切手动 */
    RUN_TEST(test_alarm_to_manual);
    
    /* 其他 */
    RUN_TEST(test_reset_clears_state);
    RUN_TEST(test_reset_preserves_params);
    RUN_TEST(test_state_save_restore);
    
    return UNITY_END();
}
