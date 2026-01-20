/**
 * @file pida.c
 * @brief PIDA功能块实现 - 带过程值报警的PID控制器
 * @version 1.0
 * @date 2026-01-20
 *
 * 基于IEC61131-3标准的工业级PID控制器实现。
 * 算法逻辑完全按照 PIDA.xml 中的ST组态实现。
 * 
 * 参考: IEC61131-1/PIDA/PIDA.xml
 */

#include "plcopen/fb_pida.h"
#include <string.h>
#include <math.h>

/* ============================================================================
 * 内部辅助函数声明
 * ========================================================================== */

/**
 * @brief 报警检测函数（带死区）
 * @param pv 过程值
 * @param limit 报警限值
 * @param deadband 死区
 * @param prev_alarm 上周期报警状态
 * @param is_high_alarm true=高限报警, false=低限报警
 * @return 报警状态
 */
static bool ai_alm(float pv, float limit, float deadband, bool prev_alarm, bool is_high_alarm);

/**
 * @brief 数据准备 - 参数边界修正
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_data_prepare(pida_instance_t* pida, const pida_input_t* input);

/**
 * @brief PID计算核心
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_pid_calculate(pida_instance_t* pida, const pida_input_t* input);

/**
 * @brief 模式处理
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_mode_process(pida_instance_t* pida, const pida_input_t* input);

/**
 * @brief 报警处理
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_alarm_process(pida_instance_t* pida, const pida_input_t* input);

/**
 * @brief 爬坡处理
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_ramp_process(pida_instance_t* pida, const pida_input_t* input);

/**
 * @brief 输出处理
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 */
static void pida_output_process(pida_instance_t* pida, const pida_input_t* input);

/* ============================================================================
 * 公共接口实现
 * ========================================================================== */

pida_params_t pida_default_params(void)
{
    pida_params_t params;
    memset(&params, 0, sizeof(params));
    
    /* PID参数 */
    params.kp = 100.0f;
    params.ti = 30.0f;
    params.td = 0.0f;
    params.kd = 1.0f;
    
    /* 量程设置 */
    params.pvu = 100.0f;
    params.pvl = 0.0f;
    params.engu = 100.0f;
    params.engl = 0.0f;
    params.outu = 100.0f;
    params.outl = 0.0f;
    params.spu = 100.0f;
    params.spl = 0.0f;
    
    /* 控制选项 */
    params.pidtype = PIDA_TYPE_SINGLE;
    params.eqn = PIDA_EQN_STANDARD;
    params.octyp = 0;
    params.outopt = false;
    params.actopt = true;   /* 默认反作用 */
    params.trkopt = true;
    params.trken = true;
    
    /* 变化率 */
    params.outrat = 5.0f;
    params.giverat = 10.0f;
    params.manf = 1.5f;
    params.mans = 0.5f;
    params.spfrat = 5.0f;
    params.spsrat = 1.0f;
    
    /* 死区 */
    params.dvdb = 0.2f;
    params.intedb = 100.0f;
    params.satdb = 0.0f;
    
    /* 报警限值 - 默认禁用 */
    params.hh = 0.0f;
    params.ah = 0.0f;
    params.al = 0.0f;
    params.ll = 0.0f;
    params.almdb = 2.0f;
    params.dal = 30.0f;
    
    /* 报警级别 - 0表示禁用 */
    params.h2 = 0;
    params.h1 = 0;
    params.l1 = 0;
    params.l2 = 0;
    params.dallv = 0;
    
    /* 报警抑制 */
    params.inhh2 = false;
    params.inhh1 = false;
    params.inhl1 = false;
    params.inhl2 = false;
    params.inhdal = false;
    
    /* 切手动控制 */
    params.mancut = 0x0780;  /* 默认1920 */
    
    /* 其他选项 */
    params.almopt = true;
    params.omanopt = false;
    params.smanopt = false;
    params.molsw = true;
    params.lmbls = false;
    params.rovep = false;
    params.trkmode = false;
    params.simu = false;
    
    return params;
}

plcopen_error_t pida_validate_params(const pida_params_t* params)
{
    if (params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    /* 验证KP > 0 */
    if (params->kp <= 0.0f) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证TI >= 0 */
    if (params->ti < 0.0f) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证TD >= 0 */
    if (params->td < 0.0f) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证KD > 0 */
    if (params->kd <= 0.0f) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证PVU > PVL */
    if (params->pvu <= params->pvl) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证ENGU > ENGL */
    if (params->engu <= params->engl) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证OUTU > OUTL */
    if (params->outu <= params->outl) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证PIDTYPE范围 */
    if (params->pidtype > 3) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 验证EQN范围 */
    if (params->eqn > 2) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    return PLCOPEN_OK;
}

plcopen_error_t pida_init(pida_instance_t* pida)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    pida_params_t default_params = pida_default_params();
    return pida_init_with_params(pida, &default_params);
}

plcopen_error_t pida_init_with_params(pida_instance_t* pida, const pida_params_t* params)
{
    if (pida == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    plcopen_error_t err = pida_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }
    
    /* 清零整个实例 */
    memset(pida, 0, sizeof(pida_instance_t));
    
    /* 复制参数 */
    memcpy(&pida->params, params, sizeof(pida_params_t));
    
    /* 初始化状态 */
    pida->state.nowrm = PIDA_MODE_MANUAL;
    pida->state.prerm = PIDA_MODE_MANUAL;
    pida->state.cycletime = 0.5f;  /* 默认计算周期 */
    
    /* 初始化输出 */
    pida->output.mode = PIDA_MODE_MANUAL;
    pida->output.out = 0.0f;
    
    return PLCOPEN_OK;
}

void pida_reset(pida_instance_t* pida)
{
    if (pida == NULL) {
        return;
    }
    
    /* 保留参数，只清零状态和输出 */
    pida_params_t params_backup;
    memcpy(&params_backup, &pida->params, sizeof(pida_params_t));
    
    memset(&pida->state, 0, sizeof(pida_state_t));
    memset(&pida->output, 0, sizeof(pida_output_t));
    
    memcpy(&pida->params, &params_backup, sizeof(pida_params_t));
    
    /* 重新初始化状态 */
    pida->state.nowrm = PIDA_MODE_MANUAL;
    pida->state.prerm = PIDA_MODE_MANUAL;
    pida->state.cycletime = 0.5f;
    pida->output.mode = PIDA_MODE_MANUAL;
}

plcopen_error_t pida_get_output(const pida_instance_t* pida, pida_output_t* output)
{
    if (pida == NULL || output == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    memcpy(output, &pida->output, sizeof(pida_output_t));
    return PLCOPEN_OK;
}

void pida_get_state(const pida_instance_t* pida, pida_state_t* state)
{
    if (pida == NULL || state == NULL) {
        return;
    }
    
    memcpy(state, &pida->state, sizeof(pida_state_t));
}

void pida_set_state(pida_instance_t* pida, const pida_state_t* state)
{
    if (pida == NULL || state == NULL) {
        return;
    }
    
    memcpy(&pida->state, state, sizeof(pida_state_t));
}

plcopen_error_t pida_set_mode(pida_instance_t* pida, pida_mode_t mode)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    if (mode > PIDA_MODE_AUTO_TRACK) {
        return PLCOPEN_ERR_INVALID_PARAM;
    }
    
    /* 模式切换将在下次execute时生效 */
    pida->output.mode = mode;
    
    return PLCOPEN_OK;
}

pida_mode_t pida_get_mode(const pida_instance_t* pida)
{
    if (pida == NULL) {
        return PIDA_MODE_MANUAL;
    }
    
    return (pida_mode_t)pida->state.nowrm;
}

plcopen_error_t pida_set_bypass(pida_instance_t* pida, bool bypass)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    /* 旁路仅对串级副调有效 */
    if (pida->params.pidtype != PIDA_TYPE_CASCADE_SLAVE) {
        return PLCOPEN_ERR_INVALID_STATE;
    }
    
    pida->output.ctrbp = bypass;
    
    return PLCOPEN_OK;
}

void pida_stop_ramp(pida_instance_t* pida)
{
    if (pida == NULL) {
        return;
    }
    
    pida->state.rcmdflag = false;
    pida->output.rcmdflag = false;
}

plcopen_error_t pida_start_ramp(pida_instance_t* pida, float target, 
                                 float time_or_rate, bool rtyp)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    /* 爬坡仅在自动模式下有效 */
    if (pida->state.nowrm != PIDA_MODE_AUTO) {
        return PLCOPEN_ERR_INVALID_STATE;
    }
    
    pida->state.rcmdflag = true;
    pida->state.prertyp = rtyp;
    pida->state.prersptv = target;
    
    if (rtyp) {
        /* 速率方式 */
        pida->state.prerratsp = time_or_rate;
    } else {
        /* 时间方式 */
        pida->state.prertimesp = time_or_rate;
    }
    
    return PLCOPEN_OK;
}

plcopen_error_t pida_get_ramp_status(const pida_instance_t* pida, 
                                      bool* active, float* remaining_time, float* current_rate)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    if (active != NULL) {
        *active = pida->state.rcmdflag;
    }
    
    if (remaining_time != NULL) {
        *remaining_time = pida->state.rtime;
    }
    
    if (current_rate != NULL) {
        *current_rate = pida->state.rrat;
    }
    
    return PLCOPEN_OK;
}

plcopen_error_t pida_get_alarms(const pida_instance_t* pida,
                                 bool* hhind, bool* ahind, bool* alind, bool* llind, bool* da)
{
    if (pida == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    if (hhind != NULL) {
        *hhind = pida->output.hhind;
    }
    
    if (ahind != NULL) {
        *ahind = pida->output.ahind;
    }
    
    if (alind != NULL) {
        *alind = pida->output.alind;
    }
    
    if (llind != NULL) {
        *llind = pida->output.llind;
    }
    
    if (da != NULL) {
        *da = pida->output.da;
    }
    
    return PLCOPEN_OK;
}

uint16_t pida_get_alarm_word(const pida_instance_t* pida)
{
    if (pida == NULL) {
        return 0;
    }
    
    return pida->output.am;
}

plcopen_error_t pida_set_params(pida_instance_t* pida, const pida_params_t* params)
{
    if (pida == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    plcopen_error_t err = pida_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }
    
    memcpy(&pida->params, params, sizeof(pida_params_t));
    
    return PLCOPEN_OK;
}

plcopen_error_t pida_execute(pida_instance_t* pida, const pida_input_t* input)
{
    if (pida == NULL || input == NULL) {
        return PLCOPEN_ERR_NULL_PTR;
    }
    
    /* 输入有效性检查 */
    if (PLCOPEN_IS_NAN(input->pv) || PLCOPEN_IS_NAN(input->sp)) {
        return PLCOPEN_ERR_NAN;
    }
    
    if (PLCOPEN_IS_INF(input->pv) || PLCOPEN_IS_INF(input->sp)) {
        return PLCOPEN_ERR_INF;
    }
    
    /* 更新设定值（如果不在爬坡） */
    if (!pida->state.rcmdflag) {
        pida->state.sp1 = PLCOPEN_CLAMP(input->sp, pida->params.spl, pida->params.spu);
    }
    
    /* 1. 数据准备 - 参数边界修正 */
    pida_data_prepare(pida, input);
    
    /* 2. 模式处理 */
    pida_mode_process(pida, input);
    
    /* 3. 爬坡处理 */
    pida_ramp_process(pida, input);
    
    /* 4. PID计算 */
    pida_pid_calculate(pida, input);
    
    /* 5. 输出处理 */
    pida_output_process(pida, input);
    
    /* 6. 报警处理 */
    pida_alarm_process(pida, input);
    
    /* 7. 更新输出结构 */
    pida->output.ek = pida->state.ek;
    pida->output.dk = pida->state.dk;
    pida->output.du = pida->state.du;
    pida->output.rrat = pida->state.rrat;
    pida->output.rtime = pida->state.rtime;
    pida->output.rcmdflag = pida->state.rcmdflag;
    pida->output.am = pida->state.am;
    pida->output.ove = pida->state.ove;
    pida->output.mode = pida->state.nowrm;
    
    return PLCOPEN_OK;
}

/* ============================================================================
 * 内部辅助函数实现
 * ========================================================================== */

static bool ai_alm(float pv, float limit, float deadband, bool prev_alarm, bool is_high_alarm)
{
    if (is_high_alarm) {
        /* 高限报警：PV > limit 触发，PV < limit - deadband 解除 */
        if (prev_alarm) {
            return (pv >= (limit - deadband));
        } else {
            return (pv > limit);
        }
    } else {
        /* 低限报警：PV < limit 触发，PV > limit + deadband 解除 */
        if (prev_alarm) {
            return (pv <= (limit + deadband));
        } else {
            return (pv < limit);
        }
    }
}

static void pida_data_prepare(pida_instance_t* pida, const pida_input_t* input)
{
    pida_params_t* p = &pida->params;
    pida_state_t* s = &pida->state;
    
    /* 周期时间处理 */
    float cyc = input->cyc;
    if (cyc <= 0.0f) {
        cyc = 0.5f;  /* 默认周期 */
    }
    s->cycletime = cyc;
    
    /* PVU/PVL 边界修正 */
    if (p->pvu <= p->pvl) {
        p->pvu = 100.0f;
        p->pvl = 0.0f;
    }
    
    /* ENGU/ENGL 边界修正 */
    if (p->engu <= p->engl) {
        p->engu = 100.0f;
        p->engl = 0.0f;
    }
    
    /* OUTU/OUTL 边界修正 */
    if (p->outu <= p->outl) {
        p->outu = 100.0f;
        p->outl = 0.0f;
    }
    
    /* KP 边界修正 */
    if (p->kp <= 0.0f) {
        p->kp = 100.0f;
    }
    
    /* TI 边界修正 */
    if (p->ti < 0.0f) {
        p->ti = 0.0f;
    }
    
    /* 计算比例带换算值 */
    s->dt1 = 100.0f / p->kp;
    
    /* 计算死区范围 */
    s->deadinterval = p->dvdb * (p->pvu - p->pvl) / 100.0f;
    
    /* 计算积分分离值 */
    s->sv1 = p->intedb * (p->pvu - p->pvl) / 100.0f;
    
    /* 计算报警死区 */
    s->ralalmdb = p->almdb * (p->pvu - p->pvl) / 100.0f;
    
    /* 计算偏差报警限值 */
    s->devalmlimit = p->dal * (p->pvu - p->pvl) / 100.0f;
    
    /* 计算输出变化率限值 */
    s->realoutrat = p->outrat * (p->engu - p->engl) / 100.0f * s->cycletime;
    
    /* 计算给定变化率限值 */
    s->realgiverat = p->giverat * (p->pvu - p->pvl) / 100.0f * s->cycletime;
    
    /* 中间输出上下限 */
    s->mu1 = p->outu;
    s->md1 = p->outl;
}

static void pida_mode_process(pida_instance_t* pida, const pida_input_t* input)
{
    pida_state_t* s = &pida->state;
    pida_params_t* p = &pida->params;
    
    /* 保存上周期模式 */
    s->prerm = s->nowrm;
    
    /* 模式值保护 */
    uint8_t new_mode = input->mode;
    if (new_mode > PIDA_MODE_AUTO_TRACK) {
        new_mode = s->nowrm;  /* 无效模式回退 */
    }
    
    /* 跟踪模式处理 */
    if (p->trken && input->trksw) {
        /* 跟踪开关打开时强制进入跟踪模式 */
        if (new_mode == PIDA_MODE_MANUAL) {
            new_mode = PIDA_MODE_MANUAL_TRACK;
        } else if (new_mode == PIDA_MODE_AUTO) {
            new_mode = PIDA_MODE_AUTO_TRACK;
        }
    }
    
    /* 模式切换无扰处理 */
    if (s->prerm != new_mode) {
        /* 从手动切到自动：SP跟踪PV */
        if (s->prerm == PIDA_MODE_MANUAL && new_mode == PIDA_MODE_AUTO) {
            if (p->trkopt) {
                s->sp1 = input->pv;
            }
        }
        
        /* 从自动切到手动：保持输出 */
        if (s->prerm == PIDA_MODE_AUTO && new_mode == PIDA_MODE_MANUAL) {
            /* 输出已保持在lastout中 */
        }
    }
    
    s->nowrm = new_mode;
}

static void pida_ramp_process(pida_instance_t* pida, const pida_input_t* input)
{
    pida_state_t* s = &pida->state;
    pida_params_t* p = &pida->params;
    
    /* 爬坡仅在自动模式下有效 */
    if (s->nowrm != PIDA_MODE_AUTO) {
        s->rcmdflag = false;
        s->rrat = 0.0f;
        s->rtime = 0.0f;
        return;
    }
    
    /* 爬坡命令处理 */
    if (input->rcmd == 1 && !s->rcmdflag) {
        /* 启动爬坡 */
        s->rcmdflag = true;
        s->prertyp = input->rtyp;
        s->prersptv = input->rsptv;
        s->prertimesp = input->rtimesp;
        s->prerratsp = input->rratsp;
        
        if (input->rtyp) {
            /* 速率方式 */
            s->rrat = input->rratsp / 60.0f;  /* 转换为工程量/秒 */
            float delta = input->rsptv - s->sp1;
            if (fabsf(s->rrat) > 0.0001f) {
                s->rtime = fabsf(delta) / fabsf(s->rrat);
            } else {
                s->rtime = 0.0f;
            }
        } else {
            /* 时间方式 */
            s->rtime = input->rtimesp * 60.0f;  /* 转换为秒 */
            if (s->rtime > 0.0001f) {
                s->rrat = (input->rsptv - s->sp1) / s->rtime;
            } else {
                s->rrat = 0.0f;
            }
        }
    } else if (input->rcmd == 0) {
        /* 停止爬坡 */
        s->rcmdflag = false;
    }
    
    /* 爬坡执行 */
    if (s->rcmdflag) {
        /* 检查是否暂停（输出超限） */
        if (p->rovep && (s->ove & (PIDA_OVE_OVER_HIGH | PIDA_OVE_OVER_LOW))) {
            /* 暂停爬坡 */
        } else {
            /* 更新设定值 */
            float delta = s->rrat * s->cycletime;
            s->sp1 += delta;
            s->rtime -= s->cycletime;
            
            /* 检查是否到达目标 */
            if (s->rtime <= 0.0f || 
                (s->rrat > 0 && s->sp1 >= s->prersptv) ||
                (s->rrat < 0 && s->sp1 <= s->prersptv)) {
                s->sp1 = s->prersptv;
                s->rcmdflag = false;
                s->rtime = 0.0f;
            }
        }
    }
}

static void pida_pid_calculate(pida_instance_t* pida, const pida_input_t* input)
{
    pida_state_t* s = &pida->state;
    pida_params_t* p = &pida->params;
    
    /* 获取设定值和过程值 */
    float sp = s->sp1;
    float pv = input->pv + input->incomp;  /* 输入补偿 */
    
    /* 计算偏差（所有模式下都计算偏差） */
    float error;
    if (p->actopt) {
        /* 反作用：error = SP - PV */
        error = sp - pv;
    } else {
        /* 正作用：error = PV - SP */
        error = pv - sp;
    }
    
    /* 保存偏差历史 */
    s->ek_2 = s->ek_1;
    s->ek_1 = s->ek;
    s->ek = error;
    
    /* 仅在自动/串级模式下进行PID计算 */
    if (s->nowrm == PIDA_MODE_MANUAL || 
        s->nowrm == PIDA_MODE_MANUAL_TRACK) {
        return;
    }
    
    /* 死区处理 */
    float pid_error = error;
    if (fabsf(error) < s->deadinterval) {
        s->dd = 1;
        pid_error = 0.0f;
    } else {
        s->dd = 0;
    }
    
    /* 积分分离判断 */
    if (fabsf(error) > s->sv1) {
        s->si = 1;  /* 积分分离 */
    } else {
        s->si = 0;
    }
    
    /* 微分项计算 */
    s->d1 = s->dk;
    
    switch (p->eqn) {
        case PIDA_EQN_STANDARD:
            /* 标准型：对偏差微分 */
            s->dk = (s->ek - s->ek_1) / s->cycletime;
            break;
            
        case PIDA_EQN_DERIVATIVE_FIRST:
            /* 微分先行：对PV微分 */
            s->dk = -(pv - s->prepv) / s->cycletime;
            break;
            
        case PIDA_EQN_PD_FIRST:
            /* 比例微分先行：对PV微分 */
            s->dk = -(pv - s->prepv) / s->cycletime;
            break;
            
        default:
            s->dk = 0.0f;
            break;
    }
    
    /* 微分增益 */
    s->dudd = p->kd * s->dk * p->td;
    
    /* PID计算 */
    float kp_inv = s->dt1;  /* 100/KP */
    float prop, integ, deriv;
    
    /* 比例项 */
    if (p->eqn == PIDA_EQN_PD_FIRST) {
        /* 比例微分先行：比例项作用于PV */
        prop = -pv / kp_inv;
    } else {
        /* 标准型/微分先行：比例项作用于偏差 */
        prop = pid_error / kp_inv;
    }
    
    /* 积分项 */
    if (p->ti > 0.0001f && s->si == 0) {
        /* 有积分且未分离 */
        integ = pid_error * s->cycletime / p->ti / kp_inv;
    } else {
        integ = 0.0f;
    }
    
    /* 微分项 */
    deriv = s->dudd / kp_inv;
    
    /* 计算增量 */
    s->du = prop + integ + deriv - s->u1 * (1.0f - 1.0f);  /* 简化 */
    
    /* 位置式输出 */
    if (!p->outopt) {
        /* 位置式 */
        s->uk = s->u1 + s->du;
        s->ukout = s->uk;
        
        /* 输出补偿 */
        if (p->octyp == 0) {
            s->ukout += input->outcomp;  /* 加法 */
        } else {
            s->ukout *= (1.0f + input->outcomp / 100.0f);  /* 乘法 */
        }
    } else {
        /* 增量式 */
        s->duout = s->du;
        
        /* 输出补偿 */
        if (p->octyp == 0) {
            s->duout += input->outcomp;
        }
    }
    
    /* 保存状态 */
    s->prepv = pv;
    s->u1 = s->uk;
}

static void pida_output_process(pida_instance_t* pida, const pida_input_t* input)
{
    pida_state_t* s = &pida->state;
    pida_params_t* p = &pida->params;
    pida_output_t* o = &pida->output;
    
    float output_val;
    
    /* 根据模式选择输出 */
    switch (s->nowrm) {
        case PIDA_MODE_MANUAL:
        case PIDA_MODE_MANUAL_TRACK:
            /* 手动模式：使用手动输出 */
            if (input->pmsw) {
                output_val = input->pmout;
            } else {
                /* 根据MANMODE调整输出 */
                output_val = s->lastout;
                float delta = 0.0f;
                
                switch (input->manmode) {
                    case 1: delta = p->manf; break;   /* 快增 */
                    case 2: delta = -p->manf; break;  /* 快减 */
                    case 3: delta = p->mans; break;   /* 慢增 */
                    case 4: delta = -p->mans; break;  /* 慢减 */
                    default: break;
                }
                
                if (!p->omanopt) {
                    /* 百分比方式 */
                    delta *= (p->engu - p->engl) / 100.0f;
                }
                
                output_val += delta;
            }
            break;
            
        case PIDA_MODE_AUTO:
        case PIDA_MODE_AUTO_TRACK:
        case PIDA_MODE_CASCADE:
            /* 自动/串级模式：使用PID输出 */
            if (!p->outopt) {
                output_val = s->ukout;
            } else {
                output_val = s->lastout + s->duout;
            }
            break;
            
        default:
            output_val = s->lastout;
            break;
    }
    
    /* 输出变化率限制 */
    if (s->realoutrat > 0.0001f) {
        float delta = output_val - s->lastout;
        if (delta > s->realoutrat) {
            output_val = s->lastout + s->realoutrat;
        } else if (delta < -s->realoutrat) {
            output_val = s->lastout - s->realoutrat;
        }
    }
    
    /* 输出限幅 */
    s->ove = 0;
    PIDA_B_WRITE(s->ove, 2, p->actopt);  /* 正反作用位 */
    
    if (output_val > p->outu) {
        output_val = p->outu;
        PIDA_B_SET(s->ove, 0);  /* 超上限 */
    } else if (output_val < p->outl) {
        output_val = p->outl;
        PIDA_B_SET(s->ove, 1);  /* 超下限 */
    }
    
    /* 旁路处理 */
    if (p->pidtype == PIDA_TYPE_CASCADE_SLAVE && input->ctrbp) {
        output_val = input->auxcomp;  /* 旁路时直接跟随主调输出 */
        PIDA_B_SET(s->ove, 3);  /* 旁路位 */
    }
    
    /* 保存输出 */
    s->lastout = output_val;
    o->out = output_val;
    o->sp = s->sp1;
    o->ctrbp = input->ctrbp;
    
    /* 内给定输出（串级主调使用） */
    if (p->pidtype == PIDA_TYPE_CASCADE_MASTER) {
        o->intersp = output_val;
        o->comp = output_val;
    }
}

static void pida_alarm_process(pida_instance_t* pida, const pida_input_t* input)
{
    pida_state_t* s = &pida->state;
    pida_params_t* p = &pida->params;
    pida_output_t* o = &pida->output;
    
    float pv = input->pv;
    
    /* 清除报警信息字 */
    s->am = 0;
    o->hhind = false;
    o->ahind = false;
    o->alind = false;
    o->llind = false;
    o->da = false;
    
    /* 如果报警功能关闭，直接返回 */
    if (!p->almopt) {
        return;
    }
    
    /* 高高限报警 */
    if (p->h2 > 0 && !p->inhh2) {
        bool alarm = ai_alm(pv, p->hh, s->ralalmdb, s->prehh, true);
        o->hhind = alarm;
        s->prehh = alarm;
        if (alarm) {
            PIDA_B_SET(s->am, 3);
        }
    }
    
    /* 高限报警 */
    if (p->h1 > 0 && !p->inhh1) {
        bool alarm = ai_alm(pv, p->ah, s->ralalmdb, s->preah, true);
        o->ahind = alarm;
        s->preah = alarm;
        if (alarm) {
            PIDA_B_SET(s->am, 2);
        }
    }
    
    /* 低限报警 */
    if (p->l1 > 0 && !p->inhl1) {
        bool alarm = ai_alm(pv, p->al, s->ralalmdb, s->preal, false);
        o->alind = alarm;
        s->preal = alarm;
        if (alarm) {
            PIDA_B_SET(s->am, 1);
        }
    }
    
    /* 低低限报警 */
    if (p->l2 > 0 && !p->inhl2) {
        bool alarm = ai_alm(pv, p->ll, s->ralalmdb, s->prell, false);
        o->llind = alarm;
        s->prell = alarm;
        if (alarm) {
            PIDA_B_SET(s->am, 0);
        }
    }
    
    /* 偏差报警 */
    if (p->dallv > 0 && !p->inhdal) {
        float deviation = fabsf(s->sp1 - pv);
        if (deviation > s->devalmlimit) {
            o->da = true;
            PIDA_B_SET(s->am, 7);
        }
    }
    
    /* 报警切手动处理 */
    if (s->am != 0 && p->mancut != 0) {
        /* 检查是否需要切手动 */
        if ((s->am & p->mancut) != 0) {
            /* 触发切手动 */
            if (s->nowrm != PIDA_MODE_MANUAL) {
                s->nowrm = PIDA_MODE_MANUAL;
                o->mode = PIDA_MODE_MANUAL;
            }
        }
    }
    
    /* 通道故障切手动 */
    if (input->q != 0) {
        /* 质量字非0表示有故障 */
        if (s->nowrm != PIDA_MODE_MANUAL) {
            s->nowrm = PIDA_MODE_MANUAL;
            o->mode = PIDA_MODE_MANUAL;
            s->evenfault++;
        }
    }
}
