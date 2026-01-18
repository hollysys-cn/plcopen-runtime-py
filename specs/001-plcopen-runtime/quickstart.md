# PLCOpen运行时 - 快速入门

**日期**: 2026-01-18
**版本**: 1.0

## 前提条件

- Docker 20.10+ 和 Docker Compose 2.0+
- VSCode（可选，用于远程调试）
- Git

## 1. 获取代码

```bash
git clone <repository-url>
cd plcopen-runtime-py
git checkout 001-plcopen-runtime
```

## 2. 启动开发环境

### 使用Docker Compose（推荐）

```bash
# 构建并启动开发容器
docker compose up -d --build

# 查看日志
docker compose logs -f
```

首次构建约需5-10分钟（使用国内镜像加速）。

### 验证环境

```bash
# 进入容器
docker compose exec plcopen-dev bash

# 验证Python扩展已加载
python -c "import plcopen; print('PLCOpen模块加载成功')"
```

## 3. 创建第一个控制脚本

在 `scripts/` 目录下创建文件 `demo.py`：

```python
"""
示例控制脚本 - PID温度控制。
"""
import plcopen

# 创建PID控制器实例
pid = plcopen.PID(
    kp=2.0,      # 比例增益
    ki=0.5,      # 积分增益
    kd=0.1,      # 微分增益
    out_min=0,   # 输出下限（加热功率最小0%）
    out_max=100  # 输出上限（加热功率最大100%）
)

# 创建一阶惯性滤波器（平滑输出）
output_filter = plcopen.FirstOrder(k=1.0, t=0.3)

# 模拟变量
setpoint = 50.0  # 设定温度
temperature = 25.0  # 当前温度（模拟）

def main():
    """主循环函数，由运行时按周期调用。"""
    global temperature

    # 执行PID计算
    heater_power = pid.execute(setpoint=setpoint, pv=temperature)

    # 滤波输出
    filtered_power = output_filter.execute(heater_power)

    # 模拟温度响应（简化模型）
    temperature += (filtered_power * 0.1 - (temperature - 20) * 0.05) * 0.1

    # 打印状态（每秒一次，假设100ms周期）
    import time
    if int(time.time() * 10) % 10 == 0:
        print(f"设定: {setpoint:.1f}°C, 当前: {temperature:.1f}°C, "
              f"输出: {filtered_power:.1f}%, 限幅: {pid.saturated}")

def on_reload(saved_states):
    """热重载回调。"""
    print(f"脚本已重新加载，功能块状态已保留")
```

## 4. 运行脚本

脚本会在运行时自动检测到（约1秒内）并开始执行。

查看输出：
```bash
docker compose logs -f
```

预期输出：
```
设定: 50.0°C, 当前: 25.3°C, 输出: 100.0%, 限幅: True
设定: 50.0°C, 当前: 26.1°C, 输出: 100.0%, 限幅: True
...
设定: 50.0°C, 当前: 49.8°C, 输出: 52.3%, 限幅: False
设定: 50.0°C, 当前: 50.1°C, 输出: 48.7%, 限幅: False
```

## 5. 热重载测试

修改 `scripts/demo.py` 中的设定值：
```python
setpoint = 60.0  # 修改设定温度
```

保存后，观察日志：
```
脚本已重新加载，功能块状态已保留
设定: 60.0°C, 当前: 50.2°C, 输出: 75.1%, 限幅: False
```

注意：PID的积分状态被保留，不会出现积分重置导致的跳变。

## 6. VSCode远程调试

### 配置调试器

在VSCode中打开项目，创建 `.vscode/launch.json`：

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

### 启动调试

1. 确保容器正在运行
2. 在VSCode中按 `F5` 或选择 "Run > Start Debugging"
3. 在 `scripts/demo.py` 中设置断点
4. 断点会在下一个执行周期触发

### 调试技巧

- 使用条件断点：`temperature > 45` 仅在特定条件下暂停
- 使用日志点：不暂停执行，仅打印信息
- 查看PID内部状态：在调试控制台执行 `pid.get_state()`

## 7. 常用命令

```bash
# 重新构建（代码变更后）
docker compose build

# 查看实时日志
docker compose logs -f

# 进入容器Shell
docker compose exec plcopen-dev bash

# 停止环境
docker compose down

# 清理所有数据
docker compose down -v
```

## 8. 项目结构

```
plcopen-runtime-py/
├── src/                      # C源代码
│   ├── fb/                   # 功能块实现
│   │   ├── pid.c
│   │   └── first_order.c
│   ├── runtime/              # 运行时核心
│   └── python/               # Python扩展
├── include/                  # C头文件
├── runtime/                  # Python运行时模块
│   ├── __init__.py
│   ├── main.py
│   └── script_manager.py
├── scripts/                  # 用户脚本目录（热加载）
├── tests/                    # 测试代码
│   ├── unit/                 # 单元测试
│   └── integration/          # 集成测试
├── docker/                   # Docker配置
│   ├── Dockerfile.dev
│   └── Dockerfile.arm
├── cmake/                    # CMake配置
├── docker-compose.yml
├── CMakeLists.txt
└── pyproject.toml
```

## 9. 下一步

- 阅读 [Python API文档](contracts/python-api.md) 了解完整API
- 阅读 [数据模型](data-model.md) 了解系统设计
- 阅读 [技术研究报告](research.md) 了解技术决策

## 故障排除

### 容器启动失败

```bash
# 检查Docker状态
docker info

# 查看构建日志
docker compose build --no-cache 2>&1 | tee build.log
```

### 脚本未被加载

1. 确认脚本在 `scripts/` 目录下
2. 确认脚本扩展名为 `.py`
3. 确认脚本定义了 `main()` 函数
4. 查看日志中的错误信息

### 调试器无法连接

1. 确认容器端口5678已映射
2. 确认防火墙允许该端口
3. 尝试直接连接测试：`nc -zv localhost 5678`
