/**
 * @file unity_config.h
 * @brief Unity测试框架配置
 * @version 1.0
 * @date 2026-01-18
 */

#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

/* 使用双精度浮点数 */
#define UNITY_INCLUDE_DOUBLE
#define UNITY_DOUBLE_PRECISION 1e-10

/* 启用浮点数支持 */
#define UNITY_INCLUDE_FLOAT

/* 输出使用UTF-8 */
#define UNITY_OUTPUT_CHAR(c) putchar(c)

/* 测试失败时不退出（继续运行其他测试） */
#define UNITY_USE_FLUSH_STDOUT

/* 64位支持 */
#define UNITY_SUPPORT_64

/* 自定义打印格式 */
#define UNITY_PRINT_EOL() UNITY_OUTPUT_CHAR('\n')

#endif /* UNITY_CONFIG_H */
