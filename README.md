# PLCOpen 嵌入式运行时环境

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Python](https://img.shields.io/badge/python-3.11+-blue.svg)](https://www.python.org/)
[![C Standard](https://img.shields.io/badge/C-C11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

嵌入式PLCOpen运行时环境，使用C11实现核心功能块（PID、一阶惯性），通过Python C扩展提供脚本化控制能力。

## 特性

- 🎯 **核心功能块**: 位置式PID控制器、一阶惯性滤波器
- 🐍 **Python脚本**: 在Python中调用功能块，快速验证控制算法
- 🔄 **热重载**: 运行时自动检测脚本变更，无需重启
- 🔧 **远程调试**: 支持VSCode远程调试Python脚本
- 🏗️ **双平台**: 支持ARM Cortex-M4和X86开发模拟

## 快速开始

### 环境要求

- Docker Desktop（推荐）
- 或本地环境：Python 3.11+，CMake 3.20+，GCC/Clang

### 使用Docker（推荐）

```bash
# 克隆仓库
git clone https://github.com/hollysys-cn/plcopen-runtime-py.git
cd plcopen-runtime-py

# 启动开发环境
docker compose up --build

# 在另一个终端连接到容器
docker compose exec runtime bash
```

### 本地开发

```bash
# 安装Python依赖
pip install -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/

# 构建C扩展
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make -j$(nproc)

# 运行测试
ctest --output-on-failure
pytest tests/
```

## 使用示例

### Python脚本

在 `scripts/` 目录创建控制脚本：

```python
# scripts/temperature_control.py
import plcopen

# 创建PID控制器
pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1, out_min=0, out_max=100)

def main():
    """主循环函数，由运行时按100ms周期调用"""
    setpoint = 60.0  # 目标温度
    pv = read_temperature()  # 读取当前温度

    output = pid.execute(setpoint=setpoint, pv=pv)
    set_heater_power(output)  # 设置加热器功率
```

### 启动运行时

```bash
# 使用Docker
docker compose up

# 或本地运行
python -m runtime.main
```

## 项目结构

```
plcopen-runtime-py/
├── src/                    # C源代码
│   ├── fb/                 # 功能块实现
│   ├── python/             # Python C扩展
│   └── common/             # 公共工具
├── include/                # C头文件
├── runtime/                # Python运行时模块
├── scripts/                # 用户脚本目录
├── tests/                  # 测试代码
├── docker/                 # Docker配置
└── specs/                  # 规格说明文档
```

## 详细文档

- [架构设计](docs/architecture.md) - 系统架构和组件说明
- [API参考](docs/api-reference.md) - 完整的API文档
- [扩展开发](docs/extending.md) - 如何添加新功能块
- [性能基准](docs/benchmark-results.md) - 性能测试结果

## 功能块API

### PID控制器

```python
import plcopen

pid = plcopen.PID(
    kp=1.0,        # 比例增益
    ki=0.1,        # 积分增益
    kd=0.05,       # 微分增益
    out_min=-100,  # 输出下限
    out_max=100,   # 输出上限
    dt=0.1         # 采样周期（秒）
)

output = pid.execute(setpoint=100.0, pv=80.0)
print(f"控制输出: {output}, 偏差: {pid.error}, 限幅: {pid.saturated}")
```

### 一阶惯性滤波器

```python
import plcopen

filter = plcopen.FirstOrder(
    k=1.0,   # 增益
    t=0.5,   # 时间常数（秒）
    dt=0.1   # 采样周期（秒）
)

# 阶跃响应
for i in range(20):
    output = filter.execute(100.0)
    print(f"Step {i}: {output:.2f}")
```

## VSCode远程调试

1. 启动运行时（调试模式已启用）
2. 在VSCode中按 `F5` 附加调试器
3. 在脚本中设置断点
4. 脚本执行到断点处将暂停

详见 [.vscode/launch.json](.vscode/launch.json) 配置。

## 热重载

运行时会自动监控 `scripts/` 目录：

- 修改脚本文件 → 自动重新加载（保留功能块状态）
- 添加新脚本 → 自动加载
- 删除脚本 → 自动卸载

```python
# 脚本中的功能块状态会在重载时保留
pid = plcopen.PID(kp=2.0, ki=0.1)

def main():
    # 重载后，pid 的积分器状态会恢复
    return pid.execute(setpoint=100, pv=read_sensor())
```

## 开发
# 构建ARM镜像

```bash
# 构建ARM交叉编译镜像
docker build -f docker/Dockerfile.arm -t plcopen-arm .

# 运行交叉编译
docker run --rm -v $(pwd):/app plcopen-arm \
    cmake -B build-arm -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm.cmake
```

## 性能

基于 x86_64 平台测试结果：

| 指标 | 结果 |
|------|------|
| PID 执行时间 | ~100 ns |
| FirstOrder 执行时间 | ~50 ns |
| PID 实例内存 | ~120 bytes |
| FirstOrder 实例内存 | ~48 bytes |

详见 [性能基准测试报告](docs/benchmark-results.md)。

##
### 运行测试

```bash
# C单元测试
cd build && ctest --output-on-failure

# Python测试
pytest tests/ -v
```

### 代码风格

```bash
# 检查Python代码
ruff check runtime/ tests/
mypy runtime/
```

## 许可证

MIT License - 详见 [LICENSE](LICENSE)

## 贡献

欢迎提交Issue和Pull Request！
