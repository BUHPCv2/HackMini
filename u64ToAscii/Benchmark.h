#pragma once

#include <cstdint>
#include <vector>

class Benchmark
{
public:
    Benchmark() = delete;
    Benchmark(int, int, const uint64_t *);
    
    void set_benchmark(int, int, const uint64_t *);
    uint64_t warmup_cache();
    uint32_t run(uint32_t (*)(uint64_t, char *));
private:
    int _num_tests;
    int _num_iterations;
    const uint64_t *_nums;
    std::vector<uint64_t> _durations;
};
