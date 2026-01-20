"""
PIDA功能块Python绑定单元测试

测试PIDA类的Python接口和功能正确性。
"""

import pytest
import math


class TestPIDACreation:
    """PIDA实例创建测试"""
    
    def test_create_default_instance(self):
        """测试默认参数创建实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        pida = PIDA()
        assert pida is not None
    
    def test_create_with_params(self):
        """测试指定参数创建实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        pida = PIDA(kp=200.0, ti=60.0, td=5.0)
        assert pida is not None
    
    def test_create_with_invalid_kp(self):
        """测试无效KP参数"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        with pytest.raises(ValueError):
            PIDA(kp=-1.0)


class TestPIDAExecution:
    """PIDA执行测试"""
    
    @pytest.fixture
    def pida(self):
        """创建PIDA测试实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        return PIDA(kp=100.0, ti=30.0, td=0.0, cyc=0.5)
    
    def test_execute_returns_float(self, pida):
        """测试execute返回浮点数"""
        result = pida.execute(pv=50.0, sp=50.0)
        assert isinstance(result, float)
    
    def test_execute_steady_state(self, pida):
        """测试稳态运行（无偏差）"""
        for _ in range(10):
            pida.execute(pv=50.0, sp=50.0)
        
        # 无偏差时，误差应接近0
        assert abs(pida.error) < 0.1
    
    def test_execute_with_error(self, pida):
        """测试有偏差时的响应"""
        pida.execute(pv=40.0, sp=50.0)
        
        # 偏差应为10
        assert abs(pida.error - 10.0) < 0.1
    
    def test_output_upper_limit(self, pida):
        """测试输出上限"""
        # 大偏差让输出饱和
        for _ in range(100):
            pida.execute(pv=0.0, sp=100.0)
        
        # 输出不应超过100（默认OUTU）
        assert pida.output <= 100.0


class TestPIDAModes:
    """PIDA模式切换测试"""
    
    @pytest.fixture
    def pida(self):
        """创建PIDA测试实例"""
        try:
            from plcopen import PIDA, PIDA_MODE_MANUAL, PIDA_MODE_AUTO
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        return PIDA()
    
    def test_get_mode(self, pida):
        """测试获取模式"""
        mode = pida.mode
        assert isinstance(mode, int)
        assert 0 <= mode <= 4
    
    def test_set_mode(self, pida):
        """测试设置模式"""
        try:
            from plcopen import PIDA_MODE_AUTO
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        pida.mode = PIDA_MODE_AUTO
        assert pida.mode == PIDA_MODE_AUTO
    
    def test_manual_mode(self, pida):
        """测试手动模式"""
        try:
            from plcopen import PIDA_MODE_MANUAL
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        pida.mode = PIDA_MODE_MANUAL
        pida.execute(pv=50.0)
        # 手动模式下，输出应由手动值决定


class TestPIDAAlarms:
    """PIDA报警功能测试"""
    
    @pytest.fixture
    def pida_with_alarms(self):
        """创建带报警配置的PIDA实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        # 需要在C代码中支持报警参数配置
        pida = PIDA()
        return pida
    
    def test_get_alarms_dict(self, pida_with_alarms):
        """测试获取报警字典"""
        alarms = pida_with_alarms.get_alarms()
        assert isinstance(alarms, dict)
        assert "hhind" in alarms
        assert "ahind" in alarms
        assert "alind" in alarms
        assert "llind" in alarms
        assert "da" in alarms
    
    def test_alarm_properties(self, pida_with_alarms):
        """测试报警属性"""
        pida_with_alarms.execute(pv=50.0, sp=50.0)
        
        # 正常情况下应无报警
        assert pida_with_alarms.hhind == False
        assert pida_with_alarms.ahind == False
        assert pida_with_alarms.alind == False
        assert pida_with_alarms.llind == False


class TestPIDARamp:
    """PIDA设定值爬坡测试"""
    
    @pytest.fixture
    def pida(self):
        """创建PIDA测试实例"""
        try:
            from plcopen import PIDA, PIDA_MODE_AUTO
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        pida = PIDA()
        pida.mode = PIDA_MODE_AUTO
        pida.execute(pv=50.0, sp=50.0)
        return pida
    
    def test_start_ramp(self, pida):
        """测试启动爬坡"""
        try:
            pida.start_ramp(target=100.0, time_or_rate=1.0, rtyp=0)
        except Exception as e:
            pytest.fail(f"启动爬坡失败: {e}")
    
    def test_stop_ramp(self, pida):
        """测试停止爬坡"""
        pida.start_ramp(target=100.0, time_or_rate=1.0)
        try:
            pida.stop_ramp()
        except Exception as e:
            pytest.fail(f"停止爬坡失败: {e}")


class TestPIDABypass:
    """PIDA控制旁路测试"""
    
    @pytest.fixture
    def pida_cascade_slave(self):
        """创建串级副调PIDA实例"""
        try:
            from plcopen import PIDA, PIDA_TYPE_CASCADE_SLAVE
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        # 需要在C代码中支持pidtype参数
        pida = PIDA(pidtype=PIDA_TYPE_CASCADE_SLAVE)
        return pida
    
    def test_bypass_property(self, pida_cascade_slave):
        """测试旁路属性"""
        # 初始应为非旁路状态
        assert pida_cascade_slave.bypass == False


class TestPIDAState:
    """PIDA状态保存/恢复测试"""
    
    @pytest.fixture
    def pida(self):
        """创建PIDA测试实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        return PIDA()
    
    def test_get_state(self, pida):
        """测试获取状态"""
        # 运行几步
        for _ in range(10):
            pida.execute(pv=40.0, sp=60.0)
        
        state = pida.get_state()
        assert isinstance(state, dict)
        assert "ek" in state
    
    def test_reset(self, pida):
        """测试重置"""
        # 运行几步
        for _ in range(10):
            pida.execute(pv=40.0, sp=60.0)
        
        pida.reset()
        
        # 重置后输出应为0
        assert abs(pida.output) < 0.01


class TestPIDAProperties:
    """PIDA属性测试"""
    
    @pytest.fixture
    def pida(self):
        """创建PIDA测试实例"""
        try:
            from plcopen import PIDA
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        return PIDA()
    
    def test_output_property(self, pida):
        """测试输出属性"""
        pida.execute(pv=50.0, sp=50.0)
        assert isinstance(pida.output, float)
    
    def test_out_alias(self, pida):
        """测试out别名"""
        pida.execute(pv=50.0, sp=50.0)
        assert pida.out == pida.output
    
    def test_error_property(self, pida):
        """测试误差属性"""
        pida.execute(pv=50.0, sp=60.0)
        assert isinstance(pida.error, float)
    
    def test_ek_alias(self, pida):
        """测试ek别名"""
        pida.execute(pv=50.0, sp=60.0)
        assert pida.ek == pida.error
    
    def test_sp_property(self, pida):
        """测试设定值属性"""
        pida.sp = 75.0
        assert abs(pida.sp - 75.0) < 0.01
    
    def test_am_property(self, pida):
        """测试报警字属性"""
        pida.execute(pv=50.0, sp=50.0)
        assert isinstance(pida.am, int)
    
    def test_ove_property(self, pida):
        """测试输出超限属性"""
        pida.execute(pv=50.0, sp=50.0)
        assert isinstance(pida.ove, int)


class TestPIDAConstants:
    """PIDA常量测试"""
    
    def test_mode_constants(self):
        """测试模式常量"""
        try:
            from plcopen import (
                PIDA_MODE_MANUAL,
                PIDA_MODE_AUTO,
                PIDA_MODE_CASCADE,
                PIDA_MODE_MANUAL_TRACK,
                PIDA_MODE_AUTO_TRACK
            )
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        assert PIDA_MODE_MANUAL == 0
        assert PIDA_MODE_AUTO == 1
        assert PIDA_MODE_CASCADE == 2
        assert PIDA_MODE_MANUAL_TRACK == 3
        assert PIDA_MODE_AUTO_TRACK == 4
    
    def test_type_constants(self):
        """测试类型常量"""
        try:
            from plcopen import (
                PIDA_TYPE_SINGLE,
                PIDA_TYPE_CASCADE_MASTER,
                PIDA_TYPE_CASCADE_SLAVE,
                PIDA_TYPE_EXTERNAL_SP
            )
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        assert PIDA_TYPE_SINGLE == 0
        assert PIDA_TYPE_CASCADE_MASTER == 1
        assert PIDA_TYPE_CASCADE_SLAVE == 2
        assert PIDA_TYPE_EXTERNAL_SP == 3
    
    def test_eqn_constants(self):
        """测试公式常量"""
        try:
            from plcopen import (
                PIDA_EQN_STANDARD,
                PIDA_EQN_DERIVATIVE_FIRST,
                PIDA_EQN_PD_FIRST
            )
        except ImportError:
            pytest.skip("plcopen模块未编译")
        
        assert PIDA_EQN_STANDARD == 0
        assert PIDA_EQN_DERIVATIVE_FIRST == 1
        assert PIDA_EQN_PD_FIRST == 2
