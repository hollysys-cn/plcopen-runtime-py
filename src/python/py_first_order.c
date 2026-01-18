/**
 * @file py_first_order.c
 * @brief 一阶惯性功能块 Python绑定
 * @version 1.0
 * @date 2026-01-18
 *
 * 将C语言一阶惯性功能块暴露为Python类。
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "plcopen/fb_first_order.h"
#include <structmember.h>

/* ============================================================================
 * Python对象定义
 * ========================================================================== */

typedef struct {
    PyObject_HEAD
    first_order_instance_t instance;  /* C侧一阶惯性实例 */
} FirstOrderObject;

/* ============================================================================
 * 对象方法
 * ========================================================================== */

static int
FirstOrder_init(FirstOrderObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"k", "t", "dt", NULL};

    double k = 1.0;
    double t = 1.0;
    double dt = 0.1;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ddd", kwlist, &k, &t, &dt)) {
        return -1;
    }

    first_order_params_t params = {
        .k = k,
        .t = t,
        .dt = dt
    };

    plcopen_error_t err = first_order_validate_params(&params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return -1;
    }

    err = first_order_init_with_params(&self->instance, &params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, plcopen_strerror(err));
        return -1;
    }

    return 0;
}

static PyObject *
FirstOrder_execute(FirstOrderObject *self, PyObject *args)
{
    double input_value;

    if (!PyArg_ParseTuple(args, "d", &input_value)) {
        return NULL;
    }

    plcopen_error_t err = first_order_execute(&self->instance, input_value);

    if (err == PLCOPEN_ERR_NAN || err == PLCOPEN_ERR_INF) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return NULL;
    } else if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_RuntimeError, plcopen_strerror(err));
        return NULL;
    }

    return PyFloat_FromDouble(self->instance.output);
}

static PyObject *
FirstOrder_reset(FirstOrderObject *self, PyObject *args)
{
    double initial_value = 0.0;

    if (!PyArg_ParseTuple(args, "|d", &initial_value)) {
        return NULL;
    }

    first_order_reset(&self->instance, initial_value);
    Py_RETURN_NONE;
}

static PyObject *
FirstOrder_get_state(FirstOrderObject *self, PyObject *Py_UNUSED(args))
{
    first_order_state_t state;
    first_order_get_state(&self->instance, &state);

    return Py_BuildValue("{s:d}", "prev_output", state.prev_output);
}

static PyObject *
FirstOrder_set_state(FirstOrderObject *self, PyObject *args)
{
    PyObject *state_dict;

    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &state_dict)) {
        return NULL;
    }

    PyObject *prev_output_obj = PyDict_GetItemString(state_dict, "prev_output");

    if (!prev_output_obj) {
        PyErr_SetString(PyExc_KeyError, "状态字典缺少'prev_output'键");
        return NULL;
    }

    first_order_state_t state = {
        .prev_output = PyFloat_AsDouble(prev_output_obj)
    };

    if (PyErr_Occurred()) {
        return NULL;
    }

    first_order_set_state(&self->instance, &state);
    Py_RETURN_NONE;
}

/* ============================================================================
 * 属性访问器
 * ========================================================================== */

static PyObject *
FirstOrder_get_k(FirstOrderObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.k);
}

static int
FirstOrder_set_k(FirstOrderObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double k = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    self->instance.params.k = k;
    return 0;
}

static PyObject *
FirstOrder_get_t(FirstOrderObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.params.t);
}

static int
FirstOrder_set_t(FirstOrderObject *self, PyObject *value, void *closure)
{
    (void)closure;
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "不能删除属性");
        return -1;
    }

    double t = PyFloat_AsDouble(value);
    if (PyErr_Occurred()) {
        return -1;
    }

    if (t <= 0.0) {
        PyErr_SetString(PyExc_ValueError, "时间常数t必须 > 0");
        return -1;
    }

    self->instance.params.t = t;
    return 0;
}

/* 只读属性 */
static PyObject *
FirstOrder_get_output(FirstOrderObject *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.output);
}

/* ============================================================================
 * 方法表
 * ========================================================================== */

static PyMethodDef FirstOrder_methods[] = {
    {"execute", (PyCFunction)FirstOrder_execute, METH_VARARGS,
     "执行一步滤波计算。\n\n参数:\n    input_value: 输入信号\n\n返回:\n    float: 滤波后的输出信号"},
    {"reset", (PyCFunction)FirstOrder_reset, METH_VARARGS,
     "重置内部状态。\n\n参数:\n    initial_value: 初始输出值，默认0.0"},
    {"get_state", (PyCFunction)FirstOrder_get_state, METH_NOARGS,
     "获取内部状态（用于热重载）。\n\n返回:\n    dict: 状态字典"},
    {"set_state", (PyCFunction)FirstOrder_set_state, METH_VARARGS,
     "恢复内部状态（用于热重载）。\n\n参数:\n    state: 状态字典"},
    {NULL}
};

/* ============================================================================
 * 属性表
 * ========================================================================== */

static PyGetSetDef FirstOrder_getsetters[] = {
    {"k", (getter)FirstOrder_get_k, (setter)FirstOrder_set_k, "增益", NULL},
    {"t", (getter)FirstOrder_get_t, (setter)FirstOrder_set_t, "时间常数（秒）", NULL},
    {"output", (getter)FirstOrder_get_output, NULL, "当前输出值（只读）", NULL},
    {NULL}
};

/* ============================================================================
 * 类型定义
 * ========================================================================== */

PyTypeObject FirstOrderType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plcopen.FirstOrder",
    .tp_doc = "一阶惯性滤波器。\n\n"
              "传递函数: G(s) = K / (Ts + 1)\n"
              "离散化: y[n] = alpha * K * x[n] + (1-alpha) * y[n-1]\n"
              "        alpha = dt / (T + dt)\n\n"
              "参数:\n"
              "    k: 增益，默认1.0\n"
              "    t: 时间常数（秒），默认1.0\n"
              "    dt: 采样周期（秒），默认0.1\n\n"
              "示例:\n"
              "    >>> fo = plcopen.FirstOrder(k=1.0, t=0.5)\n"
              "    >>> output = fo.execute(100.0)\n",
    .tp_basicsize = sizeof(FirstOrderObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)FirstOrder_init,
    .tp_methods = FirstOrder_methods,
    .tp_getset = FirstOrder_getsetters,
};
