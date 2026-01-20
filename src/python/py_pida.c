/**
 * @file py_pida.c
 * @brief PIDA功能块Python绑定实现
 * @version 1.0
 * @date 2026-01-20
 *
 * 提供PIDA功能块的Python接口封装。
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include "plcopen/fb_pida.h"

/* ============================================================================
 * PyPIDA 类型对象定义
 * ========================================================================== */

typedef struct {
    PyObject_HEAD
    pida_instance_t instance;
    pida_input_t last_input;
} PyPIDA;

/* ============================================================================
 * 前向声明
 * ========================================================================== */

static PyTypeObject PyPIDA_Type;

/* ============================================================================
 * PyPIDA 方法实现
 * ========================================================================== */

static void
PyPIDA_dealloc(PyPIDA *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
PyPIDA_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyPIDA *self;
    self = (PyPIDA *)type->tp_alloc(type, 0);
    if (self != NULL) {
        /* 使用默认参数初始化 */
        pida_init(&self->instance);
        memset(&self->last_input, 0, sizeof(pida_input_t));
        self->last_input.cyc = 0.5f;
    }
    return (PyObject *)self;
}

static int
PyPIDA_init(PyPIDA *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {
        "kp", "ti", "td", "kd",
        "pvu", "pvl", "engu", "engl",
        "outu", "outl", "spu", "spl",
        "pidtype", "eqn", "outopt", "actopt",
        "cyc",
        /* 报警参数 */
        "hh", "ah", "al", "ll",
        "h2", "h1", "l1", "l2",
        "almdb", "almopt",
        NULL
    };
    
    pida_params_t params = pida_default_params();
    float cyc = 0.5f;
    int pidtype = PIDA_TYPE_SINGLE;
    int eqn = PIDA_EQN_STANDARD;
    int outopt = 0;
    int actopt = 1;
    /* 报警参数默认值 */
    int h2 = 0, h1 = 0, l1 = 0, l2 = 0;
    int almopt = 1;
    
    /* 格式字符串: 12f + 4i + 5f + 4i + 1f + 1i = 27个参数 */
    if (!PyArg_ParseTupleAndKeywords(args, kwds, 
            "|ffffffffffffiiiifffffiiiifi", kwlist,
            &params.kp, &params.ti, &params.td, &params.kd,
            &params.pvu, &params.pvl, &params.engu, &params.engl,
            &params.outu, &params.outl, &params.spu, &params.spl,
            &pidtype, &eqn, &outopt, &actopt,
            &cyc,
            &params.hh, &params.ah, &params.al, &params.ll,
            &h2, &h1, &l1, &l2,
            &params.almdb, &almopt)) {
        return -1;
    }
    
    params.pidtype = (uint8_t)pidtype;
    params.eqn = (uint8_t)eqn;
    params.outopt = (bool)outopt;
    params.actopt = (bool)actopt;
    /* 报警级别和开关 */
    params.h2 = (uint8_t)h2;
    params.h1 = (uint8_t)h1;
    params.l1 = (uint8_t)l1;
    params.l2 = (uint8_t)l2;
    params.almopt = (bool)almopt;
    
    plcopen_error_t err = pida_init_with_params(&self->instance, &params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_ValueError, "参数无效");
        return -1;
    }
    
    self->last_input.cyc = cyc;
    
    return 0;
}

static PyObject *
PyPIDA_execute(PyPIDA *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"pv", "mout", "sp", "mode", "cyc", NULL};
    
    float pv = 0.0f;
    PyObject *mout_obj = NULL; /* 手动输出值对象，用于检测是否传入 */
    float sp = -1.0f;  /* -1表示使用当前SP */
    int mode = -1;     /* -1表示使用当前模式 */
    float cyc = -1.0f; /* -1表示使用上次周期 */
    
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "f|Ofif", kwlist,
            &pv, &mout_obj, &sp, &mode, &cyc)) {
        return NULL;
    }
    
    /* 更新输入 */
    self->last_input.pv = pv;
    
    /* 只有当用户明确传入 mout 参数时才设置 pmsw */
    if (mout_obj != NULL) {
        float mout = (float)PyFloat_AsDouble(mout_obj);
        if (PyErr_Occurred()) {
            return NULL;
        }
        self->last_input.pmout = mout;  /* 程控手动输出 */
        self->last_input.pmsw = true;   /* 使用程序手动输出 */
    } else {
        self->last_input.pmsw = false;  /* 不使用程序手动输出 */
    }
    
    if (sp >= 0.0f) {
        self->last_input.sp = sp;
    }
    
    if (mode >= 0 && mode <= PIDA_MODE_AUTO_TRACK) {
        self->last_input.mode = (uint8_t)mode;
    }
    
    if (cyc > 0.0f) {
        self->last_input.cyc = cyc;
    }
    
    /* 执行计算 */
    plcopen_error_t err = pida_execute(&self->instance, &self->last_input);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, "PIDA执行失败");
        return NULL;
    }
    
    /* 返回输出值 */
    return PyFloat_FromDouble(self->instance.output.out);
}

static PyObject *
PyPIDA_reset(PyPIDA *self, PyObject *Py_UNUSED(ignored))
{
    pida_reset(&self->instance);
    Py_RETURN_NONE;
}

static PyObject *
PyPIDA_start_ramp(PyPIDA *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"target", "time_or_rate", "rtyp", NULL};
    
    float target = 0.0f;
    float time_or_rate = 0.0f;
    int rtyp = 0;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "ff|i", kwlist,
            &target, &time_or_rate, &rtyp)) {
        return NULL;
    }
    
    plcopen_error_t err = pida_start_ramp(&self->instance, target, 
                                           time_or_rate, (bool)rtyp);
    if (err != PLCOPEN_OK) {
        if (err == PLCOPEN_ERR_INVALID_STATE) {
            PyErr_SetString(PyExc_RuntimeError, "爬坡仅在自动模式下有效");
        } else {
            PyErr_SetString(PyExc_RuntimeError, "启动爬坡失败");
        }
        return NULL;
    }
    
    Py_RETURN_NONE;
}

static PyObject *
PyPIDA_stop_ramp(PyPIDA *self, PyObject *Py_UNUSED(ignored))
{
    pida_stop_ramp(&self->instance);
    Py_RETURN_NONE;
}

static PyObject *
PyPIDA_get_alarms(PyPIDA *self, PyObject *Py_UNUSED(ignored))
{
    bool hhind, ahind, alind, llind, da;
    pida_get_alarms(&self->instance, &hhind, &ahind, &alind, &llind, &da);
    
    return Py_BuildValue("{s:O,s:O,s:O,s:O,s:O,s:I}",
        "hhind", hhind ? Py_True : Py_False,
        "ahind", ahind ? Py_True : Py_False,
        "alind", alind ? Py_True : Py_False,
        "llind", llind ? Py_True : Py_False,
        "da", da ? Py_True : Py_False,
        "am", (unsigned int)pida_get_alarm_word(&self->instance));
}

static PyObject *
PyPIDA_get_state(PyPIDA *self, PyObject *Py_UNUSED(ignored))
{
    pida_state_t state;
    pida_get_state(&self->instance, &state);
    
    /* 返回关键状态信息 */
    return Py_BuildValue("{s:f,s:f,s:f,s:f,s:f,s:I,s:O}",
        "ek", state.ek,
        "dk", state.dk,
        "du", state.du,
        "u1", state.u1,
        "sp1", state.sp1,
        "mode", (unsigned int)state.nowrm,
        "rcmdflag", state.rcmdflag ? Py_True : Py_False);
}

/* ============================================================================
 * PyPIDA 属性
 * ========================================================================== */

static PyObject *
PyPIDA_get_output(PyPIDA *self, void *closure)
{
    return PyFloat_FromDouble(self->instance.output.out);
}

static PyObject *
PyPIDA_get_error(PyPIDA *self, void *closure)
{
    return PyFloat_FromDouble(self->instance.output.ek);
}

static PyObject *
PyPIDA_get_sp(PyPIDA *self, void *closure)
{
    /* 返回用户设置的 SP 或上次执行后的 SP */
    if (self->last_input.sp > 0.0f || self->instance.output.sp == 0.0f) {
        return PyFloat_FromDouble(self->last_input.sp);
    }
    return PyFloat_FromDouble(self->instance.output.sp);
}

static int
PyPIDA_set_sp(PyPIDA *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete sp");
        return -1;
    }
    
    if (!PyFloat_Check(value) && !PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "sp must be a number");
        return -1;
    }
    
    float sp = (float)PyFloat_AsDouble(value);
    self->last_input.sp = sp;
    /* 同时更新 output.sp 使 get 立即生效 */
    self->instance.output.sp = sp;
    return 0;
}

static PyObject *
PyPIDA_get_mode(PyPIDA *self, void *closure)
{
    /* 返回用户设置的模式，如果还没有 execute 过 */
    return PyLong_FromLong(self->last_input.mode);
}

static int
PyPIDA_set_mode(PyPIDA *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete mode");
        return -1;
    }
    
    if (!PyLong_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "mode must be an integer");
        return -1;
    }
    
    long mode = PyLong_AsLong(value);
    if (mode < 0 || mode > PIDA_MODE_AUTO_TRACK) {
        PyErr_SetString(PyExc_ValueError, "mode must be 0-4");
        return -1;
    }
    
    self->last_input.mode = (uint8_t)mode;
    pida_set_mode(&self->instance, (pida_mode_t)mode);
    /* 同时更新 state.nowrm 使 get 立即生效 */
    self->instance.state.nowrm = (uint8_t)mode;
    return 0;
}

static PyObject *
PyPIDA_get_hhind(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.hhind);
}

static PyObject *
PyPIDA_get_ahind(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.ahind);
}

static PyObject *
PyPIDA_get_alind(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.alind);
}

static PyObject *
PyPIDA_get_llind(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.llind);
}

static PyObject *
PyPIDA_get_da(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.da);
}

static PyObject *
PyPIDA_get_am(PyPIDA *self, void *closure)
{
    return PyLong_FromUnsignedLong(self->instance.output.am);
}

static PyObject *
PyPIDA_get_ove(PyPIDA *self, void *closure)
{
    return PyLong_FromUnsignedLong(self->instance.output.ove);
}

static PyObject *
PyPIDA_get_bypass(PyPIDA *self, void *closure)
{
    return PyBool_FromLong(self->instance.output.ctrbp);
}

static int
PyPIDA_set_bypass(PyPIDA *self, PyObject *value, void *closure)
{
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete bypass");
        return -1;
    }
    
    bool bypass = PyObject_IsTrue(value);
    plcopen_error_t err = pida_set_bypass(&self->instance, bypass);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, "旁路仅对串级副调有效");
        return -1;
    }
    
    self->last_input.ctrbp = bypass;
    return 0;
}

/* ============================================================================
 * 方法表和属性表
 * ========================================================================== */

static PyMethodDef PyPIDA_methods[] = {
    {"execute", (PyCFunction)PyPIDA_execute, METH_VARARGS | METH_KEYWORDS,
     "执行一步PIDA计算\n\n"
     "参数:\n"
     "    pv: 过程值\n"
     "    sp: 设定值（可选）\n"
     "    mode: 运行模式（可选）\n"
     "    cyc: 计算周期（可选）\n\n"
     "返回:\n"
     "    控制输出值"},
    {"reset", (PyCFunction)PyPIDA_reset, METH_NOARGS,
     "重置PIDA内部状态"},
    {"start_ramp", (PyCFunction)PyPIDA_start_ramp, METH_VARARGS | METH_KEYWORDS,
     "启动设定值爬坡\n\n"
     "参数:\n"
     "    target: 目标设定值\n"
     "    time_or_rate: 爬坡时间（分钟）或速率（工程量/分钟）\n"
     "    rtyp: 爬坡方式，0=时间，1=速率"},
    {"stop_ramp", (PyCFunction)PyPIDA_stop_ramp, METH_NOARGS,
     "停止设定值爬坡"},
    {"get_alarms", (PyCFunction)PyPIDA_get_alarms, METH_NOARGS,
     "获取报警状态字典"},
    {"get_state", (PyCFunction)PyPIDA_get_state, METH_NOARGS,
     "获取内部状态字典"},
    {NULL}  /* Sentinel */
};

static PyGetSetDef PyPIDA_getseters[] = {
    {"output", (getter)PyPIDA_get_output, NULL, "控制输出值", NULL},
    {"out", (getter)PyPIDA_get_output, NULL, "控制输出值（别名）", NULL},
    {"error", (getter)PyPIDA_get_error, NULL, "当前偏差", NULL},
    {"ek", (getter)PyPIDA_get_error, NULL, "当前偏差（别名）", NULL},
    {"sp", (getter)PyPIDA_get_sp, (setter)PyPIDA_set_sp, "设定值", NULL},
    {"mode", (getter)PyPIDA_get_mode, (setter)PyPIDA_set_mode, "运行模式", NULL},
    {"hhind", (getter)PyPIDA_get_hhind, NULL, "高高限报警", NULL},
    {"ahind", (getter)PyPIDA_get_ahind, NULL, "高限报警", NULL},
    {"alind", (getter)PyPIDA_get_alind, NULL, "低限报警", NULL},
    {"llind", (getter)PyPIDA_get_llind, NULL, "低低限报警", NULL},
    {"da", (getter)PyPIDA_get_da, NULL, "偏差报警", NULL},
    {"am", (getter)PyPIDA_get_am, NULL, "报警信息字", NULL},
    {"ove", (getter)PyPIDA_get_ove, NULL, "输出超限状态", NULL},
    {"bypass", (getter)PyPIDA_get_bypass, (setter)PyPIDA_set_bypass, "旁路状态", NULL},
    {NULL}  /* Sentinel */
};

static PyTypeObject PyPIDA_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plcopen.PIDA",
    .tp_doc = PyDoc_STR("PIDA功能块 - 带过程值报警的PID控制器\n\n"
        "基于IEC61131-3标准的工业级PID控制器实现，\n"
        "支持五种运行模式、四级过程值报警、设定值爬坡等功能。\n\n"
        "参数:\n"
        "    kp: 比例带（%），默认100\n"
        "    ti: 积分时间（秒），默认30\n"
        "    td: 微分时间（秒），默认0\n"
        "    kd: 微分增益，默认1\n"
        "    pvu: PV量程上限，默认100\n"
        "    pvl: PV量程下限，默认0\n"
        "    engu: 输出量程上限，默认100\n"
        "    engl: 输出量程下限，默认0\n"
        "    outu: 输出上限，默认100\n"
        "    outl: 输出下限，默认0\n"
        "    pidtype: PID类型，0=单回路，1=串级主调，2=串级副调，3=外给定\n"
        "    eqn: PID公式，0=标准型，1=微分先行，2=比例微分先行\n"
        "    outopt: 输出方式，0=位置式，1=增量式\n"
        "    actopt: 作用方式，0=正作用，1=反作用\n"
        "    cyc: 计算周期（秒），默认0.5"),
    .tp_basicsize = sizeof(PyPIDA),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyPIDA_new,
    .tp_init = (initproc)PyPIDA_init,
    .tp_dealloc = (destructor)PyPIDA_dealloc,
    .tp_methods = PyPIDA_methods,
    .tp_getset = PyPIDA_getseters,
};

/* ============================================================================
 * 模块注册函数（供plcopen_module.c调用）
 * ========================================================================== */

int PyPIDA_Register(PyObject *module)
{
    if (PyType_Ready(&PyPIDA_Type) < 0) {
        return -1;
    }
    
    Py_INCREF(&PyPIDA_Type);
    if (PyModule_AddObject(module, "PIDA", (PyObject *)&PyPIDA_Type) < 0) {
        Py_DECREF(&PyPIDA_Type);
        return -1;
    }
    
    /* 添加模式常量 */
    PyModule_AddIntConstant(module, "PIDA_MODE_MANUAL", PIDA_MODE_MANUAL);
    PyModule_AddIntConstant(module, "PIDA_MODE_AUTO", PIDA_MODE_AUTO);
    PyModule_AddIntConstant(module, "PIDA_MODE_CASCADE", PIDA_MODE_CASCADE);
    PyModule_AddIntConstant(module, "PIDA_MODE_MANUAL_TRACK", PIDA_MODE_MANUAL_TRACK);
    PyModule_AddIntConstant(module, "PIDA_MODE_AUTO_TRACK", PIDA_MODE_AUTO_TRACK);
    
    /* 添加类型常量 */
    PyModule_AddIntConstant(module, "PIDA_TYPE_SINGLE", PIDA_TYPE_SINGLE);
    PyModule_AddIntConstant(module, "PIDA_TYPE_CASCADE_MASTER", PIDA_TYPE_CASCADE_MASTER);
    PyModule_AddIntConstant(module, "PIDA_TYPE_CASCADE_SLAVE", PIDA_TYPE_CASCADE_SLAVE);
    PyModule_AddIntConstant(module, "PIDA_TYPE_EXTERNAL_SP", PIDA_TYPE_EXTERNAL_SP);
    
    /* 添加公式常量 */
    PyModule_AddIntConstant(module, "PIDA_EQN_STANDARD", PIDA_EQN_STANDARD);
    PyModule_AddIntConstant(module, "PIDA_EQN_DERIVATIVE_FIRST", PIDA_EQN_DERIVATIVE_FIRST);
    PyModule_AddIntConstant(module, "PIDA_EQN_PD_FIRST", PIDA_EQN_PD_FIRST);
    
    return 0;
}
