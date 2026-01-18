# 性能基准测试结果

## 测试环境

- **平台**: Linux x86_64
- **编译器**: GCC 11.x
- **优化级别**: -O2
- **测试日期**: 2026-01-18

## 测试目标

| 指标 | 目标 | 状态 |
|------|------|------|
| PID 单次执行时间 | < 1ms | ✓ 通过 |
| FirstOrder 单次执行时间 | < 1ms | ✓ 通过 |
| PID 实例内存 | < 1KB | ✓ 通过 |
| FirstOrder 实例内存 | < 1KB | ✓ 通过 |

## 执行时间测试

### PID execute()

| 指标 | 值 |
|------|------|
| 迭代次数 | 100,000 |
| 最小时间 | ~50 ns |
| 最大时间 | ~500 ns |
| 平均时间 | ~100 ns |
| 标准差 | ~30 ns |

**结论**: PID 单次执行远低于 1ms 目标，约 0.1μs 级别。

### FirstOrder execute()

| 指标 | 值 |
|------|------|
| 迭代次数 | 100,000 |
| 最小时间 | ~30 ns |
| 最大时间 | ~300 ns |
| 平均时间 | ~50 ns |
| 标准差 | ~20 ns |

**结论**: FirstOrder 单次执行更快，约 0.05μs 级别。

## 内存占用测试

### 结构体大小

| 结构体 | 大小 (bytes) |
|--------|-------------|
| pid_params_t | 48 |
| pid_input_t | 16 |
| pid_output_t | 24 |
| pid_state_t | 24 |
| **pid_instance_t** | **120** |
| first_order_params_t | 24 |
| first_order_state_t | 8 |
| **first_order_instance_t** | **48** |

**结论**: 所有功能块实例均远小于 1KB 目标。

### 批量实例化

| 实例数量 | PID 内存 | FirstOrder 内存 |
|----------|----------|-----------------|
| 1 | 0 KB | 0 KB |
| 10 | 1 KB | 0 KB |
| 100 | 12 KB | 5 KB |
| 1000 | 117 KB | 47 KB |

## 初始化时间

| 操作 | 平均时间 |
|------|----------|
| pid_init_with_params() | ~80 ns |
| first_order_init_with_params() | ~40 ns |

## 状态保存/恢复时间

| 操作 | 平均时间 |
|------|----------|
| pid_get_state() | ~20 ns |
| pid_set_state() | ~20 ns |
| first_order_get_state() | ~10 ns |
| first_order_set_state() | ~10 ns |

**结论**: 热重载状态保存/恢复开销极低。

## 周期预算分析

假设 10ms 周期：

| 组件 | 时间 | 占比 |
|------|------|------|
| 10 个 PID 执行 | ~1 μs | 0.01% |
| 10 个 FirstOrder 执行 | ~0.5 μs | 0.005% |
| Python 调用开销（估计） | ~100 μs | 1% |
| 用户脚本逻辑（估计） | ~500 μs | 5% |
| **剩余预算** | **~9.4 ms** | **94%** |

**结论**: C 功能块执行开销可忽略不计，Python 调用开销是主要因素。

## 建议

1. **高频控制**（<1ms 周期）：直接使用 C 接口
2. **常规控制**（10-100ms 周期）：Python 脚本完全满足需求
3. **批量实例**：1000 个实例仅占用约 165KB，适合复杂控制策略

## 运行基准测试

```bash
# 构建基准测试
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_BENCHMARKS=ON
cmake --build build

# 运行测试
./build/bench_pid
./build/bench_first_order
./build/bench_memory
```
