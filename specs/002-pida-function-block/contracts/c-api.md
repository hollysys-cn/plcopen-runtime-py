# PIDA C语言API契约

**版本**: 1.0  
**日期**: 2026-01-20  
**文件**: `include/plcopen/fb_pida.h`, `src/fb/pida.c`

## 1. 概述

本文档定义PIDA功能块的C语言API接口规范，遵循现有PLCOpen运行时的设计模式（参考`fb_pid.h`）。

## 2. 头文件结构

```c
/**
 * @file fb_pida.h
 * @brief PIDA功能块头文件 - 带过程值报警的PID控制器
 * @version 1.0
 * @date 2026-01-20
 *
 * 基于IEC61131-3标准的工业级PID控制器实现，
 * 支持五种运行模式、四级过程值报警、设定值爬坡等功能。
 */

#ifndef PLCOPEN_FB_PIDA_H
#define PLCOPEN_FB_PIDA_H

#include "fb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 数据结构定义（见data-model.md） */
/* 函数接口定义（见下文） */

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_FB_PIDA_H */
```

## 3. 函数接口

### 3.1 参数获取

```c
/**
 * @brief 获取PIDA默认参数
 * @return 默认参数结构体
 * 
 * @note 返回值包含所有参数的默认值，可作为初始化基础。
 */
pida_params_t pida_default_params(void);
```

### 3.2 参数验证

```c
/**
 * @brief 验证PIDA参数有效性
 * @param params 参数结构指针
 * @return 错误码
 *   - PLCOPEN_OK: 参数有效
 *   - PLCOPEN_ERR_NULL_PTR: 参数指针为空
 *   - PLCOPEN_ERR_INVALID_PARAM: 参数值无效
 * 
 * @note 验证规则：
 *   - kp > 0, ti >= 0, td >= 0, kd > 0
 *   - pvu > pvl, engu > engl
 *   - outl >= engl, outu <= engu, outl < outu
 *   - spl >= pvl, spu <= pvu, spl < spu
 *   - pidtype ∈ {0,1,2,3}, eqn ∈ {0,1,2}
 */
plcopen_error_t pida_validate_params(const pida_params_t* params);
```

### 3.3 初始化

```c
/**
 * @brief 初始化PIDA实例（使用默认参数）
 * @param pida PIDA实例指针
 * @return 错误码
 *   - PLCOPEN_OK: 初始化成功
 *   - PLCOPEN_ERR_NULL_PTR: 实例指针为空
 * 
 * @note 初始化后实例处于手动模式(MODE=0)，输出为0。
 */
plcopen_error_t pida_init(pida_instance_t* pida);

/**
 * @brief 使用指定参数初始化PIDA实例
 * @param pida PIDA实例指针
 * @param params 参数结构指针
 * @return 错误码
 *   - PLCOPEN_OK: 初始化成功
 *   - PLCOPEN_ERR_NULL_PTR: 指针为空
 *   - PLCOPEN_ERR_INVALID_PARAM: 参数无效
 */
plcopen_error_t pida_init_with_params(pida_instance_t* pida, const pida_params_t* params);
```

### 3.4 执行计算

```c
/**
 * @brief 执行一步PIDA计算
 * @param pida PIDA实例指针
 * @param input 输入结构指针
 * @return 错误码
 *   - PLCOPEN_OK: 计算成功
 *   - PLCOPEN_ERR_NULL_PTR: 指针为空
 *   - PLCOPEN_ERR_NAN: 输入包含NaN
 *   - PLCOPEN_ERR_INF: 输入包含无穷值
 * 
 * @note 每个扫描周期调用一次。计算结果存储在pida->output中。
 * 
 * @par 处理流程：
 * 1. 报警检测与处理
 * 2. 模式切换与跟踪
 * 3. 设定值爬坡处理
 * 4. PID计算（根据EQN类型）
 * 5. 输出限幅与速率限制
 * 6. 状态更新
 */
plcopen_error_t pida_execute(pida_instance_t* pida, const pida_input_t* input);
```

### 3.5 重置

```c
/**
 * @brief 重置PIDA内部状态
 * @param pida PIDA实例指针
 * 
 * @note 保留参数配置，仅清除内部状态和输出。
 *       重置后实例处于手动模式，输出为0。
 */
void pida_reset(pida_instance_t* pida);
```

### 3.6 输出获取

```c
/**
 * @brief 获取PIDA输出
 * @param pida PIDA实例指针
 * @param[out] output 输出结构指针
 * 
 * @note 线程安全。复制整个输出结构。
 */
void pida_get_output(const pida_instance_t* pida, pida_output_t* output);
```

### 3.7 参数设置

```c
/**
 * @brief 设置PIDA参数
 * @param pida PIDA实例指针
 * @param params 新参数结构指针
 * @return 错误码
 * 
 * @note 运行时修改参数。某些参数修改可能需要重置状态。
 */
plcopen_error_t pida_set_params(pida_instance_t* pida, const pida_params_t* params);
```

### 3.8 状态保存与恢复（热重载）

```c
/**
 * @brief 获取PIDA内部状态
 * @param pida PIDA实例指针
 * @param[out] state 状态结构指针
 * 
 * @note 用于热重载时保存状态。
 */
void pida_get_state(const pida_instance_t* pida, pida_state_t* state);

/**
 * @brief 恢复PIDA内部状态
 * @param pida PIDA实例指针
 * @param state 状态结构指针
 * 
 * @note 用于热重载时恢复状态。
 */
void pida_set_state(pida_instance_t* pida, const pida_state_t* state);
```

### 3.9 模式控制

```c
/**
 * @brief 设置运行模式
 * @param pida PIDA实例指针
 * @param mode 目标模式
 * @return 错误码
 *   - PLCOPEN_OK: 切换成功
 *   - PLCOPEN_ERR_INVALID_PARAM: 模式值无效
 *   - PLCOPEN_ERR_STATE: 当前状态不允许切换
 * 
 * @note 模式切换遵循无扰原则：
 *   - 手动→自动：输出保持，SP跟踪PV（如TRKOPT=1）
 *   - 自动→手动：输出保持
 *   - 自动→串级：副调就绪时生效
 *   - 串级→自动：SP保持内给定值
 */
plcopen_error_t pida_set_mode(pida_instance_t* pida, uint8_t mode);

/**
 * @brief 获取当前运行模式
 * @param pida PIDA实例指针
 * @return 当前模式值，错误时返回0xFF
 */
uint8_t pida_get_mode(const pida_instance_t* pida);
```

### 3.10 手动输出控制

```c
/**
 * @brief 手动模式设置输出值
 * @param pida PIDA实例指针
 * @param value 输出值
 * @return 错误码
 * 
 * @note 仅在MODE=0（手动）时生效。
 *       输出值将被限制在[OUTL, OUTU]范围内（如MOLSW=1）。
 */
plcopen_error_t pida_set_manual_output(pida_instance_t* pida, float value);

/**
 * @brief 手动模式增减输出
 * @param pida PIDA实例指针
 * @param manmode 操作模式：1=快增,2=快减,3=慢增,4=慢减
 * @return 错误码
 */
plcopen_error_t pida_manual_adjust(pida_instance_t* pida, uint8_t manmode);
```

### 3.11 设定值控制

```c
/**
 * @brief 设置设定值
 * @param pida PIDA实例指针
 * @param sp 设定值
 * @return 错误码
 * 
 * @note 设定值将被限制在[SPL, SPU]范围内。
 *       如正在爬坡，此调用将停止爬坡。
 */
plcopen_error_t pida_set_sp(pida_instance_t* pida, float sp);

/**
 * @brief 设定值增减
 * @param pida PIDA实例指针
 * @param spmode 操作模式：1=快增,2=快减,3=慢增,4=慢减
 * @return 错误码
 */
plcopen_error_t pida_sp_adjust(pida_instance_t* pida, uint8_t spmode);
```

### 3.12 爬坡控制

```c
/**
 * @brief 启动设定值爬坡
 * @param pida PIDA实例指针
 * @param target 目标值
 * @param rtyp 爬坡方式：0=时间,1=速率
 * @param value 时间（分钟）或速率（工程量/分钟）
 * @return 错误码
 * 
 * @note 仅在MODE=1（自动）时生效。
 */
plcopen_error_t pida_start_ramp(pida_instance_t* pida, float target, bool rtyp, float value);

/**
 * @brief 停止设定值爬坡
 * @param pida PIDA实例指针
 * @return 错误码
 */
plcopen_error_t pida_stop_ramp(pida_instance_t* pida);

/**
 * @brief 获取爬坡状态
 * @param pida PIDA实例指针
 * @param[out] active 爬坡是否进行中
 * @param[out] remaining 剩余时间（分钟）
 * @param[out] rate 当前速率
 */
void pida_get_ramp_status(const pida_instance_t* pida, bool* active, float* remaining, float* rate);
```

### 3.13 旁路控制

```c
/**
 * @brief 设置控制旁路
 * @param pida PIDA实例指针
 * @param bypass 旁路状态：true=旁路，false=投用
 * @return 错误码
 *   - PLCOPEN_OK: 操作成功
 *   - PLCOPEN_ERR_STATE: 当前状态不支持旁路
 * 
 * @note 仅PIDTYPE=2（串级副调）且MODE∈{0,1,2}时支持旁路。
 */
plcopen_error_t pida_set_bypass(pida_instance_t* pida, bool bypass);
```

### 3.14 报警查询

```c
/**
 * @brief 获取报警状态
 * @param pida PIDA实例指针
 * @param[out] hhind 高高限报警
 * @param[out] ahind 高限报警
 * @param[out] alind 低限报警
 * @param[out] llind 低低限报警
 * @param[out] da 偏差报警
 */
void pida_get_alarms(const pida_instance_t* pida, 
                     bool* hhind, bool* ahind, bool* alind, bool* llind, bool* da);

/**
 * @brief 获取报警信息字
 * @param pida PIDA实例指针
 * @return 报警信息字（位定义见PIDA_AM_*宏）
 */
uint16_t pida_get_alarm_word(const pida_instance_t* pida);
```

## 4. 辅助宏

```c
/* 位操作宏 */
#define PIDA_B_GET(word, bit)       (((word) >> (bit)) & 1)
#define PIDA_B_WRITE(word, bit, val) \
    ((val) ? ((word) | (1 << (bit))) : ((word) & ~(1 << (bit))))

/* 浮点比较阈值 */
#define PIDA_FLOAT_EPSILON  1.0e-6f

/* 浮点相等比较 */
#define PIDA_FLOAT_EQ(a, b) (fabsf((a) - (b)) < PIDA_FLOAT_EPSILON)
```

## 5. 错误码

使用现有`fb_common.h`中定义的错误码：

| 错误码 | 值 | 说明 |
|--------|-----|------|
| PLCOPEN_OK | 0 | 成功 |
| PLCOPEN_ERR_NULL_PTR | -1 | 空指针 |
| PLCOPEN_ERR_INVALID_PARAM | -2 | 参数无效 |
| PLCOPEN_ERR_NAN | -3 | NaN值 |
| PLCOPEN_ERR_INF | -4 | 无穷值 |
| PLCOPEN_ERR_STATE | -5 | 状态错误 |

## 6. 线程安全

- 单个`pida_instance_t`实例不是线程安全的
- 不同实例可在不同线程中并发使用
- 读取输出（`pida_get_output`等）与执行（`pida_execute`）可能产生竞态条件

## 7. 内存管理

- 所有结构体由调用方分配内存
- 无动态内存分配
- 推荐栈分配或静态分配

---

**文档版本**: 1.0  
**最后更新**: 2026-01-20
