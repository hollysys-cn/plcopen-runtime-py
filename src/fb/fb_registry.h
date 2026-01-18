/**
 * @file fb_registry.h
 * @brief 功能块注册表
 * @version 1.0
 * @date 2026-01-18
 *
 * 提供功能块类型的动态注册机制。
 */

#ifndef FB_REGISTRY_H
#define FB_REGISTRY_H

#include "plcopen/plcopen.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 类型定义
 * ========================================================================== */

/**
 * @brief 功能块信息
 */
typedef struct {
    const char *name;           /**< 功能块名称 */
    const char *description;    /**< 功能块描述 */
    size_t instance_size;       /**< 实例大小（字节） */
    size_t state_size;          /**< 状态大小（字节） */

    /* 函数指针 */
    plcopen_error_t (*init)(void *inst);
    plcopen_error_t (*execute)(void *inst, void *input, void *output);
    void (*reset)(void *inst);
    void (*get_state)(const void *inst, void *state);
    void (*set_state)(void *inst, const void *state);
} fb_info_t;

/**
 * @brief 注册表条目
 */
typedef struct fb_registry_entry {
    fb_info_t info;
    struct fb_registry_entry *next;
} fb_registry_entry_t;

/* ============================================================================
 * 函数声明
 * ========================================================================== */

/**
 * @brief 注册功能块类型
 *
 * @param info 功能块信息
 * @return 成功返回 PLCOPEN_OK
 */
plcopen_error_t fb_registry_register(const fb_info_t *info);

/**
 * @brief 查找功能块类型
 *
 * @param name 功能块名称
 * @return 功能块信息，未找到返回 NULL
 */
const fb_info_t* fb_registry_find(const char *name);

/**
 * @brief 获取所有已注册的功能块
 *
 * @param count 输出参数，返回数量
 * @return 功能块信息数组
 */
const fb_info_t** fb_registry_list(size_t *count);

/**
 * @brief 注销功能块类型
 *
 * @param name 功能块名称
 * @return 成功返回 PLCOPEN_OK
 */
plcopen_error_t fb_registry_unregister(const char *name);

/**
 * @brief 清空注册表
 */
void fb_registry_clear(void);

/**
 * @brief 获取已注册的功能块数量
 *
 * @return 数量
 */
size_t fb_registry_count(void);

/* ============================================================================
 * 便捷宏
 * ========================================================================== */

/**
 * @brief 注册功能块的便捷宏
 *
 * 使用示例：
 * FB_REGISTER(PID, "位置式PID控制器", pid_instance_t, pid_state_t,
 *             pid_init, pid_execute_wrapper, pid_reset,
 *             pid_get_state, pid_set_state);
 */
#define FB_REGISTER(name, desc, inst_type, state_type, \
                    init_fn, exec_fn, reset_fn, get_fn, set_fn) \
    do { \
        fb_info_t info = { \
            .name = #name, \
            .description = desc, \
            .instance_size = sizeof(inst_type), \
            .state_size = sizeof(state_type), \
            .init = (plcopen_error_t (*)(void *))(init_fn), \
            .execute = (plcopen_error_t (*)(void *, void *, void *))(exec_fn), \
            .reset = (void (*)(void *))(reset_fn), \
            .get_state = (void (*)(const void *, void *))(get_fn), \
            .set_state = (void (*)(void *, const void *))(set_fn), \
        }; \
        fb_registry_register(&info); \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* FB_REGISTRY_H */
