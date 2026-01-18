# PLCOpen嵌入式运行时 - 技术研究报告

**日期**: 2026-01-18
**分支**: `001-plcopen-runtime`
**状态**: 已完成

## 1. C11嵌入CPython解释器

### 决策：使用Python 3.11稳定C API，采用单解释器 + 多线程隔离模式

### 理由

**初始化和清理流程**：
```c
#include <Python.h>

// 初始化流程（推荐使用 PyConfig）
PyConfig config;
PyConfig_InitPythonConfig(&config);
config.isolated = 1;                    // 隔离模式，忽略环境变量
config.site_import = 1;                 // 允许导入 site 模块
PyConfig_SetString(&config, &config.program_name, L"plcopen_runtime");
Py_InitializeFromConfig(&config);
PyConfig_Clear(&config);

// 清理流程
Py_FinalizeEx();  // 使用 Ex 版本，返回错误码
```

**GIL对嵌入式场景的影响**：
- 场景是"主循环周期调用"，Python脚本在固定周期被运行时调用
- 运行时主循环持有GIL，顺序执行各脚本的周期函数
- **建议**：在C侧执行耗时操作（如功能块计算）时**释放GIL**：

```c
Py_BEGIN_ALLOW_THREADS
// C侧执行 PID 或一阶惯性计算（无Python对象访问）
result = pid_execute(instance, setpoint, process_value);
Py_END_ALLOW_THREADS
```

**多解释器隔离（Sub-interpreter）**：
- ❌ **不推荐用于此项目**
- Sub-interpreter在Python 3.11中仍有限制：C扩展模块不一定支持多解释器
- debugpy不支持sub-interpreter调试
- **替代方案**：使用单解释器 + 每脚本独立的Python模块命名空间实现逻辑隔离

### 备选方案

| 方案 | 优点 | 未选择原因 |
|------|------|-----------|
| Sub-interpreter | 完全隔离 | debugpy不支持，C扩展兼容性差 |
| 多进程 | 完全隔离 | 资源开销大，IPC复杂 |
| PyPy嵌入 | 可能更快 | 嵌入API不成熟，C扩展兼容性差 |

---

## 2. Python C扩展模块开发

### 决策：使用PyModule_Create + 自定义Python类型（Heap Type），CMake构建

### 理由

**标准模块创建流程**：
```c
// plcopen_module.c
static PyMethodDef PlcopenMethods[] = {
    {"create_pid", plcopen_create_pid, METH_VARARGS, "创建PID功能块实例"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef plcopenmodule = {
    PyModuleDef_HEAD_INIT,
    "plcopen",           // 模块名
    "PLCOpen功能块运行时", // 文档字符串
    -1,                  // 模块级状态大小（-1表示无）
    PlcopenMethods
};

PyMODINIT_FUNC PyInit_plcopen(void) {
    PyObject *m = PyModule_Create(&plcopenmodule);
    if (m == NULL) return NULL;

    // 注册 PID 类型
    if (PyType_Ready(&PIDType) < 0) return NULL;
    Py_INCREF(&PIDType);
    PyModule_AddObject(m, "PID", (PyObject *)&PIDType);

    return m;
}
```

**将C结构体暴露为Python对象**（推荐使用Heap Type）：
```c
// PID功能块的Python对象包装
typedef struct {
    PyObject_HEAD
    PID_Instance *c_instance;  // 指向C侧PID实例
} PIDObject;

static PyType_Slot PID_slots[] = {
    {Py_tp_new, PID_new},
    {Py_tp_init, PID_init},
    {Py_tp_dealloc, PID_dealloc},
    {Py_tp_methods, PID_methods},
    {Py_tp_getset, PID_getsetters},  // 属性访问器
    {0, NULL}
};

static PyType_Spec PID_spec = {
    .name = "plcopen.PID",
    .basicsize = sizeof(PIDObject),
    .flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE,
    .slots = PID_slots,
};
```

**内存管理和引用计数最佳实践**：
```c
// 黄金法则
// 1. 函数返回新引用：调用者负责 Py_DECREF
// 2. 函数返回借用引用：调用者不能 Py_DECREF
// 3. 函数参数：通常是借用引用，函数内使用不需额外处理

// 正确的错误处理模式
static PyObject* my_function(PyObject *self, PyObject *args) {
    PyObject *result = NULL;
    PyObject *temp = NULL;

    temp = PyObject_CallMethod(...);
    if (temp == NULL) goto error;  // 统一错误出口

    result = ...;
    Py_DECREF(temp);
    return result;

error:
    Py_XDECREF(temp);  // X版本安全处理NULL
    return NULL;
}
```

**构建工具选择 - CMake**：
```cmake
# CMakeLists.txt
find_package(Python3 REQUIRED COMPONENTS Development)

add_library(plcopen SHARED
    src/plcopen_module.c
    src/pid.c
    src/first_order.c
)

target_include_directories(plcopen PRIVATE ${Python3_INCLUDE_DIRS})
target_link_libraries(plcopen PRIVATE ${Python3_LIBRARIES})

# 设置正确的输出名称和后缀
set_target_properties(plcopen PROPERTIES
    PREFIX ""
    SUFFIX "${Python3_SOABI}.so"
)
```

### 备选方案

| 方案 | 优点 | 未选择原因 |
|------|------|-----------|
| setuptools | Python生态标准 | 嵌入式场景需要CMake统一管理C/C++构建 |
| Cython | 简化绑定代码 | 增加构建复杂度，调试困难 |
| pybind11 | C++友好 | 项目使用C11，不需要C++特性 |
| meson | 现代构建系统 | CMake生态更成熟，ARM工具链支持更好 |

---

## 3. 脚本热重载实现

### 决策：基于文件监控 + importlib.reload + 状态迁移回调

### 理由

**热重载核心流程**：
```python
# script_manager.py
import importlib
import importlib.util
from pathlib import Path
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class ScriptManager:
    def __init__(self, script_dir: Path):
        self.script_dir = script_dir
        self.loaded_scripts = {}  # name -> (module, fb_instances)

    def reload_script(self, script_name: str):
        """热重载脚本，保留功能块实例状态"""
        if script_name not in self.loaded_scripts:
            return self._load_new_script(script_name)

        old_module, fb_instances = self.loaded_scripts[script_name]

        # 1. 保存功能块实例状态
        saved_states = {}
        for name, instance in fb_instances.items():
            saved_states[name] = instance.get_state()  # C扩展提供

        # 2. 重新加载模块
        try:
            new_module = importlib.reload(old_module)
        except Exception as e:
            logging.error(f"脚本重载失败: {script_name}, 错误: {e}")
            return False  # 保持旧模块运行

        # 3. 恢复功能块实例状态
        if hasattr(new_module, 'on_reload'):
            new_module.on_reload(saved_states)

        # 4. 更新模块引用
        self.loaded_scripts[script_name] = (new_module, fb_instances)
        return True
```

**importlib.reload的限制和规避**：

| 限制 | 规避策略 |
|------|---------|
| 不更新已存在的对象引用 | 功能块实例由C侧管理，脚本只持有句柄 |
| 不删除旧模块的属性 | 每次重载前清理模块的 `__dict__` |
| from X import Y 不更新 | 强制使用 `import plcopen` 而非 `from plcopen import *` |

**功能块状态保留设计**（C扩展侧）：
```c
// PID实例状态序列化
static PyObject* PID_get_state(PIDObject *self, PyObject *Py_UNUSED(args)) {
    return Py_BuildValue("{s:d,s:d,s:d,s:d,s:d,s:d}",
        "kp", self->c_instance->kp,
        "ki", self->c_instance->ki,
        "kd", self->c_instance->kd,
        "integral", self->c_instance->integral,
        "prev_error", self->c_instance->prev_error,
        "output", self->c_instance->output
    );
}

// 状态恢复
static PyObject* PID_set_state(PIDObject *self, PyObject *state) {
    // 从字典恢复内部状态...
}
```

### 备选方案

| 方案 | 优点 | 未选择原因 |
|------|------|-----------|
| 重启子进程 | 完全干净的状态 | 丢失功能块状态，违反需求 |
| exec() 重新执行 | 简单 | 命名空间污染，难以管理状态 |
| 动态代码替换 | 精细控制 | 实现复杂，容易出错 |

---

## 4. debugpy集成

### 决策：使用debugpy监听模式 + DAP协议 + VSCode Remote附加

### 理由

**嵌入式Python中启用debugpy**：
```python
# 在运行时初始化时启动调试服务
import debugpy

def init_debug_server(host: str = "0.0.0.0", port: int = 5678):
    """初始化DAP调试服务器"""
    try:
        debugpy.listen((host, port))
        logging.info(f"debugpy调试服务器已启动: {host}:{port}")
        return True
    except Exception as e:
        logging.warning(f"debugpy启动失败: {e}，调试功能不可用")
        return False
```

**VSCode调试配置**（`.vscode/launch.json`）：
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "附加到PLCOpen运行时",
            "type": "debugpy",
            "request": "attach",
            "connect": {
                "host": "localhost",
                "port": 5678
            },
            "pathMappings": [
                {
                    "localRoot": "${workspaceFolder}/scripts",
                    "remoteRoot": "/app/scripts"
                }
            ],
            "justMyCode": false
        }
    ]
}
```

### 备选方案

| 方案 | 优点 | 未选择原因 |
|------|------|-----------|
| pdb远程调试 | 内置无依赖 | 无GUI支持，体验差 |
| PyCharm远程 | 功能强大 | 商业协议，debugpy更开放 |
| rpdb | 轻量 | 功能有限，无断点条件支持 |

---

## 5. Docker开发环境

### 决策：基于python:3.11-slim + 阿里云镜像 + 多阶段构建

### 理由

**完整Dockerfile示例**：
```dockerfile
# syntax=docker/dockerfile:1
# ============ 构建阶段 ============
FROM python:3.11-slim AS builder

# 配置apt国内镜像（阿里云）
RUN sed -i 's/deb.debian.org/mirrors.aliyun.com/g' /etc/apt/sources.list.d/debian.sources && \
    sed -i 's/security.debian.org/mirrors.aliyun.com/g' /etc/apt/sources.list.d/debian.sources

# 配置pip国内镜像（阿里云）
RUN mkdir -p /root/.pip && \
    echo '[global]\n\
index-url = https://mirrors.aliyun.com/pypi/simple/\n\
trusted-host = mirrors.aliyun.com\n\
timeout = 120' > /root/.pip/pip.conf

# 安装构建依赖
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    python3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY . .

# 构建C扩展
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

# ============ 运行阶段 ============
FROM python:3.11-slim AS runtime

# 配置pip国内镜像
COPY --from=builder /root/.pip/pip.conf /root/.pip/pip.conf

# 安装运行时Python依赖
RUN pip install --no-cache-dir debugpy watchdog

# 复制构建产物
COPY --from=builder /build/build/*.so /app/lib/
COPY --from=builder /build/runtime /app/runtime/

WORKDIR /app
ENV PYTHONPATH=/app/lib:/app

EXPOSE 5678

CMD ["python", "-m", "runtime.main"]
```

**推荐的国内镜像源配置**：

| 资源类型 | 镜像源 | 配置方式 |
|---------|-------|---------|
| Docker Hub | 阿里云容器镜像 | `/etc/docker/daemon.json` |
| PyPI | 阿里云 `mirrors.aliyun.com/pypi/simple` | `pip.conf` |
| APT (Debian) | 阿里云 `mirrors.aliyun.com` | `sources.list` |

**docker-compose.yml**：
```yaml
version: '3.8'
services:
  plcopen-dev:
    build:
      context: .
      dockerfile: Dockerfile.dev
    volumes:
      - ./scripts:/app/scripts  # 脚本热重载
      - ./logs:/app/logs
    ports:
      - "5678:5678"  # debugpy
    environment:
      - PYTHONDONTWRITEBYTECODE=1
      - PYTHONUNBUFFERED=1
    platform: linux/amd64
```

### 备选方案

| 方案 | 优点 | 未选择原因 |
|------|------|-----------|
| Ubuntu基础镜像 | 更完整 | 镜像体积大（400MB+ vs 150MB） |
| Alpine镜像 | 最小体积 | musl libc与CPython存在兼容性问题 |
| 清华镜像源 | 稳定 | 阿里云在国内覆盖更广、速度更快 |

---

## 总结决策表

| 领域 | 决策 | 关键理由 |
|------|------|---------|
| Python嵌入 | 单解释器 + GIL释放 | debugpy兼容、实现简单 |
| C扩展开发 | PyModule_Create + Heap Type + CMake | 类型安全、与项目构建统一 |
| 热重载 | importlib.reload + 状态回调 | 满足状态保留需求 |
| 调试 | debugpy + DAP + VSCode | 标准协议、生态成熟 |
| Docker环境 | python:3.11-slim + 阿里云镜像 | 体积适中、国内加速 |
