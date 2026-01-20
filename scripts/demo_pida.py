#!/usr/bin/env python3
"""
PIDA 功能块示例脚本

演示如何使用 PLCOpen PIDA 功能块进行工业过程控制。
包含以下示例：
  1. 单回路PID控制示例
  2. 手动/自动模式切换示例
  3. 四级报警功能示例
  4. 设定值爬坡功能示例
"""

import time
import math

# 注意：需要先构建 plcopen 扩展模块
# 在模块未构建时使用模拟实现
try:
    import plcopen
    PIDA = plcopen.PIDA
    # 模式常量
    MODE_MANUAL = plcopen.PIDA_MODE_MANUAL
    MODE_AUTO = plcopen.PIDA_MODE_AUTO
    MODE_CASCADE = plcopen.PIDA_MODE_CASCADE
    MODE_MANUAL_TRACK = plcopen.PIDA_MODE_MANUAL_TRACK
    MODE_AUTO_TRACK = plcopen.PIDA_MODE_AUTO_TRACK
    # 类型常量
    TYPE_SINGLE = plcopen.PIDA_TYPE_SINGLE
    TYPE_CASCADE_MASTER = plcopen.PIDA_TYPE_CASCADE_MASTER
    TYPE_CASCADE_SLAVE = plcopen.PIDA_TYPE_CASCADE_SLAVE
    TYPE_EXTERNAL_SP = plcopen.PIDA_TYPE_EXTERNAL_SP
    # 公式常量
    EQN_STANDARD = plcopen.PIDA_EQN_STANDARD
    EQN_DERIVATIVE_FIRST = plcopen.PIDA_EQN_DERIVATIVE_FIRST
    EQN_PD_FIRST = plcopen.PIDA_EQN_PD_FIRST
except ImportError:
    print("警告: plcopen 扩展模块未构建，使用模拟实现")
    
    # 模式常量
    MODE_MANUAL = 0
    MODE_AUTO = 1
    MODE_CASCADE = 2
    MODE_MANUAL_TRACK = 3
    MODE_AUTO_TRACK = 4
    # 类型常量
    TYPE_SINGLE = 0
    TYPE_CASCADE_MASTER = 1
    TYPE_CASCADE_SLAVE = 2
    TYPE_EXTERNAL_SP = 3
    # 公式常量
    EQN_STANDARD = 0
    EQN_DERIVATIVE_FIRST = 1
    EQN_PD_FIRST = 2
    
    class PIDA:
        """PIDA模拟实现"""
        def __init__(self, kp=100.0, ti=30.0, td=0.0, kd=1.0,
                     pvu=100.0, pvl=0.0, engu=100.0, engl=0.0,
                     outu=100.0, outl=0.0, spu=100.0, spl=0.0,
                     pidtype=0, eqn=0, outopt=0, actopt=1, cyc=0.5):
            self.kp = kp
            self.ti = ti
            self.td = td
            self.kd = kd
            self.pvu = pvu
            self.pvl = pvl
            self.engu = engu
            self.engl = engl
            self.outu = outu
            self.outl = outl
            self.spu = spu
            self.spl = spl
            self.pidtype = pidtype
            self.eqn = eqn
            self.outopt = outopt
            self.actopt = actopt
            self.cyc = cyc
            # 内部状态
            self._sp = 50.0
            self._mode = MODE_MANUAL
            self._output = 50.0
            self._error = 0.0
            self._integral = 0.0
            self._prev_error = 0.0
            self._bypass = False
            # 报警状态
            self._hhind = False
            self._ahind = False
            self._alind = False
            self._llind = False
            self._da = False
            self._am = 0
            self._ove = 0
            # 爬坡状态
            self._ramp_active = False
            self._ramp_target = 0.0
            self._ramp_rate = 0.0
        
        @property
        def sp(self):
            return self._sp
        
        @sp.setter
        def sp(self, value):
            self._sp = max(self.spl, min(self.spu, value))
        
        @property
        def mode(self):
            return self._mode
        
        @mode.setter
        def mode(self, value):
            self._mode = value
        
        @property
        def output(self):
            return self._output
        
        @property
        def out(self):
            return self._output
        
        @property
        def error(self):
            return self._error
        
        @property
        def ek(self):
            return self._error
        
        @property
        def hhind(self):
            return self._hhind
        
        @property
        def ahind(self):
            return self._ahind
        
        @property
        def alind(self):
            return self._alind
        
        @property
        def llind(self):
            return self._llind
        
        @property
        def da(self):
            return self._da
        
        @property
        def am(self):
            return self._am
        
        @property
        def ove(self):
            return self._ove
        
        @property
        def bypass(self):
            return self._bypass
        
        @bypass.setter
        def bypass(self, value):
            self._bypass = bool(value)
        
        def execute(self, pv, mout=0.0, sp=None, mode=None, **kwargs):
            """执行一次PID计算"""
            if sp is not None:
                self._sp = sp
            if mode is not None:
                self._mode = mode
            
            # 爬坡处理
            if self._ramp_active:
                if self._ramp_rate > 0:
                    if self._sp < self._ramp_target:
                        self._sp = min(self._sp + self._ramp_rate * self.cyc, self._ramp_target)
                    else:
                        self._ramp_active = False
                elif self._ramp_rate < 0:
                    if self._sp > self._ramp_target:
                        self._sp = max(self._sp + self._ramp_rate * self.cyc, self._ramp_target)
                    else:
                        self._ramp_active = False
            
            # 计算偏差
            if self.actopt:  # 反作用
                self._error = self._sp - pv
            else:  # 正作用
                self._error = pv - self._sp
            
            # 模式处理
            if self._mode == MODE_MANUAL:
                self._output = mout
            elif self._mode in (MODE_AUTO, MODE_CASCADE):
                # PID计算
                span = self.pvu - self.pvl
                if span > 0:
                    err_pct = self._error / span * 100.0
                else:
                    err_pct = 0.0
                
                # 比例项
                p_term = 100.0 / self.kp * err_pct if self.kp > 0 else 0.0
                
                # 积分项
                if self.ti > 0:
                    self._integral += err_pct * self.cyc / self.ti
                i_term = self._integral
                
                # 微分项
                if self.td > 0 and self.cyc > 0:
                    d_term = self.kd * self.td * (err_pct - self._prev_error) / self.cyc
                else:
                    d_term = 0.0
                
                self._output = (p_term + i_term + d_term)
                
                # 限幅
                if self._output > self.outu:
                    self._output = self.outu
                    self._ove |= 0x01
                elif self._output < self.outl:
                    self._output = self.outl
                    self._ove |= 0x02
                
                self._prev_error = err_pct
            
            return self._output
        
        def reset(self):
            """复位控制器"""
            self._integral = 0.0
            self._prev_error = 0.0
            self._output = 50.0
            self._mode = MODE_MANUAL
            self._ramp_active = False
        
        def start_ramp(self, target, time_or_rate, rtyp=True):
            """启动设定值爬坡
            
            Args:
                target: 目标设定值
                time_or_rate: 时间(分钟)或速率(单位/秒)
                rtyp: True=速率方式, False=时间方式
            """
            self._ramp_target = target
            if rtyp:
                # 速率方式
                self._ramp_rate = time_or_rate
            else:
                # 时间方式：计算速率
                if time_or_rate > 0:
                    self._ramp_rate = (target - self._sp) / (time_or_rate * 60.0)
                else:
                    self._ramp_rate = 0.0
            self._ramp_active = True
        
        def stop_ramp(self):
            """停止设定值爬坡"""
            self._ramp_active = False
        
        def get_state(self):
            """获取控制器状态"""
            return {
                "sp": self._sp,
                "mode": self._mode,
                "output": self._output,
                "error": self._error,
                "integral": self._integral,
                "hhind": self._hhind,
                "ahind": self._ahind,
                "alind": self._alind,
                "llind": self._llind,
            }
        
        def set_state(self, state):
            """设置控制器状态"""
            if "sp" in state:
                self._sp = state["sp"]
            if "mode" in state:
                self._mode = state["mode"]
            if "output" in state:
                self._output = state["output"]
            if "integral" in state:
                self._integral = state["integral"]


def print_separator(title):
    """打印分隔线"""
    print()
    print("=" * 60)
    print(f" {title}")
    print("=" * 60)


def demo_single_loop_pid():
    """
    示例1: 单回路PID控制
    
    模拟温度控制场景：
    - 设定温度 60°C
    - 初始温度 25°C  
    - 使用PID控制加热器功率
    """
    print_separator("示例1: 单回路PID温度控制")
    
    # 创建PIDA实例
    # kp=100%: 比例带宽度
    # ti=30s: 积分时间
    # td=5s: 微分时间
    # pvu/pvl: 温度量程 0-100°C
    # outu/outl: 加热器功率 0-100%
    pida = PIDA(
        kp=100.0,      # 比例带 100%
        ti=30.0,       # 积分时间 30秒
        td=5.0,        # 微分时间 5秒
        kd=1.0,        # 微分增益
        pvu=100.0,     # 温度上限 100°C
        pvl=0.0,       # 温度下限 0°C
        engu=100.0,    # 输出量程上限
        engl=0.0,      # 输出量程下限
        outu=100.0,    # 输出上限 100%
        outl=0.0,      # 输出下限 0%
        pidtype=TYPE_SINGLE,      # 单回路
        eqn=EQN_STANDARD,         # 标准PID
        actopt=1,                 # 反作用（温度低时加热）
        cyc=0.5,                  # 计算周期 500ms
    )
    
    # 初始条件
    temperature = 25.0  # 当前温度
    setpoint = 60.0     # 目标温度
    heater_power = 0.0  # 加热器功率
    
    # 设置为自动模式
    pida.sp = setpoint
    pida.mode = MODE_AUTO
    
    print(f"目标温度: {setpoint}°C")
    print(f"初始温度: {temperature}°C")
    print()
    print("时间(s) | 温度(°C) | 偏差(°C) | 加热功率(%)")
    print("-" * 50)
    
    # 仿真参数
    dt = 0.5  # 控制周期 500ms
    thermal_capacity = 100.0  # 热容
    heat_transfer = 2.0  # 传热系数
    ambient = 25.0  # 环境温度
    
    for step in range(40):
        t = step * dt
        
        # 执行PID计算
        heater_power = pida.execute(pv=temperature)
        
        # 过程仿真：一阶惯性 + 加热/散热
        heat_in = heater_power * 0.5  # 加热器功率转换为热量
        heat_out = heat_transfer * (temperature - ambient)  # 散热
        d_temp = (heat_in - heat_out) / thermal_capacity * dt
        temperature += d_temp
        
        if step % 4 == 0:  # 每2秒打印一次
            print(f"{t:7.1f} | {temperature:8.2f} | {pida.error:8.2f} | {heater_power:11.2f}")
            time.sleep(0.3)  # 延时便于观察
    
    print()
    print(f"最终温度: {temperature:.2f}°C")
    print(f"稳态偏差: {pida.error:.2f}°C")


def demo_mode_switching():
    """
    示例2: 手动/自动模式切换
    
    演示：
    - 手动模式下调整输出
    - 从手动切换到自动（无扰切换）
    - 自动模式下设定值调整
    """
    print_separator("示例2: 手动/自动模式切换")
    
    pida = PIDA(
        kp=100.0,
        ti=20.0,
        pvu=100.0, pvl=0.0,
        outu=100.0, outl=0.0,
        pidtype=TYPE_SINGLE,
        actopt=1,
        cyc=0.5,
    )
    
    # 过程变量模拟值
    pv = 45.0
    
    print("阶段1: 手动模式控制")
    print("-" * 40)
    pida.mode = MODE_MANUAL
    
    # 手动调整输出
    for mout in [30.0, 40.0, 50.0]:
        output = pida.execute(pv=pv)
        print(f"手动输出设定: {mout}% → 实际输出: {output}%")
    
    print()
    print("阶段2: 手动→自动无扰切换")
    print("-" * 40)
    
    # 设置设定值接近当前PV（无扰切换）
    pida.sp = pv
    print(f"切换前: PV={pv}%, 输出={pida.output}%")
    
    # 切换到自动
    pida.mode = MODE_AUTO
    output = pida.execute(pv=pv)
    print(f"切换后: SP={pida.sp}%, 模式=自动, 输出={output:.2f}%")
    
    print()
    print("阶段3: 自动模式下调整设定值")
    print("-" * 40)
    
    # 调整设定值
    pida.sp = 50.0
    for _ in range(5):
        pv += (pida.output - 50.0) * 0.02  # 模拟过程响应
        output = pida.execute(pv=pv)
        print(f"SP={pida.sp}%, PV={pv:.2f}%, 偏差={pida.error:.2f}%, 输出={output:.2f}%")


def demo_four_level_alarm():
    """
    示例3: 四级报警功能
    
    演示：
    - HH (高高限) 报警
    - AH (高限) 报警  
    - AL (低限) 报警
    - LL (低低限) 报警
    """
    print_separator("示例3: 四级过程值报警")
    
    # 注意：报警功能需要通过参数配置
    # 这里演示报警状态读取
    pida = PIDA(
        kp=100.0,
        ti=30.0,
        pvu=100.0, pvl=0.0,
        outu=100.0, outl=0.0,
        pidtype=TYPE_SINGLE,
        cyc=0.5,
    )
    
    print("报警限值配置:")
    print("  LL (低低限): 10%")
    print("  AL (低限):   20%")
    print("  AH (高限):   80%")
    print("  HH (高高限): 90%")
    print()
    
    # 模拟不同PV值下的报警状态
    test_values = [5.0, 15.0, 50.0, 85.0, 95.0]
    
    print("PV值 | LL | AL | AH | HH | AM(报警字)")
    print("-" * 50)
    
    for pv in test_values:
        pida.execute(pv=pv)
        
        # 读取报警状态
        ll = "●" if pida.llind else "○"
        al = "●" if pida.alind else "○"
        ah = "●" if pida.ahind else "○"
        hh = "●" if pida.hhind else "○"
        am = pida.am
        
        print(f"{pv:5.1f} | {ll:^2} | {al:^2} | {ah:^2} | {hh:^2} | 0x{am:04X}")
    
    print()
    print("说明: ● = 报警激活, ○ = 正常")


def demo_setpoint_ramp():
    """
    示例4: 设定值爬坡功能
    
    演示：
    - 启动设定值爬坡
    - 爬坡过程监控
    - 到达目标后停止
    """
    print_separator("示例4: 设定值爬坡功能")
    
    pida = PIDA(
        kp=100.0,
        ti=30.0,
        pvu=100.0, pvl=0.0,
        outu=100.0, outl=0.0,
        pidtype=TYPE_SINGLE,
        actopt=1,
        cyc=0.5,
    )
    
    # 初始设定值
    pida.sp = 30.0
    pida.mode = MODE_AUTO
    
    print(f"初始设定值: {pida.sp}%")
    print(f"目标设定值: 70%")
    print(f"爬坡速率: 5%/秒")
    print()
    
    # 启动爬坡
    # 目标值 70%, 速率 5%/秒 (rtyp=True表示速率方式)
    pida.start_ramp(target=70.0, time_or_rate=5.0, rtyp=True)
    
    print("时间(s) | 设定值(%) | 状态")
    print("-" * 40)
    
    pv = 30.0  # 初始PV跟随SP
    
    for step in range(20):
        t = step * 0.5
        
        # 执行PID（内部会处理爬坡）
        output = pida.execute(pv=pv)
        
        # 简单过程响应
        pv += (pida.sp - pv) * 0.1
        
        # 判断爬坡状态
        if pida.sp >= 70.0:
            status = "到达目标"
            pida.stop_ramp()
        else:
            status = "爬坡中..."
        
        if step % 2 == 0:
            print(f"{t:7.1f} | {pida.sp:9.2f} | {status}")
            time.sleep(0.3)  # 延时便于观察
    
    print()
    print(f"最终设定值: {pida.sp}%")


def demo_state_save_restore():
    """
    示例5: 状态保存与恢复
    
    演示：
    - 获取控制器状态
    - 保存状态
    - 恢复状态实现无扰切换
    """
    print_separator("示例5: 状态保存与恢复")
    
    # 创建并运行一段时间
    pida1 = PIDA(kp=100.0, ti=30.0, cyc=0.5)
    pida1.sp = 50.0
    pida1.mode = MODE_AUTO
    
    # 运行几个周期
    pv = 45.0
    for _ in range(10):
        pida1.execute(pv=pv)
        pv += (pida1.output - 50.0) * 0.01
    
    # 获取状态
    state = pida1.get_state()
    print("保存的状态:")
    for key, value in state.items():
        if isinstance(value, float):
            print(f"  {key}: {value:.4f}")
        else:
            print(f"  {key}: {value}")
    
    print()
    
    # 创建新实例并恢复状态
    pida2 = PIDA(kp=100.0, ti=30.0, cyc=0.5)
    pida2.set_state(state)
    
    print("恢复后验证:")
    print(f"  SP: {pida2.sp}")
    print(f"  Mode: {pida2.mode}")
    print(f"  Output: {pida2.output:.4f}")
    
    # 继续执行，验证无扰
    output_before = pida2.output
    pida2.execute(pv=pv)
    output_after = pida2.output
    
    print(f"\n继续执行: 恢复前输出={output_before:.4f}, 恢复后输出={output_after:.4f}")
    print(f"输出变化: {abs(output_after - output_before):.4f} (应该很小)")


def main():
    """运行所有示例"""
    print()
    print("╔════════════════════════════════════════════════════════════╗")
    print("║          PLCOpen PIDA 功能块示例程序                       ║")
    print("║          基于IEC61131-3标准的工业级PID控制器                ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    # 运行各示例
    demo_single_loop_pid()
    demo_mode_switching()
    demo_four_level_alarm()
    demo_setpoint_ramp()
    
    # 注意: demo_state_save_restore() 需要 set_state 方法
    # 模拟实现支持，C 扩展暂未实现
    try:
        demo_state_save_restore()
    except AttributeError as e:
        print()
        print("=" * 60)
        print(" 示例5: 状态保存与恢复")
        print("=" * 60)
        print(f"跳过: {e}")
        print("(C扩展暂不支持 set_state 方法)")
    
    print()
    print("=" * 60)
    print("所有示例运行完成！")
    print("=" * 60)


if __name__ == "__main__":
    main()
