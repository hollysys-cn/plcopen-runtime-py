/**
 * @file plcopen.h
 * @brief PLCOpen运行时主头文件
 * @version 1.0
 * @date 2026-01-18
 *
 * 包含此头文件以使用PLCOpen运行时的所有功能。
 */

#ifndef PLCOPEN_PLCOPEN_H
#define PLCOPEN_PLCOPEN_H

/* 版本信息 */
#define PLCOPEN_VERSION_MAJOR 1
#define PLCOPEN_VERSION_MINOR 0
#define PLCOPEN_VERSION_PATCH 0
#define PLCOPEN_VERSION_STRING "1.0.0"

/* 包含所有子模块头文件 */
#include "plcopen/fb_common.h"

/* 如果不是纯嵌入式环境，包含功能块头文件 */
#ifndef PLCOPEN_MINIMAL
#include "plcopen/fb_pid.h"
#include "plcopen/fb_first_order.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化PLCOpen运行时库
 * @return 错误码
 *
 * 在使用任何功能块之前调用此函数。
 */
plcopen_error_t plcopen_init(void);

/**
 * @brief 清理PLCOpen运行时库
 *
 * 在程序退出前调用此函数释放资源。
 */
void plcopen_cleanup(void);

/**
 * @brief 获取库版本字符串
 * @return 版本字符串
 */
const char* plcopen_version(void);

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_PLCOPEN_H */
