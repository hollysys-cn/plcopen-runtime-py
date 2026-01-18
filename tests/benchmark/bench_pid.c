/**
 * @file bench_pid.c
 * @brief PID功能块性能基准测试
 * @version 1.0
 * @date 2026-01-18
 *
 * 测试目标：单次执行时间 < 1ms
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "plcopen/fb_pid.h"

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

static void bench_pid_execute(void)
{
    pid_instance_t pid;
    pid_params_t params = {
        .kp = 2.0,
        .ki = 0.1,
        .kd = 0.5,
        .out_min = -100.0,
        .out_max = 100.0,
        .dt = 0.1
    };

    pid_init_with_params(&pid, &params);

    stats_t stats;
    stats_init(&stats);

    /* 预热 */
    printf("预热中 (%d 次)...\n", WARMUP_ITERATIONS);
    for (int i = 0; i < WARMUP_ITERATIONS; i++) {
        pid_input_t input = {.setpoint = 100.0, .pv = 80.0 + i * 0.001};
        pid_execute(&pid, &input);
    }

    /* 基准测试 */
    printf("基准测试中 (%d 次)...\n", BENCHMARK_ITERATIONS);

    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        pid_input_t input = {.setpoint = 100.0, .pv = 80.0 + sin(i * 0.01) * 10.0};

        double start = get_time_ns();
        pid_execute(&pid, &input);
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
    printf("PID execute() 性能测试结果\n");
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

static void bench_pid_init(void)
{
    stats_t stats;
    stats_init(&stats);

    printf("\nPID init() 性能测试...\n");

    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        pid_instance_t pid;
        pid_params_t params = {
            .kp = 2.0 + i * 0.00001,
            .ki = 0.1,
            .kd = 0.5,
            .out_min = -100.0,
            .out_max = 100.0,
            .dt = 0.1
        };

        double start = get_time_ns();
        pid_init_with_params(&pid, &params);
        double end = get_time_ns();

        stats_add(&stats, end - start);
    }

    printf("----------------------------------------\n");
    printf("PID init() 性能测试结果\n");
    printf("----------------------------------------\n");
    printf("平均时间:   %.2f ns\n", stats_mean(&stats));
    printf("最大时间:   %.2f ns\n", stats.max);
    printf("----------------------------------------\n");
}

static void bench_pid_state_operations(void)
{
    pid_instance_t pid;
    pid_state_t state;
    pid_params_t params = {
        .kp = 2.0, .ki = 0.1, .kd = 0.5,
        .out_min = -100.0, .out_max = 100.0, .dt = 0.1
    };
    pid_init_with_params(&pid, &params);

    stats_t get_stats, set_stats;
    stats_init(&get_stats);
    stats_init(&set_stats);

    printf("\nPID get_state/set_state 性能测试...\n");

    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        double start, end;

        start = get_time_ns();
        pid_get_state(&pid, &state);
        end = get_time_ns();
        stats_add(&get_stats, end - start);

        start = get_time_ns();
        pid_set_state(&pid, &state);
        end = get_time_ns();
        stats_add(&set_stats, end - start);
    }

    printf("----------------------------------------\n");
    printf("get_state() 平均时间: %.2f ns\n", stats_mean(&get_stats));
    printf("set_state() 平均时间: %.2f ns\n", stats_mean(&set_stats));
    printf("----------------------------------------\n");
}

/* ============================================================================
 * Main
 * ========================================================================== */

int main(void)
{
    printf("PLCOpen PID 功能块性能基准测试\n");
    printf("目标: 单次执行时间 < 1ms (1000000 ns)\n");
    printf("\n");

    bench_pid_execute();
    bench_pid_init();
    bench_pid_state_operations();

    return 0;
}
