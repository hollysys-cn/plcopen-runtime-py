/**
 * @file bench_memory.c
 * @brief 功能块内存占用基准测试
 * @version 1.0
 * @date 2026-01-18
 *
 * 测试目标：单个功能块实例内存 < 1KB
 */

#include <stdio.h>
#include <stddef.h>
#include "plcopen/fb_pid.h"
#include "plcopen/fb_first_order.h"

/* ============================================================================
 * 内存大小报告
 * ========================================================================== */

static void report_struct_sizes(void)
{
    printf("PLCOpen 功能块内存占用报告\n");
    printf("========================================\n");
    printf("目标: 单个功能块实例 < 1KB (1024 bytes)\n");
    printf("\n");

    /* PID 相关结构体 */
    printf("PID 功能块:\n");
    printf("  pid_params_t:    %zu bytes\n", sizeof(pid_params_t));
    printf("  pid_input_t:     %zu bytes\n", sizeof(pid_input_t));
    printf("  pid_output_t:    %zu bytes\n", sizeof(pid_output_t));
    printf("  pid_state_t:     %zu bytes\n", sizeof(pid_state_t));
    printf("  pid_instance_t:  %zu bytes\n", sizeof(pid_instance_t));

    size_t pid_total = sizeof(pid_instance_t);
    if (pid_total < 1024) {
        printf("  ✓ 通过: %zu bytes < 1024 bytes\n", pid_total);
    } else {
        printf("  ✗ 失败: %zu bytes >= 1024 bytes\n", pid_total);
    }

    printf("\n");

    /* FirstOrder 相关结构体 */
    printf("FirstOrder 功能块:\n");
    printf("  first_order_params_t:    %zu bytes\n", sizeof(first_order_params_t));
    printf("  first_order_state_t:     %zu bytes\n", sizeof(first_order_state_t));
    printf("  first_order_instance_t:  %zu bytes\n", sizeof(first_order_instance_t));

    size_t fo_total = sizeof(first_order_instance_t);
    if (fo_total < 1024) {
        printf("  ✓ 通过: %zu bytes < 1024 bytes\n", fo_total);
    } else {
        printf("  ✗ 失败: %zu bytes >= 1024 bytes\n", fo_total);
    }

    printf("\n");
    printf("========================================\n");

    /* 汇总 */
    printf("内存占用汇总:\n");
    printf("  PID 实例:        %4zu bytes\n", pid_total);
    printf("  FirstOrder 实例: %4zu bytes\n", fo_total);
    printf("  总计（各一个）:  %4zu bytes\n", pid_total + fo_total);
    printf("========================================\n");
}

static void report_array_memory(void)
{
    printf("\n批量实例化内存估算:\n");
    printf("----------------------------------------\n");

    size_t pid_size = sizeof(pid_instance_t);
    size_t fo_size = sizeof(first_order_instance_t);

    printf("实例数量  |  PID 内存   | FirstOrder 内存\n");
    printf("----------|-------------|----------------\n");

    int counts[] = {1, 10, 100, 1000};
    for (int i = 0; i < 4; i++) {
        int n = counts[i];
        printf("  %4d    | %7zu KB  | %7zu KB\n",
               n,
               (n * pid_size) / 1024,
               (n * fo_size) / 1024);
    }

    printf("----------------------------------------\n");
}

static void report_alignment(void)
{
    printf("\n结构体对齐信息:\n");
    printf("----------------------------------------\n");

    printf("pid_params_t 对齐:   %zu\n", _Alignof(pid_params_t));
    printf("pid_instance_t 对齐: %zu\n", _Alignof(pid_instance_t));
    printf("first_order_instance_t 对齐: %zu\n", _Alignof(first_order_instance_t));

    printf("----------------------------------------\n");
}

static void report_field_offsets(void)
{
    printf("\nPID 结构体字段偏移:\n");
    printf("----------------------------------------\n");

    printf("pid_instance_t:\n");
    printf("  params:  offset %zu, size %zu\n",
           offsetof(pid_instance_t, params),
           sizeof(((pid_instance_t *)0)->params));
    printf("  state:   offset %zu, size %zu\n",
           offsetof(pid_instance_t, state),
           sizeof(((pid_instance_t *)0)->state));
    printf("  output:  offset %zu, size %zu\n",
           offsetof(pid_instance_t, output),
           sizeof(((pid_instance_t *)0)->output));

    printf("\nfirst_order_instance_t:\n");
    printf("  params:  offset %zu, size %zu\n",
           offsetof(first_order_instance_t, params),
           sizeof(((first_order_instance_t *)0)->params));
    printf("  state:   offset %zu, size %zu\n",
           offsetof(first_order_instance_t, state),
           sizeof(((first_order_instance_t *)0)->state));
    printf("  output:  offset %zu, size %zu\n",
           offsetof(first_order_instance_t, output),
           sizeof(double));

    printf("----------------------------------------\n");
}

/* ============================================================================
 * Main
 * ========================================================================== */

int main(void)
{
    report_struct_sizes();
    report_array_memory();
    report_alignment();
    report_field_offsets();

    return 0;
}
