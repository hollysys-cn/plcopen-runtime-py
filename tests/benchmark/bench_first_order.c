/**
 * @file bench_first_order.c
 * @brief 一阶惯性功能块性能基准测试
 * @version 1.0
 * @date 2026-01-18
 *
 * 测试目标：单次执行时间 < 1ms
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "plcopen/fb_first_order.h"

/* ============================================================================
 * 配置
 * ========================================================================== */

#define WARMUP_ITERATIONS    1000
#define BENCHMARK_ITERATIONS 100000
#define REPORT_INTERVAL      10000

/* ============================================================================
 * 时间测量
 * ========================================================================== */

static double get_time_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}

/* ============================================================================
 * 统计
 * ========================================================================== */

typedef struct {
    double min;
    double max;
    double sum;
    double sum_sq;
    size_t count;
} stats_t;

static void stats_init(stats_t *s)
{
    s->min = INFINITY;
    s->max = -INFINITY;
    s->sum = 0.0;
    s->sum_sq = 0.0;
    s->count = 0;
}

static void stats_add(stats_t *s, double value)
{
    if (value < s->min) s->min = value;
    if (value > s->max) s->max = value;
    s->sum += value;
    s->sum_sq += value * value;
    s->count++;
}

static double stats_mean(const stats_t *s)
{
    return s->sum / s->count;
}

static double stats_stddev(const stats_t *s)
{
    double mean = stats_mean(s);
    double variance = (s->sum_sq / s->count) - (mean * mean);
    return sqrt(variance);
}

/* ============================================================================
 * 基准测试
 * ========================================================================== */

static void bench_first_order_execute(void)
{
    first_order_instance_t fo;
    first_order_params_t params = {
        .k = 1.0,
        .t = 0.5,
        .dt = 0.1
    };

    first_order_init_with_params(&fo, &params);

    stats_t stats;
    stats_init(&stats);

    /* 预热 */
    printf("预热中 (%d 次)...\n", WARMUP_ITERATIONS);
    for (int i = 0; i < WARMUP_ITERATIONS; i++) {
        first_order_execute(&fo, 100.0 + i * 0.001);
    }

    /* 基准测试 */
    printf("基准测试中 (%d 次)...\n", BENCHMARK_ITERATIONS);

    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        double input = 50.0 + sin(i * 0.01) * 50.0;

        double start = get_time_ns();
        first_order_execute(&fo, input);
        double end = get_time_ns();

        stats_add(&stats, end - start);

        if ((i + 1) % REPORT_INTERVAL == 0) {
            printf("  进度: %d/%d (%.1f%%)\n",
                   i + 1, BENCHMARK_ITERATIONS,
                   100.0 * (i + 1) / BENCHMARK_ITERATIONS);
        }
    }

    /* 输出结果 */
    printf("\n");
    printf("========================================\n");
    printf("FirstOrder execute() 性能测试结果\n");
    printf("========================================\n");
    printf("迭代次数:   %zu\n", stats.count);
    printf("最小时间:   %.2f ns\n", stats.min);
    printf("最大时间:   %.2f ns\n", stats.max);
    printf("平均时间:   %.2f ns\n", stats_mean(&stats));
    printf("标准差:     %.2f ns\n", stats_stddev(&stats));
    printf("----------------------------------------\n");

    double target_ns = 1000000.0;  /* 1ms = 1000000ns */
    if (stats.max < target_ns) {
        printf("✓ 通过: 最大执行时间 < 1ms\n");
    } else {
        printf("✗ 失败: 最大执行时间 >= 1ms\n");
    }
    printf("========================================\n");
}

static void bench_first_order_init(void)
{
    stats_t stats;
    stats_init(&stats);

    printf("\nFirstOrder init() 性能测试...\n");

    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        first_order_instance_t fo;
        first_order_params_t params = {
            .k = 1.0 + i * 0.00001,
            .t = 0.5,
            .dt = 0.1
        };

        double start = get_time_ns();
        first_order_init_with_params(&fo, &params);
        double end = get_time_ns();

        stats_add(&stats, end - start);
    }

    printf("----------------------------------------\n");
    printf("FirstOrder init() 性能测试结果\n");
    printf("----------------------------------------\n");
    printf("平均时间:   %.2f ns\n", stats_mean(&stats));
    printf("最大时间:   %.2f ns\n", stats.max);
    printf("----------------------------------------\n");
}

static void bench_filter_convergence(void)
{
    printf("\n一阶惯性收敛性能测试...\n");

    first_order_instance_t fo;
    first_order_params_t params = {
        .k = 1.0,
        .t = 1.0,
        .dt = 0.1
    };
    first_order_init_with_params(&fo, &params);

    double input = 100.0;
    int steps_to_99 = 0;

    double start = get_time_ns();

    while (fo.output < 99.0 && steps_to_99 < 1000) {
        first_order_execute(&fo, input);
        steps_to_99++;
    }

    double end = get_time_ns();

    printf("----------------------------------------\n");
    printf("收敛到99%%的步数: %d\n", steps_to_99);
    printf("收敛总时间:       %.2f us\n", (end - start) / 1000.0);
    printf("理论时间常数:     %.1f s (%d 步)\n", params.t, (int)(params.t / params.dt));
    printf("----------------------------------------\n");
}

/* ============================================================================
 * Main
 * ========================================================================== */

int main(void)
{
    printf("PLCOpen FirstOrder 功能块性能基准测试\n");
    printf("目标: 单次执行时间 < 1ms (1000000 ns)\n");
    printf("\n");

    bench_first_order_execute();
    bench_first_order_init();
    bench_filter_convergence();

    return 0;
}
