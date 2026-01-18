"""
PID温度控制示例脚本

演示如何使用 PLCOpen PID 功能块进行温度控制。
"""

# 注意：需要先构建 plcopen 扩展模块
# 在模块未构建时使用模拟实现
try:
    import plcopen

    PID = plcopen.PID
except ImportError:
    # 模拟 PID 实现（用于测试）
    class PID:
        def __init__(self, kp=1.0, ki=0.0, kd=0.0, out_min=-100, out_max=100, dt=0.1):
            self.kp = kp
            self.ki = ki
            self.kd = kd
            self.out_min = out_min
            self.out_max = out_max
            self.dt = dt
            self._integral = 0.0
            self._prev_error = 0.0
            self._output = 0.0

        def execute(self, setpoint, pv):
            error = setpoint - pv
            self._integral += error * self.dt
            derivative = (error - self._prev_error) / self.dt
            output = self.kp * error + self.ki * self._integral + self.kd * derivative
            output = max(self.out_min, min(self.out_max, output))
            self._prev_error = error
            self._output = output
            return output

        @property
        def output(self):
            return self._output

        def get_state(self):
            return {
                "integral": self._integral,
                "prev_error": self._prev_error,
                "prev_output": self._output,
            }

        def set_state(self, state):
            self._integral = state.get("integral", 0.0)
            self._prev_error = state.get("prev_error", 0.0)
            self._output = state.get("prev_output", 0.0)

        def reset(self):
            self._integral = 0.0
            self._prev_error = 0.0
            self._output = 0.0


# ============================================================================
# 控制器配置
# ============================================================================

# PID 参数（根据实际系统调整）
PID_KP = 2.0  # 比例增益
PID_KI = 0.1  # 积分增益
PID_KD = 0.5  # 微分增益
OUTPUT_MIN = 0.0  # 最小输出（加热功率 0%）
OUTPUT_MAX = 100.0  # 最大输出（加热功率 100%）
CYCLE_TIME = 0.1  # 控制周期 100ms

# 目标温度
SETPOINT = 60.0  # 目标温度 60°C

# ============================================================================
# 模拟过程
# ============================================================================


class TemperatureProcess:
    """
    温度过程模拟

    模拟一个简单的热系统：
    - 加热器功率与热输入成正比
    - 系统有热惯性（一阶延迟）
    - 存在热损失（与环境温度差成正比）
    """

    def __init__(
        self,
        initial_temp: float = 25.0,
        ambient_temp: float = 25.0,
        thermal_mass: float = 10.0,  # 热容（影响响应速度）
        heat_loss_coeff: float = 0.1,  # 热损失系数
        heater_power: float = 50.0,  # 加热器最大功率 (°C/s at 100%)
    ):
        self.temperature = initial_temp
        self.ambient_temp = ambient_temp
        self.thermal_mass = thermal_mass
        self.heat_loss_coeff = heat_loss_coeff
        self.heater_power = heater_power

    def update(self, heater_output: float, dt: float) -> float:
        """
        更新温度

        Args:
            heater_output: 加热器输出 (0-100%)
            dt: 时间步长 (秒)

        Returns:
            当前温度
        """
        # 加热器热输入
        heat_in = (heater_output / 100.0) * self.heater_power * dt

        # 热损失
        heat_loss = self.heat_loss_coeff * (self.temperature - self.ambient_temp) * dt

        # 温度变化
        delta_temp = (heat_in - heat_loss) / self.thermal_mass
        self.temperature += delta_temp

        return self.temperature


# ============================================================================
# 全局实例
# ============================================================================

# 创建 PID 控制器
pid = PID(
    kp=PID_KP,
    ki=PID_KI,
    kd=PID_KD,
    out_min=OUTPUT_MIN,
    out_max=OUTPUT_MAX,
    dt=CYCLE_TIME,
)

# 创建模拟过程
process = TemperatureProcess()

# 控制循环计数器
cycle_count = 0


# ============================================================================
# 主函数
# ============================================================================


def main():
    """
    主控制循环

    每个周期执行一次，由运行时调用。
    """
    global cycle_count

    cycle_count += 1

    # 读取当前温度（过程值）
    pv = process.temperature

    # 计算 PID 输出
    output = pid.execute(setpoint=SETPOINT, pv=pv)

    # 应用控制输出到过程
    process.update(output, CYCLE_TIME)

    # 每10个周期打印一次状态
    if cycle_count % 10 == 0:
        print(
            f"[周期 {cycle_count:4d}] "
            f"设定值: {SETPOINT:.1f}°C  "
            f"过程值: {pv:.2f}°C  "
            f"输出: {output:.1f}%  "
            f"偏差: {SETPOINT - pv:.2f}°C"
        )

    return {
        "cycle": cycle_count,
        "setpoint": SETPOINT,
        "pv": pv,
        "output": output,
        "error": SETPOINT - pv,
    }


# ============================================================================
# 测试代码
# ============================================================================

if __name__ == "__main__":
    print("PID 温度控制演示")
    print("=" * 60)
    print(f"目标温度: {SETPOINT}°C")
    print(f"初始温度: {process.temperature}°C")
    print(f"PID 参数: Kp={PID_KP}, Ki={PID_KI}, Kd={PID_KD}")
    print("=" * 60)

    # 运行100个周期（10秒）
    for _ in range(100):
        result = main()

    print("=" * 60)
    print(f"最终温度: {process.temperature:.2f}°C")
    print(f"目标温度: {SETPOINT}°C")
    print(f"稳态偏差: {abs(SETPOINT - process.temperature):.3f}°C")
