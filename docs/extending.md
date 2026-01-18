# 功能块扩展开发指南

本文档介绍如何为 PLCOpen 运行时添加新的功能块类型。

## 概述

PLCOpen 运行时采用 C 实现核心算法，通过 Python C 扩展暴露给 Python 脚本使用。添加新功能块需要完成以下步骤：

1. 定义 C 头文件（接口）
2. 实现 C 算法
3. 创建 Python 绑定
4. 注册到模块
5. 编写测试

## 文件结构

```
include/plcopen/
├── fb_common.h         # 通用定义
├── fb_pid.h            # PID 功能块头文件
├── fb_first_order.h    # 一阶惯性头文件
└── fb_<your_fb>.h      # 新功能块头文件

src/fb/
├── pid.c               # PID 实现
├── first_order.c       # 一阶惯性实现
└── <your_fb>.c         # 新功能块实现

src/python/
├── py_pid.c            # PID Python 绑定
├── py_first_order.c    # 一阶惯性 Python 绑定
├── py_<your_fb>.c      # 新功能块 Python 绑定
└── plcopen_module.c    # 模块注册

tests/unit/c/
└── test_<your_fb>.c    # C 单元测试

tests/unit/python/
└── test_<your_fb>.py   # Python 单元测试
```

## 步骤 1：定义 C 头文件

在 `include/plcopen/` 目录创建 `fb_<your_fb>.h`：

```c
/**
 * @file fb_<your_fb>.h
 * @brief <功能块名称>功能块定义
 */

#ifndef FB_<YOUR_FB>_H
#define FB_<YOUR_FB>_H

#include "fb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 结构体定义
 * ========================================================================== */

/**
 * @brief 参数结构体
 */
typedef struct {
    double param1;      /**< 参数1说明 */
    double param2;      /**< 参数2说明 */
    double dt;          /**< 采样周期（秒） */
} <your_fb>_params_t;

/**
 * @brief 状态结构体（用于热重载保存/恢复）
 */
typedef struct {
    double state1;      /**< 状态1 */
    double state2;      /**< 状态2 */
} <your_fb>_state_t;

/**
 * @brief 功能块实例
 */
typedef struct {
    <your_fb>_params_t params;  /**< 参数 */
    <your_fb>_state_t state;    /**< 内部状态 */
    double output;              /**< 输出值 */
} <your_fb>_instance_t;

/* ============================================================================
 * 函数声明
 * ========================================================================== */

/**
 * @brief 初始化功能块（默认参数）
 */
plcopen_error_t <your_fb>_init(<your_fb>_instance_t *inst);

/**
 * @brief 初始化功能块（自定义参数）
 */
plcopen_error_t <your_fb>_init_with_params(
    <your_fb>_instance_t *inst,
    const <your_fb>_params_t *params
);

/**
 * @brief 验证参数
 */
plcopen_error_t <your_fb>_validate_params(const <your_fb>_params_t *params);

/**
 * @brief 执行一步计算
 */
plcopen_error_t <your_fb>_execute(<your_fb>_instance_t *inst, double input);

/**
 * @brief 重置状态
 */
void <your_fb>_reset(<your_fb>_instance_t *inst, double initial_value);

/**
 * @brief 获取状态
 */
void <your_fb>_get_state(const <your_fb>_instance_t *inst, <your_fb>_state_t *state);

/**
 * @brief 设置状态
 */
void <your_fb>_set_state(<your_fb>_instance_t *inst, const <your_fb>_state_t *state);

#ifdef __cplusplus
}
#endif

#endif /* FB_<YOUR_FB>_H */
```

## 步骤 2：实现 C 算法

在 `src/fb/` 目录创建 `<your_fb>.c`：

```c
/**
 * @file <your_fb>.c
 * @brief <功能块名称>功能块实现
 */

#include "plcopen/fb_<your_fb>.h"
#include <math.h>
#include <string.h>

/* ============================================================================
 * 初始化
 * ========================================================================== */

plcopen_error_t <your_fb>_init(<your_fb>_instance_t *inst)
{
    if (inst == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    <your_fb>_params_t default_params = {
        .param1 = 1.0,
        .param2 = 1.0,
        .dt = 0.1
    };

    return <your_fb>_init_with_params(inst, &default_params);
}

plcopen_error_t <your_fb>_init_with_params(
    <your_fb>_instance_t *inst,
    const <your_fb>_params_t *params)
{
    if (inst == NULL || params == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    plcopen_error_t err = <your_fb>_validate_params(params);
    if (err != PLCOPEN_OK) {
        return err;
    }

    memcpy(&inst->params, params, sizeof(<your_fb>_params_t));
    memset(&inst->state, 0, sizeof(<your_fb>_state_t));
    inst->output = 0.0;

    return PLCOPEN_OK;
}

/* ============================================================================
 * 参数验证
 * ========================================================================== */

plcopen_error_t <your_fb>_validate_params(const <your_fb>_params_t *params)
{
    if (params == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    // 验证参数范围
    if (params->dt <= 0.0) {
        return PLCOPEN_ERR_PARAM;
    }

    return PLCOPEN_OK;
}

/* ============================================================================
 * 执行
 * ========================================================================== */

plcopen_error_t <your_fb>_execute(<your_fb>_instance_t *inst, double input)
{
    if (inst == NULL) {
        return PLCOPEN_ERR_NULL;
    }

    // 检查输入有效性
    if (isnan(input)) {
        return PLCOPEN_ERR_NAN;
    }
    if (isinf(input)) {
        return PLCOPEN_ERR_INF;
    }

    // TODO: 实现算法
    inst->output = input * inst->params.param1;

    return PLCOPEN_OK;
}

/* ============================================================================
 * 状态管理
 * ========================================================================== */

void <your_fb>_reset(<your_fb>_instance_t *inst, double initial_value)
{
    if (inst == NULL) return;

    memset(&inst->state, 0, sizeof(<your_fb>_state_t));
    inst->output = initial_value;
}

void <your_fb>_get_state(const <your_fb>_instance_t *inst, <your_fb>_state_t *state)
{
    if (inst == NULL || state == NULL) return;
    memcpy(state, &inst->state, sizeof(<your_fb>_state_t));
}

void <your_fb>_set_state(<your_fb>_instance_t *inst, const <your_fb>_state_t *state)
{
    if (inst == NULL || state == NULL) return;
    memcpy(&inst->state, state, sizeof(<your_fb>_state_t));
}
```

## 步骤 3：创建 Python 绑定

在 `src/python/` 目录创建 `py_<your_fb>.c`：

```c
/**
 * @file py_<your_fb>.c
 * @brief <功能块名称> Python 绑定
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "plcopen/fb_<your_fb>.h"

typedef struct {
    PyObject_HEAD
    <your_fb>_instance_t instance;
} <YourFB>Object;

/* 初始化方法 */
static int
<YourFB>_init(<YourFB>Object *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"param1", "param2", "dt", NULL};

    double param1 = 1.0, param2 = 1.0, dt = 0.1;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ddd", kwlist,
                                     &param1, &param2, &dt)) {
        return -1;
    }

    <your_fb>_params_t params = {
        .param1 = param1,
        .param2 = param2,
        .dt = dt
    };

    plcopen_error_t err = <your_fb>_validate_params(&params);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return -1;
    }

    <your_fb>_init_with_params(&self->instance, &params);
    return 0;
}

/* execute 方法 */
static PyObject *
<YourFB>_execute(<YourFB>Object *self, PyObject *args)
{
    double input;
    if (!PyArg_ParseTuple(args, "d", &input)) {
        return NULL;
    }

    plcopen_error_t err = <your_fb>_execute(&self->instance, input);
    if (err != PLCOPEN_OK) {
        PyErr_SetString(PyExc_ValueError, plcopen_strerror(err));
        return NULL;
    }

    return PyFloat_FromDouble(self->instance.output);
}

/* reset 方法 */
static PyObject *
<YourFB>_reset(<YourFB>Object *self, PyObject *args)
{
    double initial = 0.0;
    if (!PyArg_ParseTuple(args, "|d", &initial)) {
        return NULL;
    }

    <your_fb>_reset(&self->instance, initial);
    Py_RETURN_NONE;
}

/* get_state 方法 */
static PyObject *
<YourFB>_get_state(<YourFB>Object *self, PyObject *Py_UNUSED(args))
{
    <your_fb>_state_t state;
    <your_fb>_get_state(&self->instance, &state);

    return Py_BuildValue("{s:d,s:d}",
                         "state1", state.state1,
                         "state2", state.state2);
}

/* set_state 方法 */
static PyObject *
<YourFB>_set_state(<YourFB>Object *self, PyObject *args)
{
    PyObject *state_dict;
    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &state_dict)) {
        return NULL;
    }

    <your_fb>_state_t state = {0};
    PyObject *obj;

    if ((obj = PyDict_GetItemString(state_dict, "state1"))) {
        state.state1 = PyFloat_AsDouble(obj);
    }
    if ((obj = PyDict_GetItemString(state_dict, "state2"))) {
        state.state2 = PyFloat_AsDouble(obj);
    }

    <your_fb>_set_state(&self->instance, &state);
    Py_RETURN_NONE;
}

/* 方法表 */
static PyMethodDef <YourFB>_methods[] = {
    {"execute", (PyCFunction)<YourFB>_execute, METH_VARARGS,
     "执行一步计算。"},
    {"reset", (PyCFunction)<YourFB>_reset, METH_VARARGS,
     "重置状态。"},
    {"get_state", (PyCFunction)<YourFB>_get_state, METH_NOARGS,
     "获取状态。"},
    {"set_state", (PyCFunction)<YourFB>_set_state, METH_VARARGS,
     "设置状态。"},
    {NULL}
};

/* 属性访问器（示例） */
static PyObject *
<YourFB>_get_output(<YourFB>Object *self, void *closure)
{
    (void)closure;
    return PyFloat_FromDouble(self->instance.output);
}

static PyGetSetDef <YourFB>_getsetters[] = {
    {"output", (getter)<YourFB>_get_output, NULL, "输出值", NULL},
    {NULL}
};

/* 类型定义 */
PyTypeObject <YourFB>Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "plcopen.<YourFB>",
    .tp_doc = "<功能块名称>\n\n功能描述...",
    .tp_basicsize = sizeof(<YourFB>Object),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)<YourFB>_init,
    .tp_methods = <YourFB>_methods,
    .tp_getset = <YourFB>_getsetters,
};
```

## 步骤 4：注册到模块

编辑 `src/python/plcopen_module.c`：

```c
/* 添加外部类型声明 */
extern PyTypeObject <YourFB>Type;

/* 在 PyInit_plcopen 中添加 */
PyMODINIT_FUNC
PyInit_plcopen(void)
{
    // ... 现有代码 ...

    /* 准备新类型 */
    if (PyType_Ready(&<YourFB>Type) < 0) {
        return NULL;
    }

    /* 添加到模块 */
    Py_INCREF(&<YourFB>Type);
    if (PyModule_AddObject(m, "<YourFB>", (PyObject *)&<YourFB>Type) < 0) {
        Py_DECREF(&<YourFB>Type);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
```

## 步骤 5：更新 CMakeLists.txt

在 `CMakeLists.txt` 中添加源文件：

```cmake
set(FB_SOURCES
    src/fb/pid.c
    src/fb/first_order.c
    src/fb/<your_fb>.c    # 添加这行
)

set(PYTHON_SOURCES
    src/python/plcopen_module.c
    src/python/py_pid.c
    src/python/py_first_order.c
    src/python/py_<your_fb>.c    # 添加这行
)
```

## 步骤 6：编写测试

### C 单元测试

在 `tests/unit/c/` 创建 `test_<your_fb>.c`：

```c
#include "unity.h"
#include "plcopen/fb_<your_fb>.h"

static <your_fb>_instance_t fb;

void setUp(void) {
    memset(&fb, 0, sizeof(fb));
}

void tearDown(void) {}

void test_default_init(void) {
    plcopen_error_t err = <your_fb>_init(&fb);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
}

void test_execute(void) {
    <your_fb>_init(&fb);
    plcopen_error_t err = <your_fb>_execute(&fb, 10.0);
    TEST_ASSERT_EQUAL(PLCOPEN_OK, err);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_default_init);
    RUN_TEST(test_execute);
    return UNITY_END();
}
```

### Python 单元测试

在 `tests/unit/python/` 创建 `test_<your_fb>.py`：

```python
import pytest
import plcopen

class TestYourFB:
    def test_create(self):
        fb = plcopen.<YourFB>()
        assert fb is not None

    def test_execute(self):
        fb = plcopen.<YourFB>()
        output = fb.execute(10.0)
        assert output is not None

    def test_state_save_restore(self):
        fb = plcopen.<YourFB>()
        fb.execute(10.0)
        state = fb.get_state()
        fb.reset()
        fb.set_state(state)
```

## 构建和测试

```bash
# 配置构建
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

# 构建
cmake --build build

# 运行 C 测试
ctest --test-dir build --output-on-failure

# 运行 Python 测试
pytest tests/unit/python/test_<your_fb>.py -v
```

## 命名约定

| 类型 | 约定 | 示例 |
|------|------|------|
| 文件名 | 小写 + 下划线 | `fb_your_fb.h` |
| C 类型 | 小写 + 下划线 + `_t` | `your_fb_instance_t` |
| C 函数 | 小写 + 下划线 | `your_fb_execute` |
| Python 类 | 大驼峰 | `YourFB` |
| 测试函数 | `test_` 前缀 | `test_default_init` |

## 检查清单

- [ ] C 头文件定义完整（参数、状态、实例结构体）
- [ ] C 实现包含所有必要函数
- [ ] 参数验证完整
- [ ] NaN/Inf 输入处理
- [ ] Python 绑定包含 get_state/set_state（支持热重载）
- [ ] 模块注册完成
- [ ] CMakeLists.txt 更新
- [ ] C 单元测试覆盖主要场景
- [ ] Python 单元测试覆盖主要场景
- [ ] 文档和注释完整
