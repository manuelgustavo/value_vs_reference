#include <benchmark/benchmark.h>
#include <memory>

template<int COUNT>
void func_by_value(std::shared_ptr<int> v)
{
    func_by_value<COUNT-1>(v);
}

template<>
void func_by_value<1>(std::shared_ptr<int> v)
{
    // prevent "optimization away" of v;
    volatile int i = *v;
}

template<int COUNT>
void func_by_reference(const std::shared_ptr<int>& v)
{
    func_by_reference<COUNT-1>(v);
}

template<>
void func_by_reference<1>(const std::shared_ptr<int>& v)
{
    // prevent "optimization away" of v;
    volatile int i = *v;
}

auto p_i = std::make_shared<int>(1);

#define BM_SHARED_PTR_BY_VALUE_DEPTH_OF(x) \
static void bm_shared_ptr_by_value_depth_of_##x(benchmark::State& state) \
{\
    for (auto _ : state)\
    {\
        func_by_value<x>(p_i);\
    }\
}
#define BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(x) \
static void bm_shared_ptr_by_const_reference_depth_of_##x(benchmark::State& state) \
{ \
    for (auto _ : state) \
    { \
        func_by_reference<x>(p_i); \
    } \
}

BM_SHARED_PTR_BY_VALUE_DEPTH_OF(1)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(2)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(4)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(8)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(16)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(32)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(64)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(128)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(256)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(512)
BM_SHARED_PTR_BY_VALUE_DEPTH_OF(1024)

BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(1)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(2)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(4)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(8)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(16)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(32)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(64)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(128)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(256)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(512)
BM_SHARED_PTR_BY_CONST_REFERENCE_DEPTH_OF(1024)
// Register the function as a benchmark
BENCHMARK(bm_shared_ptr_by_value_depth_of_1);
BENCHMARK(bm_shared_ptr_by_value_depth_of_2);
BENCHMARK(bm_shared_ptr_by_value_depth_of_4);
BENCHMARK(bm_shared_ptr_by_value_depth_of_8);
BENCHMARK(bm_shared_ptr_by_value_depth_of_16);
BENCHMARK(bm_shared_ptr_by_value_depth_of_32);
BENCHMARK(bm_shared_ptr_by_value_depth_of_128);
BENCHMARK(bm_shared_ptr_by_value_depth_of_256);
BENCHMARK(bm_shared_ptr_by_value_depth_of_512);
BENCHMARK(bm_shared_ptr_by_value_depth_of_1024);

BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_1);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_2);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_4);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_8);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_16);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_32);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_128);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_256);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_512);
BENCHMARK(bm_shared_ptr_by_const_reference_depth_of_1024);


// Run the benchmark
BENCHMARK_MAIN();