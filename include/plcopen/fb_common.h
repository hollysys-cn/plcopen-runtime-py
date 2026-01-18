/**
 * @file fb_common.h
 * @brief 功能块通用定义
 * @version 1.0
 * @date 2026-01-18
 *
 * 定义功能块的通用数据类型、错误码和接口。
 */

#ifndef PLCOPEN_FB_COMMON_H
#define PLCOPEN_FB_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 错误码定义
 * ========================================================================== */

/**
 * @brief PLCOpen错误码
 */
typedef enum {
    PLCOPEN_OK = 0,              /**< 成功 */
    PLCOPEN_ERR_INVALID_PARAM,   /**< 参数无效 */
    PLCOPEN_ERR_NULL_PTR,        /**< 空指针 */
    PLCOPEN_ERR_OUT_OF_MEMORY,   /**< 内存不足 */
    PLCOPEN_ERR_INVALID_STATE,   /**< 状态无效 */
    PLCOPEN_ERR_NOT_FOUND,       /**< 未找到 */
    PLCOPEN_ERR_ALREADY_EXISTS,  /**< 已存在 */
    PLCOPEN_ERR_OVERFLOW,        /**< 溢出 */
    PLCOPEN_ERR_UNDERFLOW,       /**< 下溢 */
    PLCOPEN_ERR_NAN,             /**< NaN值 */
    PLCOPEN_ERR_INF,             /**< 无穷值 */
} plcopen_error_t;

/**
 * @brief 获取错误描述
 * @param err 错误码
 * @return 错误描述字符串（简体中文）
 */
const char* plcopen_strerror(plcopen_error_t err);

/* ============================================================================
 * 通用工具宏
 * ========================================================================== */

/**
 * @brief 限幅宏
 */
#define PLCOPEN_CLAMP(x, min, max) \
    ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

/**
 * @brief 检查是否为NaN
 */
#define PLCOPEN_IS_NAN(x) isnan(x)

/**
 * @brief 检查是否为无穷
 */
#define PLCOPEN_IS_INF(x) isinf(x)

/**
 * @brief 检查浮点数是否有效（非NaN且非Inf）
 */
#define PLCOPEN_IS_VALID(x) (!isnan(x) && !isinf(x))

/* ============================================================================
 * 功能块类型信息
 * ========================================================================== */

/**
 * @brief 功能块实例句柄（不透明指针）
 */
typedef struct fb_instance* fb_handle_t;

/**
 * @brief 功能块类型信息
 */
typedef struct {
    const char* name;           /**< 类型名称 */
    size_t instance_size;       /**< 实例大小（字节） */

    /**
     * @brief 初始化函数指针
     * @param handle 实例句柄
     * @return 错误码
     */
    plcopen_error_t (*init)(fb_handle_t handle);

    /**
     * @brief 销毁函数指针
     * @param handle 实例句柄
     */
    void (*destroy)(fb_handle_t handle);

    /**
     * @brief 重置函数指针
     * @param handle 实例句柄
     */
    void (*reset)(fb_handle_t handle);

} fb_type_info_t;

/**
 * @brief 注册功能块类型
 * @param type_info 类型信息
 * @return 错误码
 */
plcopen_error_t fb_register_type(const fb_type_info_t* type_info);

/**
 * @brief 获取已注册的功能块类型信息
 * @param type_name 类型名称
 * @return 类型信息指针，未找到返回NULL
 */
const fb_type_info_t* fb_get_type_info(const char* type_name);

/**
 * @brief 创建功能块实例
 * @param type_name 类型名称
 * @param[out] handle 输出实例句柄
 * @return 错误码
 */
plcopen_error_t fb_create(const char* type_name, fb_handle_t* handle);

/**
 * @brief 销毁功能块实例
 * @param handle 实例句柄
 */
void fb_destroy(fb_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_FB_COMMON_H */
