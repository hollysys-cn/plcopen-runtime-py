/**
 * @file error.h
 * @brief 错误处理头文件
 * @version 1.0
 * @date 2026-01-18
 */

#ifndef PLCOPEN_ERROR_H
#define PLCOPEN_ERROR_H

#include "plcopen/fb_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置最后错误
 * @param err 错误码
 */
void plcopen_set_last_error(plcopen_error_t err);

/**
 * @brief 获取最后错误
 * @return 错误码
 */
plcopen_error_t plcopen_get_last_error(void);

/**
 * @brief 清除最后错误
 */
void plcopen_clear_last_error(void);

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_ERROR_H */
