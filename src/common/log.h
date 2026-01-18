/**
 * @file log.h
 * @brief 日志系统头文件
 * @version 1.0
 * @date 2026-01-18
 *
 * 支持控制台输出和文件轮转。
 */

#ifndef PLCOPEN_LOG_H
#define PLCOPEN_LOG_H

#include "plcopen/fb_common.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 日志级别
 * ========================================================================== */

/**
 * @brief 日志级别
 */
typedef enum {
    LOG_LEVEL_DEBUG = 0,  /**< 调试 */
    LOG_LEVEL_INFO,       /**< 信息 */
    LOG_LEVEL_WARN,       /**< 警告 */
    LOG_LEVEL_ERROR,      /**< 错误 */
    LOG_LEVEL_FATAL,      /**< 致命 */
    LOG_LEVEL_OFF,        /**< 关闭日志 */
} log_level_t;

/* ============================================================================
 * 日志配置
 * ========================================================================== */

/**
 * @brief 日志配置
 */
typedef struct {
    log_level_t level;           /**< 最低日志级别 */
    bool console_enabled;        /**< 是否输出到控制台 */
    bool file_enabled;           /**< 是否输出到文件 */
    const char* log_dir;         /**< 日志目录 */
    const char* log_filename;    /**< 日志文件名（不含路径） */
    size_t max_file_size;        /**< 单个日志文件最大字节数 */
    int backup_count;            /**< 日志文件保留数量 */
} log_config_t;

/**
 * @brief 获取默认日志配置
 * @return 默认配置
 */
log_config_t log_default_config(void);

/**
 * @brief 初始化日志系统
 * @param config 配置（NULL使用默认配置）
 * @return 错误码
 */
plcopen_error_t log_init(const log_config_t* config);

/**
 * @brief 关闭日志系统
 */
void log_shutdown(void);

/* ============================================================================
 * 日志接口
 * ========================================================================== */

/**
 * @brief 写入日志
 * @param level 日志级别
 * @param file 源文件名
 * @param line 行号
 * @param fmt 格式字符串
 * @param ... 参数
 */
void log_write(log_level_t level, const char* file, int line, const char* fmt, ...);

/**
 * @brief 写入日志（va_list版本）
 */
void log_writev(log_level_t level, const char* file, int line, const char* fmt, va_list args);

/**
 * @brief 设置日志级别
 * @param level 新的日志级别
 */
void log_set_level(log_level_t level);

/**
 * @brief 获取当前日志级别
 * @return 当前日志级别
 */
log_level_t log_get_level(void);

/**
 * @brief 刷新日志缓冲区
 */
void log_flush(void);

/* ============================================================================
 * 便捷宏
 * ========================================================================== */

#define LOG_DEBUG(fmt, ...) log_write(LOG_LEVEL_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  log_write(LOG_LEVEL_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  log_write(LOG_LEVEL_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) log_write(LOG_LEVEL_FATAL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* PLCOPEN_LOG_H */
