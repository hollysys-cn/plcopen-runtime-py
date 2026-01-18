/**
 * @file log.c
 * @brief 日志系统实现
 * @version 1.0
 * @date 2026-01-18
 *
 * 支持控制台输出和文件轮转。
 */

#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_SEPARATOR "\\"
#else
    #include <sys/stat.h>
    #include <unistd.h>
    #include <errno.h>
    #define PATH_SEPARATOR "/"
#endif

/* ============================================================================
 * 内部状态
 * ========================================================================== */

static struct {
    log_config_t config;
    FILE* log_file;
    size_t current_file_size;
    bool initialized;
} g_log = {0};

/* 日志级别名称 */
static const char* const g_level_names[] = {
    [LOG_LEVEL_DEBUG] = "调试",
    [LOG_LEVEL_INFO]  = "信息",
    [LOG_LEVEL_WARN]  = "警告",
    [LOG_LEVEL_ERROR] = "错误",
    [LOG_LEVEL_FATAL] = "致命",
};

/* 日志级别颜色（ANSI） */
static const char* const g_level_colors[] = {
    [LOG_LEVEL_DEBUG] = "\033[36m",  /* 青色 */
    [LOG_LEVEL_INFO]  = "\033[32m",  /* 绿色 */
    [LOG_LEVEL_WARN]  = "\033[33m",  /* 黄色 */
    [LOG_LEVEL_ERROR] = "\033[31m",  /* 红色 */
    [LOG_LEVEL_FATAL] = "\033[35m",  /* 紫色 */
};

#define COLOR_RESET "\033[0m"

/* ============================================================================
 * 内部函数
 * ========================================================================== */

/**
 * @brief 获取当前时间字符串
 */
static void get_timestamp(char* buf, size_t size)
{
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(buf, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

/**
 * @brief 构建日志文件路径
 */
static void build_log_path(char* buf, size_t size, int index)
{
    if (index == 0) {
        snprintf(buf, size, "%s%s%s",
                 g_log.config.log_dir,
                 PATH_SEPARATOR,
                 g_log.config.log_filename);
    } else {
        snprintf(buf, size, "%s%s%s.%d",
                 g_log.config.log_dir,
                 PATH_SEPARATOR,
                 g_log.config.log_filename,
                 index);
    }
}

/**
 * @brief 日志文件轮转
 */
static void rotate_log_file(void)
{
    if (!g_log.log_file) return;

    fclose(g_log.log_file);
    g_log.log_file = NULL;

    char old_path[512], new_path[512];

    /* 删除最旧的日志文件 */
    build_log_path(old_path, sizeof(old_path), g_log.config.backup_count);
    remove(old_path);

    /* 重命名现有日志文件 */
    for (int i = g_log.config.backup_count - 1; i >= 0; i--) {
        build_log_path(old_path, sizeof(old_path), i);
        build_log_path(new_path, sizeof(new_path), i + 1);
        rename(old_path, new_path);
    }

    /* 打开新的日志文件 */
    build_log_path(old_path, sizeof(old_path), 0);
    g_log.log_file = fopen(old_path, "w");
    g_log.current_file_size = 0;
}

/**
 * @brief 确保日志目录存在
 */
static bool ensure_log_dir(const char* dir)
{
#ifdef _WIN32
    return CreateDirectoryA(dir, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
#else
    return mkdir(dir, 0755) == 0 || errno == EEXIST;
#endif
}

/* ============================================================================
 * 公共接口
 * ========================================================================== */

log_config_t log_default_config(void)
{
    return (log_config_t){
        .level = LOG_LEVEL_INFO,
        .console_enabled = true,
        .file_enabled = true,
        .log_dir = "logs",
        .log_filename = "plcopen.log",
        .max_file_size = 10 * 1024 * 1024,  /* 10MB */
        .backup_count = 5,
    };
}

plcopen_error_t log_init(const log_config_t* config)
{
    if (g_log.initialized) {
        log_shutdown();
    }

    g_log.config = config ? *config : log_default_config();

    if (g_log.config.file_enabled) {
        if (!ensure_log_dir(g_log.config.log_dir)) {
            fprintf(stderr, "无法创建日志目录: %s\n", g_log.config.log_dir);
            return PLCOPEN_ERR_INVALID_STATE;
        }

        char log_path[512];
        build_log_path(log_path, sizeof(log_path), 0);
        g_log.log_file = fopen(log_path, "a");
        if (!g_log.log_file) {
            fprintf(stderr, "无法打开日志文件: %s\n", log_path);
            return PLCOPEN_ERR_INVALID_STATE;
        }

        /* 获取当前文件大小 */
        fseek(g_log.log_file, 0, SEEK_END);
        g_log.current_file_size = (size_t)ftell(g_log.log_file);
    }

    g_log.initialized = true;
    return PLCOPEN_OK;
}

void log_shutdown(void)
{
    if (g_log.log_file) {
        fclose(g_log.log_file);
        g_log.log_file = NULL;
    }
    g_log.initialized = false;
}

void log_write(log_level_t level, const char* file, int line, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    log_writev(level, file, line, fmt, args);
    va_end(args);
}

void log_writev(log_level_t level, const char* file, int line, const char* fmt, va_list args)
{
    if (!g_log.initialized || level < g_log.config.level || level >= LOG_LEVEL_OFF) {
        return;
    }

    char timestamp[32];
    get_timestamp(timestamp, sizeof(timestamp));

    /* 提取文件名 */
    const char* filename = strrchr(file, '/');
    if (!filename) filename = strrchr(file, '\\');
    filename = filename ? filename + 1 : file;

    /* 格式化消息 */
    char message[1024];
    vsnprintf(message, sizeof(message), fmt, args);

    /* 输出到控制台 */
    if (g_log.config.console_enabled) {
        fprintf(stderr, "%s[%s] [%s] %s:%d - %s%s\n",
                g_level_colors[level],
                timestamp,
                g_level_names[level],
                filename,
                line,
                message,
                COLOR_RESET);
    }

    /* 输出到文件 */
    if (g_log.config.file_enabled && g_log.log_file) {
        int written = fprintf(g_log.log_file, "[%s] [%s] %s:%d - %s\n",
                              timestamp,
                              g_level_names[level],
                              filename,
                              line,
                              message);
        if (written > 0) {
            g_log.current_file_size += (size_t)written;
        }

        /* 检查是否需要轮转 */
        if (g_log.current_file_size >= g_log.config.max_file_size) {
            rotate_log_file();
        }
    }
}

void log_set_level(log_level_t level)
{
    g_log.config.level = level;
}

log_level_t log_get_level(void)
{
    return g_log.config.level;
}

void log_flush(void)
{
    if (g_log.log_file) {
        fflush(g_log.log_file);
    }
    fflush(stderr);
}
