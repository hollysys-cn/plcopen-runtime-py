/**
 * @file py_pid.c
 * @brief PID功能块 Python绑定
 * @version 1.0
 * @date 2026-01-18
 *
 * 将C语言PID功能块暴露为Python类。
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "plcopen/fb_pid.h"
#include <structmember.h>

/* ============================================================================
 * Python对象定义
 * ========================================================================== */

typedef struct {
    PyObject_HEAD
    pid_instance_t instance;  /* C侧PID实例 */
} PIDObject;

/* ============================================================================
 * 对象方法
 * ========================================================================== */

static int
PID_init(PIDObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"kp", "ki", "kd", "out_min", "out_max", "dt", NULL};

    double kp = 1.0;
    double ki = 0.0;
    double kd = 0.0;
    double out_min = -INFINITY;
    double out_max = INFINITY;
    double dt = 0.1;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|dddddd", kwlist,
                                     &kp, &ki, &kd, &out_min, &out_max, &dt)) {
        return -1;
    }

    pid_params_t params = {
        .kp = kp,
        .ki = ki,
        .kd = kd,
        .out_min = out_min,
        .out_max = out_max,
        .dt = dt
    };

    plcopen_error_t err = pid_validate_params(&params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return -1;
    }

    err = pid_init_with_params(&self->instance, &params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, plcopen_strerror(err));
        return -1;
    }

    return 0;
}

static PyObject *
PID_execute(PIDObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"setpoint", "pv", NULL};

    double setpoint, pv;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "dd", kwlist, &setpoint, &pv)) {
        return NULL;
    }

    pid_input_t input = {.setpoint = setpoint, .pv = pv};
    plcopen_error_t err = pid_execute(&self->instance, &input);

    if (err == PLCOPEN_ERR_NAN || err == PLCOPEN_ERR_INF) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return NULL;
    } else if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, plcopen_strerror(err));
        return NULL;
    }

    return PyFloat_FromDouble(self->instance.output.output);
}

static PyObject *
PID_reset(PIDObject *self, PyObject *Py_UNUSED(args))
{
    pid_reset(&self->instance);
    Py_RETURN_NONE;
}

static PyObject *
PID_get_state(PIDObject *self, PyObject *Py_UNUSED(args))
{
    pid_state_t state;
    pid_get_state(&self->instance, &state);

    return Py_BuildValue("{s:d,s:d,s:d}",
                         "integral", state.integral,
                         "prev_error", state.prev_error,
                         "prev_output", state.prev_output);
}

static PyObject *
PID_set_state(PIDObject *self, PyObject *args)
{
    PyObject *state_dict;

    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &state_dict)) {
        return NULL;
    }

    PyObject *integral_obj = PyDict_GetItemString(state_dict, "integral");
    PyObject *prev_error_obj = PyDict_GetItemString(state_dict, "prev_error");
    PyObject *prev_output_obj = PyDict_GetItemString(state_dict, "prev_output");

    if (!integral_obj || !prev_error_obj || !prev_output_obj) {
        PyErr_SetString(PyExc_KeyError, "状态字典缺少必要的键");
        return NULL;
    }

    pid_state_t state = {
        .integral = PyFloat_AsDouble(integral_obj),
        .prev_error = PyFloat_AsDouble(prev_error_obj),
        .prev_output = PyFloat_AsDouble(prev_output_obj)
    };

    if (PyErr_Occurred()) {
        return NULL;
    }

    pid_set_state(&self->instance, &state);
    Py_RETURN_NONE;
}

/* ============================================================================
 * 属性访问器
 * ========================================================================== */

static PyObject *
PID_get_kp(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.kp);
}

static int
PID_set_kp(PIDObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double kp = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (kp < 0.0) {
        PyErr_SetString(PyExc_ValueError, "kp必须 >= 0");
        return -1;
    }

    self->instance.params.kp = kp;
    return 0;
}

static PyObject *
PID_get_ki(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.ki);
}

static int
PID_set_ki(PIDObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double ki = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (ki < 0.0) {
        PyErr_SetString(PyExc_ValueError, "ki必须 >= 0");
        return -1;
    }

    self->instance.params.ki = ki;
    return 0;
}

static PyObject *
PID_get_kd(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.kd);
}

static int
PID_set_kd(PIDObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double kd = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (kd < 0.0) {
        PyErr_SetString(PyExc_ValueError, "kd必须 >= 0");
        return -1;
    }

    self->instance.params.kd = kd;
    return 0;
}

static PyObject *
PID_get_out_min(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.out_min);
}

static int
PID_set_out_min(PIDObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double out_min = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (out_min >= self->instance.params.out_max) {
        PyErr_SetString(PyExc_ValueError, "out_min必须 < out_max");
        return -1;
    }

    self->instance.params.out_min = out_min;
    return 0;
}

static PyObject *
PID_get_out_max(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.out_max);
}

static int
PID_set_out_max(PIDObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double out_max = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (out_max <= self->instance.params.out_min) {
        PyErr_SetString(PyExc_ValueError, "out_max必须 > out_min");
        return -1;
    }

    self->instance.params.out_max = out_max;
    return 0;
}

/* 只读属性 */
static PyObject *
PID_get_output(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.output.output);
}

static PyObject *
PID_get_error(PIDObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.output.error);
}

static PyObject *
PID_get_saturated(PIDObject *self, void *closure)
{
    (void)closure;
    return PyBool_FromLong(self->instance.output.saturated);
}

/* ============================================================================
 * 方法表
 * ========================================================================== */

static PyMethodDef PID_methods[] = {
    {"execute", (PyCFunction)PID_execute, METH_VARARGS | METH_KEYWORDS,
     "执行一步PID计算。\n\n参数:\n    setpoint: 设定值\n    pv: 过程值\n\n返回:\n    float: 控制输出值"},
    {"reset", (PyCFunction)PID_reset, METH_NOARGS,
     "重置内部状态。"},
    {"get_state", (PyCFunction)PID_get_state, METH_NOARGS,
     "获取内部状态（用于热重载）。\n\n返回:\n    dict: 状态字典"},
    {"set_state", (PyCFunction)PID_set_state, METH_VARARGS,
     "恢复内部状态（用于热重载）。\n\n参数:\n    state: 状态字典"},
    {NULL}
};

/* ============================================================================
 * 属性表
 * ========================================================================== */

static PyGetSetDef PID_getsetters[] = {
    {"kp", (getter)PID_get_kp, (setter)PID_set_kp, "比例增益", NULL},
    {"ki", (getter)PID_get_ki, (setter)PID_set_ki, "积分增益", NULL},
    {"kd", (getter)PID_get_kd, (setter)PID_set_kd, "微分增益", NULL},
    {"out_min", (getter)PID_get_out_min, (setter)PID_set_out_min, "输出下限", NULL},
    {"out_max", (getter)PID_get_out_max, (setter)PID_set_out_max, "输出上限", NULL},
    {"output", (getter)PID_get_output, NULL, "上一次计算的输出值（只读）", NULL},
    {"error", (getter)PID_get_error, NULL, "上一次计算的偏差值（只读）", NULL},
    {"saturated", (getter)PID_get_saturated, NULL, "上一次输出是否被限幅（只读）", NULL},
    {NULL}
};

/* ============================================================================
 * 类型定义
 * ========================================================================== */

PyTypeObject PIDType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plcopen.PID",
    .tp_doc = "位置式PID控制器。\n\n"
              "算法: output = Kp * error + Ki * ∫error + Kd * d(error)/dt\n\n"
              "参数:\n"
              "    kp: 比例增益，默认1.0\n"
              "    ki: 积分增益，默认0.0\n"
              "    kd: 微分增益，默认0.0\n"
              "    out_min: 输出下限，默认-inf\n"
              "    out_max: 输出上限，默认+inf\n"
              "    dt: 采样周期（秒），默认0.1\n\n"
              "示例:\n"
              "    >>> pid = plcopen.PID(kp=1.0, ki=0.1, kd=0.05)\n"
              "    >>> output = pid.execute(setpoint=100.0, pv=80.0)\n",
    .tp_basicsize = sizeof(PIDObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)PID_init,
    .tp_methods = PID_methods,
    .tp_getset = PID_getsetters,
};
