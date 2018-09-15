#include "Benchmark.h"
#include <cstdint>
#include <vector>
#include <chrono>

Benchmark::Benchmark(int num_tests, int num_iterations, const uint64_t *nums)
    : _num_tests(num_tests), _num_iterations(num_iterations), _nums(nums)
{
}

uint64_t
Benchmark::warmup_cache()
{
    auto len = 0ULL;
    for (int i = 0; i < _num_tests; i++)
    {
        len += _nums[i];
    }

    for (auto &d: _durations) len += d;
    return len;
}

uint32_t Benchmark::run(uint32_t (*func)(uint64_t, char *))
{
    _durations.clear();
    _durations.reserve(_num_iterations * _num_tests);

    char buf[64];
    for (int i = 0; i < _num_iterations; i++)
    {
        for (int j = 0; j < _num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = func(_nums[j], buf);
            auto end = std::chrono::high_resolution_clock::now();

            // save the measured duration
            _durations.emplace_back(
                (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start))
                    .count()
            );
        }
    }

    auto total = 0ULL;
    for (const auto &d : _durations) total += d;
    return total / _durations.size();
}
