# PIDA功能块数据模型

**日期**: 2026-01-20  
**版本**: 1.0  
**参考**: [spec.md](spec.md) | [research.md](research.md)

## 1. 实体概述

PIDA功能块的数据模型遵循现有PLCOpen运行时的结构模式，将变量按职责划分为以下结构体：

| 结构体 | 说明 | 持久化 |
|--------|------|--------|
| `pida_params_t` | 配置参数（初始化后较少变化） | 否 |
| `pida_input_t` | 运行时输入（每周期更新） | 否 |
| `pida_state_t` | 内部状态（算法使用） | 热重载时 |
| `pida_output_t` | 输出结果（每周期计算） | 否 |
| `pida_instance_t` | 实例容器（包含以上全部） | 否 |

## 2. 结构体定义

### 2.1 pida_params_t - 配置参数

```c
/**
 * @brief PIDA功能块配置参数
 * 
 * 对应PIDA.xml中Property含"configurable"（值包含4）的变量。
 * 这些参数在初始化时设置，运行中较少修改。
 */
typedef struct {
    /* === PID参数 === */
    float kp;           /**< 比例带，百分数(%)，默认100 */
    float ti;           /**< 积分时间（秒），默认30 */
    float td;           /**< 微分时间（秒），默认0 */
    float kd;           /**< 微分增益，默认1 */
    
    /* === 量程设置 === */
    float pvu;          /**< PV量程上限，默认100 */
    float pvl;          /**< PV量程下限，默认0 */
    float engu;         /**< 输出量程上限，默认100 */
    float engl;         /**< 输出量程下限，默认0 */
    float outu;         /**< 输出上限值，默认100 */
    float outl;         /**< 输出下限值，默认0 */
    float spu;          /**< SP上限值，默认100 */
    float spl;          /**< SP下限值，默认0 */
    
    /* === 控制选项 === */
    uint8_t pidtype;    /**< PID回路类型：0=单回路,1=串级主调,2=串级副调,3=外给定 */
    uint8_t eqn;        /**< PID公式：0=标准型,1=微分先行,2=比例微分先行 */
    uint8_t octyp;      /**< 输出补偿方式：0=加法,1=乘法 */
    bool outopt;        /**< 输出方式：false=位置式,true=增量式 */
    bool actopt;        /**< 作用方式：false=正作用,true=反作用 */
    bool trkopt;        /**< SP跟踪PV：false=不跟踪,true=跟踪 */
    bool trken;         /**< 跟踪允许：false=不允许,true=允许 */
    
    /* === 变化率限制 === */
    float outrat;       /**< 输出变化率，%/s，默认5 */
    float giverat;      /**< SP变化率，%/s，默认10 */
    float manf;         /**< 手动输出快速变化率，默认1.5 */
    float mans;         /**< 手动输出慢速变化率，默认0.5 */
    float spfrat;       /**< SP快速变化率，默认5 */
    float spsrat;       /**< SP慢速变化率，默认1 */
    
    /* === 死区与分离 === */
    float dvdb;         /**< 输入死区（%），默认0.2 */
    float intedb;       /**< 积分分离值（%），默认100 */
    float satdb;        /**< 饱和区间（%），默认0 */
    
    /* === 报警限值 === */
    float hh;           /**< 报警高高限 */
    float ah;           /**< 报警高限 */
    float al;           /**< 报警低限 */
    float ll;           /**< 报警低低限 */
    float almdb;        /**< 限值报警死区（%），默认2 */
    float dal;          /**< 偏差报警限（%），默认30 */
    
    /* === 报警级别 === */
    uint8_t h2;         /**< 高高限报警级（0=禁用） */
    uint8_t h1;         /**< 高限报警级（0=禁用） */
    uint8_t l1;         /**< 低限报警级（0=禁用） */
    uint8_t l2;         /**< 低低限报警级（0=禁用） */
    uint8_t dallv;      /**< 偏差报警级（0=禁用） */
    
    /* === 报警抑制 === */
    bool inhh2;         /**< 高高限报警抑制 */
    bool inhh1;         /**< 高限报警抑制 */
    bool inhl1;         /**< 低限报警抑制 */
    bool inhl2;         /**< 低低限报警抑制 */
    bool inhdal;        /**< 偏差报警抑制 */
    
    /* === 切手动控制 === */
    uint16_t mancut;    /**< 报警切手动位掩码，默认1920 (0x0780) */
    
    /* === 其他选项 === */
    bool almopt;        /**< 过程报警开关，默认true */
    bool omanopt;       /**< 手动输出变化方式：false=百分比,true=工程量 */
    bool smanopt;       /**< SP变化方式：false=百分比,true=工程量 */
    bool molsw;         /**< 手动输出限幅：false=不限幅,true=限幅 */
    bool lmbls;         /**< 输出限幅无扰开关 */
    bool rovep;         /**< 输出超限暂停爬坡 */
    
} pida_params_t;
```

### 2.2 pida_input_t - 运行时输入

```c
/**
 * @brief PIDA功能块运行时输入
 * 
 * 对应PIDA.xml中InOutType="INPUT"且非配置项的变量。
 * 这些值每个扫描周期更新。
 */
typedef struct {
    /* === 主要输入 === */
    float pv;           /**< 测量值（过程变量） */
    float sp;           /**< 设定值 */
    float cyc;          /**< 计算周期（秒），默认0.5 */
    
    /* === 补偿值 === */
    float incomp;       /**< 输入补偿 */
    float outcomp;      /**< 输出补偿 */
    
    /* === 跟踪输入 === */
    float trkval;       /**< 跟踪点值 */
    bool trksw;         /**< 跟踪开关 */
    
    /* === 串级输入 === */
    uint8_t auxmode;    /**< 副调运行方式 */
    float auxcomp;      /**< 副调PV-INCOMP */
    uint8_t auxove;     /**< 副调输出超限状态 */
    
    /* === 通道状态 === */
    uint16_t q;         /**< 测量值质量字 */
    
    /* === 超驰输入 === */
    uint8_t orsts;      /**< 超驰反馈输入状态 */
    float orfb;         /**< 超驰反馈输入值 */
    
    /* === 模式控制 === */
    uint8_t mode;       /**< 运行模式：0=手动,1=自动,2=串级,3=手动跟踪,4=自动跟踪 */
    uint8_t manmode;    /**< 手动输出模式：1=快增,2=快减,3=慢增,4=慢减,0=无 */
    uint8_t spmode;     /**< SP变化模式：1=快增,2=快减,3=慢增,4=慢减,0=无 */
    
    /* === 爬坡控制 === */
    uint8_t rcmd;       /**< 爬坡命令：0=停止,1=启动 */
    bool rtyp;          /**< 爬坡方式：false=时间,true=速率 */
    float rtimesp;      /**< 爬坡时间设定（分钟） */
    float rratsp;       /**< 爬坡速率设定（工程量/分钟） */
    float rsptv;        /**< 爬坡目标值 */
    
    /* === 手动控制 === */
    bool pmsw;          /**< 手动输出源：false=人工,true=程序 */
    float pmout;        /**< 程控手动模式输出值 */
    
    /* === 旁路控制 === */
    bool ctrbp;         /**< 控制旁路：false=投用,true=旁路 */
    
    /* === 其他 === */
    bool lock;          /**< 锁定操作面板 */
    
} pida_input_t;
```

### 2.3 pida_state_t - 内部状态

```c
/**
 * @brief PIDA功能块内部状态
 * 
 * 对应PIDA.xml中InOutType="TEMP"且需要跨周期保持的变量。
 * 用于热重载时保存和恢复状态。
 */
typedef struct {
    /* === PID计算状态 === */
    float ek;           /**< 本周期偏差值 */
    float ek_1;         /**< 上一周期偏差值 */
    float ek_2;         /**< 上两周期偏差值 */
    float du;           /**< 输出增量（无补偿） */
    float uk;           /**< 控制输出（无补偿） */
    float u1;           /**< 上一周期位置输出 */
    float i1;           /**< 上一周期增量输出 */
    
    /* === 微分状态 === */
    float dk;           /**< 本周期微分计算值 */
    float d1;           /**< 上周期微分计算值 */
    float dudd;         /**< 微分增量 */
    
    /* === 设定值状态 === */
    float sp1;          /**< 内部设定值 */
    float spcal;        /**< 计算用设定值 */
    float intersp;      /**< 内给定值（副调） */
    
    /* === 输出状态 === */
    float ukout;        /**< 位置式输出（有补偿） */
    float duout;        /**< 增量式输出（有补偿） */
    float lastukout;    /**< 上周期位置式输出 */
    float lastduout;    /**< 上周期增量式输出 */
    float lastout;      /**< 上周期输出值 */
    
    /* === 模式状态 === */
    uint8_t nowrm;      /**< 当前运行方式 */
    uint8_t prerm;      /**< 前一运行方式 */
    
    /* === 死区与分离 === */
    uint8_t dd;         /**< 死区进入标志 */
    uint8_t si;         /**< 积分分离标志 */
    float deadinterval; /**< 计算死区范围 */
    float devalmlimit;  /**< 偏差报警限值 */
    float sv1;          /**< 积分分离值 */
    float dt1;          /**< 比例带换算值 */
    
    /* === 报警状态 === */
    bool prehh;         /**< 上周期高高限报警 */
    bool preah;         /**< 上周期高限报警 */
    bool preal;         /**< 上周期低限报警 */
    bool prell;         /**< 上周期低低限报警 */
    uint16_t am;        /**< 报警信息字 */
    uint8_t evenfault;  /**< 偶校验故障计数 */
    
    /* === 爬坡状态 === */
    float rrat;         /**< 实际爬坡速率 */
    float rtime;        /**< 爬坡剩余时间 */
    bool rcmdflag;      /**< 爬坡进行中标志 */
    bool prertyp;       /**< 上周期爬坡方式 */
    float prertimesp;   /**< 上周期爬坡时间设定 */
    float prerratsp;    /**< 上周期爬坡速率设定 */
    float prersptv;     /**< 上周期爬坡目标值 */
    float presp;        /**< 上周期SP值 */
    float presp1;       /**< 上周期SP1值 */
    
    /* === 其他状态 === */
    float prepv;        /**< 上周期PV值 */
    bool prectrbp;      /**< 上周期旁路状态 */
    bool moflag;        /**< 手动切自动超限标记 */
    float realoutrat;   /**< 实际输出变化率限值 */
    float realgiverat;  /**< 实际给定变化率限值 */
    float ralalmdb;     /**< 计算报警死区 */
    float cycletime;    /**< 计算周期（内部使用） */
    
    /* === 量程中间值 === */
    float mu1;          /**< 中间输出上限 */
    float md1;          /**< 中间输出下限 */
    
} pida_state_t;
```

### 2.4 pida_output_t - 输出结果

```c
/**
 * @brief PIDA功能块输出结果
 * 
 * 对应PIDA.xml中InOutType="OUTPUT"和部分"INOUT"的变量。
 * 每个扫描周期计算更新。
 */
typedef struct {
    /* === 主要输出 === */
    float out;          /**< 控制输出值 */
    float comp;         /**< 补偿输出（串级时为INTERSP） */
    
    /* === 设定值输出 === */
    float sp;           /**< 当前设定值（可能被爬坡修改） */
    float intersp;      /**< 内给定值（副调使用） */
    
    /* === 模式输出 === */
    uint8_t mode;       /**< 当前运行模式 */
    uint8_t ove;        /**< 输出超限状态：bit0=超上限,bit1=超下限,bit2=正反作用,bit3=旁路 */
    
    /* === 报警输出 === */
    bool hhind;         /**< 高高限报警指示 */
    bool ahind;         /**< 高限报警指示 */
    bool alind;         /**< 低限报警指示 */
    bool llind;         /**< 低低限报警指示 */
    bool da;            /**< 偏差报警指示 */
    uint16_t am;        /**< 报警信息字 */
    
    /* === 爬坡输出 === */
    float rrat;         /**< 实际爬坡速率（只读） */
    float rtime;        /**< 爬坡剩余时间（只读） */
    bool rcmdflag;      /**< 爬坡进行中标志 */
    
    /* === 状态输出 === */
    float ek;           /**< 当前偏差值 */
    float dk;           /**< 当前微分值 */
    float du;           /**< 当前增量值 */
    
    /* === 旁路状态 === */
    bool ctrbp;         /**< 当前旁路状态 */
    
} pida_output_t;
```

### 2.5 pida_instance_t - 实例容器

```c
/**
 * @brief PIDA功能块实例
 * 
 * 包含所有子结构体，作为功能块的完整上下文。
 */
typedef struct {
    pida_params_t params;   /**< 配置参数 */
    pida_state_t state;     /**< 内部状态 */
    pida_output_t output;   /**< 输出结果 */
} pida_instance_t;
```

## 3. 枚举类型定义

### 3.1 运行模式

```c
/**
 * @brief PIDA运行模式枚举
 */
typedef enum {
    PIDA_MODE_MANUAL = 0,       /**< 手动模式 */
    PIDA_MODE_AUTO = 1,         /**< 自动模式 */
    PIDA_MODE_CASCADE = 2,      /**< 串级模式 */
    PIDA_MODE_MANUAL_TRACK = 3, /**< 手动跟踪模式 */
    PIDA_MODE_AUTO_TRACK = 4    /**< 自动跟踪模式 */
} pida_mode_t;
```

### 3.2 PID回路类型

```c
/**
 * @brief PID回路类型枚举
 */
typedef enum {
    PIDA_TYPE_SINGLE = 0,       /**< 单回路 */
    PIDA_TYPE_CASCADE_MASTER = 1, /**< 串级主调 */
    PIDA_TYPE_CASCADE_SLAVE = 2,  /**< 串级副调 */
    PIDA_TYPE_EXTERNAL_SP = 3   /**< 外给定单回路 */
} pida_type_t;
```

### 3.3 PID公式类型

```c
/**
 * @brief PID公式类型枚举
 */
typedef enum {
    PIDA_EQN_STANDARD = 0,      /**< 标准型 */
    PIDA_EQN_DERIVATIVE_FIRST = 1, /**< 微分先行 */
    PIDA_EQN_PD_FIRST = 2       /**< 比例微分先行 */
} pida_eqn_t;
```

### 3.4 输出超限状态位

```c
/**
 * @brief 输出超限状态位定义
 */
#define PIDA_OVE_OVER_HIGH   0x01  /**< bit0: 输出超上限 */
#define PIDA_OVE_OVER_LOW    0x02  /**< bit1: 输出超下限 */
#define PIDA_OVE_DIRECT_ACT  0x04  /**< bit2: 正作用(1)/反作用(0) */
#define PIDA_OVE_BYPASS      0x08  /**< bit3: 旁路状态 */
```

### 3.5 报警信息位

```c
/**
 * @brief 报警信息字位定义
 */
#define PIDA_AM_LL           0x0001  /**< bit0: 低低限报警 */
#define PIDA_AM_AL           0x0002  /**< bit1: 低限报警 */
#define PIDA_AM_AH           0x0004  /**< bit2: 高限报警 */
#define PIDA_AM_HH           0x0008  /**< bit3: 高高限报警 */
#define PIDA_AM_DEVIATION    0x0080  /**< bit7: 偏差报警 */
```

## 4. 验证规则

### 4.1 参数验证

| 参数 | 验证规则 |
|------|----------|
| kp | > 0 |
| ti | >= 0 |
| td | >= 0 |
| kd | > 0 |
| pvu, pvl | pvu > pvl |
| engu, engl | engu > engl |
| outu, outl | outl <= outu <= engu, outl >= engl |
| spu, spl | spl >= pvl, spu <= pvu, spl < spu |
| cyc | > 0 |
| pidtype | 0, 1, 2, 3 |
| eqn | 0, 1, 2 |
| mode | 0, 1, 2, 3, 4 |

### 4.2 状态约束

| 约束 | 说明 |
|------|------|
| 模式切换 | 仅允许相邻模式切换，避免跳变 |
| 旁路 | 仅PIDTYPE=2且MODE∈{0,1,2}时允许 |
| 爬坡 | 仅MODE=1（自动）时生效 |

## 5. 默认值

```c
/**
 * @brief 获取PIDA默认参数
 */
pida_params_t pida_default_params(void)
{
    return (pida_params_t){
        /* PID参数 */
        .kp = 100.0f,
        .ti = 30.0f,
        .td = 0.0f,
        .kd = 1.0f,
        
        /* 量程设置 */
        .pvu = 100.0f,
        .pvl = 0.0f,
        .engu = 100.0f,
        .engl = 0.0f,
        .outu = 100.0f,
        .outl = 0.0f,
        .spu = 100.0f,
        .spl = 0.0f,
        
        /* 控制选项 */
        .pidtype = PIDA_TYPE_SINGLE,
        .eqn = PIDA_EQN_STANDARD,
        .octyp = 0,
        .outopt = false,
        .actopt = true,
        .trkopt = true,
        .trken = true,
        
        /* 变化率 */
        .outrat = 5.0f,
        .giverat = 10.0f,
        .manf = 1.5f,
        .mans = 0.5f,
        .spfrat = 5.0f,
        .spsrat = 1.0f,
        
        /* 死区 */
        .dvdb = 0.2f,
        .intedb = 100.0f,
        .satdb = 0.0f,
        
        /* 报警限值 */
        .hh = 0.0f,
        .ah = 0.0f,
        .al = 0.0f,
        .ll = 0.0f,
        .almdb = 2.0f,
        .dal = 30.0f,
        
        /* 报警级别 */
        .h2 = 0,
        .h1 = 0,
        .l1 = 0,
        .l2 = 0,
        .dallv = 0,
        
        /* 报警抑制 */
        .inhh2 = false,
        .inhh1 = false,
        .inhl1 = false,
        .inhl2 = false,
        .inhdal = false,
        
        /* 切手动控制 */
        .mancut = 0x0780,
        
        /* 其他选项 */
        .almopt = true,
        .omanopt = false,
        .smanopt = false,
        .molsw = true,
        .lmbls = false,
        .rovep = false,
    };
}
```

## 6. 关系图

```
┌─────────────────────────────────────────────────────────────────────┐
│                         pida_instance_t                              │
├─────────────────────────────────────────────────────────────────────┤
│  ┌──────────────────┐  ┌──────────────────┐  ┌──────────────────┐  │
│  │  pida_params_t   │  │  pida_state_t    │  │  pida_output_t   │  │
│  ├──────────────────┤  ├──────────────────┤  ├──────────────────┤  │
│  │ • kp, ti, td, kd │  │ • ek, ek_1, ek_2 │  │ • out            │  │
│  │ • pvu, pvl       │  │ • dk, d1, dudd   │  │ • sp             │  │
│  │ • engu, engl     │  │ • uk, u1, i1     │  │ • mode           │  │
│  │ • outu, outl     │  │ • sp1, spcal     │  │ • ove            │  │
│  │ • pidtype, eqn   │  │ • nowrm, prerm   │  │ • hhind...llind  │  │
│  │ • outopt, actopt │  │ • dd, si         │  │ • da, am         │  │
│  │ • hh, ah, al, ll │  │ • prehh...prell  │  │ • rrat, rtime    │  │
│  │ • h2, h1, l1, l2 │  │ • rrat, rtime    │  │ • ek, dk, du     │  │
│  │ • mancut         │  │ • rcmdflag       │  │ • ctrbp          │  │
│  │ • almopt...      │  │ • prepv, prectrbp│  │ • comp           │  │
│  └──────────────────┘  └──────────────────┘  └──────────────────┘  │
└─────────────────────────────────────────────────────────────────────┘
                                  │
                                  │ pida_execute()
                                  ▼
                         ┌──────────────────┐
                         │   pida_input_t   │
                         ├──────────────────┤
                         │ • pv, sp, cyc    │
                         │ • incomp, outcomp│
                         │ • mode, manmode  │
                         │ • rcmd, rsptv    │
                         │ • ctrbp          │
                         │ • auxmode...     │
                         └──────────────────┘
```

---

**文档版本**: 1.0  
**最后更新**: 2026-01-20
