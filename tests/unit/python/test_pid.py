"""
PID功能块 Python绑定单元测试

测试Python层面的PID类功能。
"""

import math
import pytest


class TestPIDCreation:
    """PID实例创建测试"""

    def test_create_with_defaults(self):
        """测试使用默认参数创建PID"""
        import plcopen

        pid = plcopen.PID()
        assert pid.kp == 1.0
        assert pid.ki == 0.0
        assert pid.kd == 0.0
        assert math.isinf(pid.out_min) and pid.out_min < 0
        assert math.isinf(pid.out_max) and pid.out_max > 0

    def test_create_with_custom_params(self):
        """测试使用自定义参数创建PID"""
        import plcopen

        pid = plcopen.PID(kp=2.0, ki=0.5, kd=0.1, out_min=0, out_max=100, dt=0.05)
        assert pid.kp == 2.0
        assert pid.ki == 0.5
        assert pid.kd == 0.1
        assert pid.out_min == 0.0
        assert pid.out_max == 100.0

    def test_create_with_invalid_kp(self):
        """测试负Kp参数应抛出异常"""
        import plcopen

        with pytest.raises(ValueError):
            plcopen.PID(kp=-1.0)

    def test_create_with_invalid_limits(self):
        """测试无效输出限幅应抛出异常"""
        import plcopen

        with pytest.raises(ValueError):
            plcopen.PID(out_min=100, out_max=50)


class TestPIDExecution:
    """PID执行测试"""

    def test_proportional_control(self):
        """测试比例控制"""
        import plcopen

        pid = plcopen.PID(kp=2.0, ki=0.0, kd=0.0)
        output = pid.execute(setpoint=100.0, pv=80.0)

        # error = 20, output = 2.0 * 20 = 40
        assert output == pytest.approx(40.0)
        assert pid.error == pytest.approx(20.0)
        assert not pid.saturated

    def test_integral_accumulation(self):
        """测试积分累积"""
        import plcopen

        pid = plcopen.PID(kp=0.0, ki=1.0, kd=0.0, dt=0.1)

        # 第一次: integral = 20 * 0.1 = 2
        output1 = pid.execute(setpoint=100.0, pv=80.0)
        assert output1 == pytest.approx(2.0)

        # 第二次: integral = 2 + 2 = 4
        output2 = pid.execute(setpoint=100.0, pv=80.0)
        assert output2 == pytest.approx(4.0)

    def test_output_saturation(self):
        """测试输出限幅"""
        import plcopen

        pid = plcopen.PID(kp=10.0, out_min=0.0, out_max=100.0)
        output = pid.execute(setpoint=100.0, pv=50.0)

        # output = 10 * 50 = 500, 限幅到100
        assert output == pytest.approx(100.0)
        assert pid.saturated

    def test_nan_input_raises(self):
        """测试NaN输入应抛出异常"""
        import plcopen

        pid = plcopen.PID()
        with pytest.raises(ValueError):
            pid.execute(setpoint=float("nan"), pv=80.0)

    def test_inf_input_raises(self):
        """测试无穷输入应抛出异常"""
        import plcopen

        pid = plcopen.PID()
        with pytest.raises(ValueError):
            pid.execute(setpoint=float("inf"), pv=80.0)


class TestPIDReset:
    """PID重置测试"""

    def test_reset_clears_state(self):
        """测试重置清除内部状态"""
        import plcopen

        pid = plcopen.PID(kp=1.0, ki=1.0, dt=0.1)

        # 执行几次累积状态
        pid.execute(setpoint=100.0, pv=80.0)
        pid.execute(setpoint=100.0, pv=80.0)

        # 保存输出值
        old_output = pid.output

        # 重置
        pid.reset()

        # 重新执行，输出应该和第一次一样
        new_output = pid.execute(setpoint=100.0, pv=80.0)
        first_output = 1.0 * 20 + 1.0 * (20 * 0.1)  # kp*e + ki*integral
        assert new_output == pytest.approx(first_output)


class TestPIDState:
    """PID状态保存/恢复测试（热重载支持）"""

    def test_get_state(self):
        """测试获取状态"""
        import plcopen

        pid = plcopen.PID(kp=1.0, ki=1.0, dt=0.1)
        pid.execute(setpoint=100.0, pv=80.0)
        pid.execute(setpoint=100.0, pv=80.0)

        state = pid.get_state()
        assert "integral" in state
        assert "prev_error" in state
        assert "prev_output" in state
        assert state["integral"] == pytest.approx(4.0)  # 2 * (20 * 0.1)

    def test_set_state(self):
        """测试恢复状态"""
        import plcopen

        pid1 = plcopen.PID(kp=1.0, ki=1.0, dt=0.1)
        pid1.execute(setpoint=100.0, pv=80.0)
        pid1.execute(setpoint=100.0, pv=80.0)

        state = pid1.get_state()

        # 创建新实例并恢复状态
        pid2 = plcopen.PID(kp=1.0, ki=1.0, dt=0.1)
        pid2.set_state(state)

        # 两个实例执行相同输入应产生相同输出
        output1 = pid1.execute(setpoint=100.0, pv=80.0)
        output2 = pid2.execute(setpoint=100.0, pv=80.0)

        assert output1 == pytest.approx(output2)


class TestPIDPropertyModification:
    """PID属性动态修改测试"""

    def test_modify_kp(self):
        """测试动态修改Kp"""
        import plcopen

        pid = plcopen.PID(kp=1.0)
        pid.kp = 2.0
        assert pid.kp == 2.0

        output = pid.execute(setpoint=100.0, pv=80.0)
        assert output == pytest.approx(40.0)  # 2.0 * 20

    def test_modify_kp_invalid(self):
        """测试设置无效Kp应抛出异常"""
        import plcopen

        pid = plcopen.PID()
        with pytest.raises(ValueError):
            pid.kp = -1.0

    def test_readonly_output_property(self):
        """测试输出属性为只读"""
        import plcopen

        pid = plcopen.PID()
        pid.execute(setpoint=100.0, pv=80.0)

        with pytest.raises(AttributeError):
            pid.output = 50.0
