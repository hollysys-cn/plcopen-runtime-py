/**
 * @file plcopen_module.c
 * @brief PLCOpen Python模块入口
 * @version 1.0
 * @date 2026-01-18
 *
 * 使用功能块注册表动态注册所有功能块类型到Python模块。
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "plcopen/plcopen.h"
#include "fb/fb_registry.h"

/* 外部类型声明 */
extern PyTypeObject PIDType;
extern PyTypeObject FirstOrderType;

/* Python类型注册表 */
typedef struct {
    const char *name;
    PyTypeObject *type;
} py_type_entry_t;

static py_type_entry_t py_types[] = {
    {"PID", &PIDType},
    {"FirstOrder", &FirstOrderType},
    {NULL, NULL}  /* 结束标记 */
};

/* ============================================================================
 * 模块级函数
 * ========================================================================== */

static PyObject *
py_plcopen_version(PyObject *self, PyObject *Py_UNUSED(args))
{
    (void)self;
    return PyUnicode_FromString(PLCOPEN_VERSION_STRING);
}

static PyObject *
plcopen_list_types(PyObject *self, PyObject *Py_UNUSED(args))
{
    (void)self;

    /* 获取注册表中的功能块列表 */
    size_t count = 0;
    const fb_info_t **infos = fb_registry_list(&count);

    PyObject *list = PyList_New(count);
    if (list == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        PyObject *name = PyUnicode_FromString(infos[i]->name);
        if (name == NULL) {
            Py_DECREF(list);
            return NULL;
        }
        PyList_SET_ITEM(list, i, name);
    }

    return list;
}

static PyMethodDef PlcopenMethods[] = {
    {"version", py_plcopen_version, METH_NOARGS,
     "获取PLCOpen运行时版本。\n\n返回:\n    str: 版本字符串"},
    {"list_types", plcopen_list_types, METH_NOARGS,
     "列出所有已注册的功能块类型。\n\n返回:\n    list: 功能块名称列表"},
    {NULL, NULL, 0, NULL}
};

/* ============================================================================
 * 模块定义
 * ========================================================================== */

static struct PyModuleDef plcopenmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "plcopen",
    .m_doc = "PLCOpen功能块运行时\n\n"
             "提供工业控制领域常用的功能块：\n"
             "  - PID: 位置式PID控制器\n"
             "  - FirstOrder: 一阶惯性滤波器\n\n"
             "示例:\n"
             "    >>> import plcopen\n"
             "    >>> pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1)\n"
             "    >>> output = pid.execute(setpoint=100.0, pv=80.0)\n",
    .m_size = -1,
    .m_methods = PlcopenMethods,
};

/* ============================================================================
 * 模块初始化
 * ========================================================================== */

/**
 * @brief 使用注册表动态添加所有Python类型
 *
 * @param module Python模块对象
 * @return 成功返回 0，失败返回 -1
 */
static int
register_all_types(PyObject *module)
{
    for (py_type_entry_t *entry = py_types; entry->name != NULL; entry++) {
        /* 准备类型 */
        if (PyType_Ready(entry->type) < 0) {
            PyErr_Format(PyExc_RuntimeError,
                         "无法准备类型: %s", entry->name);
            return -1;
        }

        /* 添加到模块 */
        Py_INCREF(entry->type);
        if (PyModule_AddObject(module, entry->name, (PyObject *)entry->type) < 0) {
            Py_DECREF(entry->type);
            PyErr_Format(PyExc_RuntimeError,
                         "无法注册类型到模块: %s", entry->name);
            return -1;
        }
    }

    return 0;
}

PyMODINIT_FUNC
PyInit_plcopen(void)
{
    PyObject *m;

    /* 创建模块 */
    m = PyModule_Create(&plcopenmodule);
    if (m == NULL) {
        return NULL;
    }

    /* 使用注册表添加所有类型 */
    if (register_all_types(m) < 0) {
        Py_DECREF(m);
        return NULL;
    }

    /* 添加版本常量 */
    if (PyModule_AddStringConstant(m, "__version__", PLCOPEN_VERSION_STRING) < 0) {
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
