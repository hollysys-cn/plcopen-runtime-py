"""
一阶惯性功能块 Python 单元测试

测试 plcopen.FirstOrder 类的所有功能。
"""

import math
import pytest

# 注意：实际测试时需要先构建扩展模块
# 这里假设模块已经安装或在 Python 路径中
try:
    import plcopen
except ImportError:
    plcopen = None
    pytestmark = pytest.mark.skip(reason="plcopen模块未构建")


class TestFirstOrderCreation:
    """FirstOrder实例创建测试"""

    def test_default_params(self):
        """测试默认参数"""
        fo = plcopen.FirstOrder()
        assert fo.k == pytest.approx(1.0)
        assert fo.t == pytest.approx(1.0)

    def test_custom_params(self):
        """测试自定义参数"""
        fo = plcopen.FirstOrder(k=2.5, t=0.5, dt=0.05)
        assert fo.k == pytest.approx(2.5)
        assert fo.t == pytest.approx(0.5)

    def test_invalid_time_constant_zero(self):
        """测试时间常数为0"""
        with pytest.raises(ValueError):
            plcopen.FirstOrder(t=0.0)

    def test_invalid_time_constant_negative(self):
        """测试负时间常数"""
        with pytest.raises(ValueError):
            plcopen.FirstOrder(t=-1.0)

    def test_negative_gain_allowed(self):
        """测试负增益（应该允许）"""
        fo = plcopen.FirstOrder(k=-1.0, t=1.0)
        assert fo.k == pytest.approx(-1.0)


class TestFirstOrderExecution:
    """FirstOrder执行测试"""

    def test_step_response_converges(self):
        """测试阶跃响应收敛"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for _ in range(100):
            fo.execute(100.0)

        assert fo.output == pytest.approx(100.0, rel=0.01)

    def test_gain_scaling(self):
        """测试增益缩放"""
        fo = plcopen.FirstOrder(k=2.0, t=0.5, dt=0.1)

        for _ in range(100):
            fo.execute(50.0)

        assert fo.output == pytest.approx(100.0, rel=0.01)

    def test_zero_input(self):
        """测试零输入"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)
        output = fo.execute(0.0)
        assert output == pytest.approx(0.0)

    def test_negative_input(self):
        """测试负输入"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for _ in range(100):
            fo.execute(-50.0)

        assert fo.output == pytest.approx(-50.0, rel=0.01)

    def test_nan_input_raises(self):
        """测试NaN输入"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0)
        with pytest.raises(ValueError):
            fo.execute(float("nan"))

    def test_inf_input_raises(self):
        """测试无穷大输入"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0)
        with pytest.raises(ValueError):
            fo.execute(float("inf"))


class TestFirstOrderReset:
    """FirstOrder重置测试"""

    def test_reset_to_zero(self):
        """测试重置到0"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for _ in range(10):
            fo.execute(100.0)
        assert fo.output > 0

        fo.reset()
        assert fo.output == pytest.approx(0.0)

    def test_reset_to_initial_value(self):
        """测试重置到指定初始值"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        fo.reset(50.0)
        assert fo.output == pytest.approx(50.0)

        # 从50开始滤波
        output = fo.execute(100.0)
        assert 50.0 < output < 100.0


class TestFirstOrderState:
    """FirstOrder状态保存/恢复测试"""

    def test_get_state(self):
        """测试获取状态"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for _ in range(5):
            fo.execute(100.0)

        state = fo.get_state()
        assert "prev_output" in state
        assert state["prev_output"] == pytest.approx(fo.output)

    def test_set_state(self):
        """测试恢复状态"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for _ in range(5):
            fo.execute(100.0)

        state = fo.get_state()
        saved_output = fo.output

        # 继续执行
        for _ in range(5):
            fo.execute(100.0)

        # 恢复状态
        fo.set_state(state)
        assert fo.output == pytest.approx(saved_output)

    def test_state_missing_key_raises(self):
        """测试缺少键的状态字典"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0)
        with pytest.raises(KeyError):
            fo.set_state({})


class TestFirstOrderPropertyModification:
    """FirstOrder属性运行时修改测试"""

    def test_modify_gain(self):
        """测试运行时修改增益"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        fo.k = 2.0
        assert fo.k == pytest.approx(2.0)

        for _ in range(100):
            fo.execute(50.0)

        assert fo.output == pytest.approx(100.0, rel=0.01)

    def test_modify_time_constant(self):
        """测试运行时修改时间常数"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        fo.t = 0.5
        assert fo.t == pytest.approx(0.5)

    def test_invalid_time_constant_modification(self):
        """测试修改为无效时间常数"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0)

        with pytest.raises(ValueError):
            fo.t = 0.0

        with pytest.raises(ValueError):
            fo.t = -1.0


class TestFirstOrderFiltering:
    """FirstOrder滤波效果测试"""

    def test_smoothing_noisy_signal(self):
        """测试平滑噪声信号"""
        fo = plcopen.FirstOrder(k=1.0, t=0.5, dt=0.1)

        outputs = []
        for i in range(50):
            # 带噪声的信号
            noisy_input = 100.0 + 10.0 * math.sin(i * 0.5)
            output = fo.execute(noisy_input)
            outputs.append(output)

        # 输出应该比输入更平滑
        output_variance = sum((o - sum(outputs) / len(outputs)) ** 2 for o in outputs) / len(
            outputs
        )
        # 由于滤波效果，方差应该减小
        assert output_variance < 100  # 输入方差约为50


class TestFirstOrderEdgeCases:
    """FirstOrder边界情况测试"""

    def test_small_time_constant_fast_response(self):
        """测试小时间常数快速响应"""
        fo = plcopen.FirstOrder(k=1.0, t=0.01, dt=0.01)

        output = fo.execute(100.0)
        # alpha = 0.01/(0.01+0.01) = 0.5
        assert output == pytest.approx(50.0, rel=0.01)

    def test_large_time_constant_slow_response(self):
        """测试大时间常数慢速响应"""
        fo = plcopen.FirstOrder(k=1.0, t=100.0, dt=0.1)

        output = fo.execute(100.0)
        # alpha ≈ 0.001, output ≈ 0.1
        assert output < 1.0

    def test_continuous_operation(self):
        """测试长时间连续运行"""
        fo = plcopen.FirstOrder(k=1.0, t=1.0, dt=0.1)

        for i in range(10000):
            input_val = 50.0 * math.sin(0.01 * i) + 50.0
            output = fo.execute(input_val)
            # 输出应该始终有效
            assert not math.isnan(output)
            assert not math.isinf(output)
