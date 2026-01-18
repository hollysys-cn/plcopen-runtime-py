/**
 * @file error.c
 * @brief 错误处理实现
 * @version 1.0
 * @date 2026-01-18
 */

#include "error.h"
#include <string.h>

/* 线程本地存储（如果支持） */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)
    #include <threads.h>
    static _Thread_local plcopen_error_t g_last_error = PLCOPEN_OK;
#else
    /* 非线程安全的回退实现 */
    static plcopen_error_t g_last_error = PLCOPEN_OK;
#endif

/**
 * @brief 错误描述表（简体中文）
 */
static const char* const g_error_messages[] = {
    [PLCOPEN_OK]                = "成功",
    [PLCOPEN_ERR_INVALID_PARAM] = "参数无效",
    [PLCOPEN_ERR_NULL_PTR]      = "空指针",
    [PLCOPEN_ERR_OUT_OF_MEMORY] = "内存不足",
    [PLCOPEN_ERR_INVALID_STATE] = "状态无效",
    [PLCOPEN_ERR_NOT_FOUND]     = "未找到",
    [PLCOPEN_ERR_ALREADY_EXISTS]= "已存在",
    [PLCOPEN_ERR_OVERFLOW]      = "溢出",
    [PLCOPEN_ERR_UNDERFLOW]     = "下溢",
    [PLCOPEN_ERR_NAN]           = "NaN值",
    [PLCOPEN_ERR_INF]           = "无穷值",
};

#define ERROR_MESSAGE_COUNT (sizeof(g_error_messages) / sizeof(g_error_messages[0]))

const char* plcopen_strerror(plcopen_error_t err)
{
    if (err >= 0 && (size_t)err < ERROR_MESSAGE_COUNT && g_error_messages[err] != NULL) {
        return g_error_messages[err];
    }
    return "未知错误";
}

void plcopen_set_last_error(plcopen_error_t err)
{
    g_last_error = err;
}

plcopen_error_t plcopen_get_last_error(void)
{
    return g_last_error;
}

void plcopen_clear_last_error(void)
{
    g_last_error = PLCOPEN_OK;
}
