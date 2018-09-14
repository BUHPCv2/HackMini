#include <string>
#include <cstring>
#include <benchmark/benchmark.h>

unsigned long atoul_stream(std::string numstr);
unsigned long atoul_std(const char * begin);
unsigned long atoul_O0(const char * begin, const char * end);
unsigned long atoul_O1(const char * begin, const char * end);
unsigned long atoul_O2(const char * begin, const char * end);

static const std::vector<std::string> num_strings = 
{
    "9","99","999","9999","99999"
    // "999999", "9999999", "99999999", 
    // "999999999", "9999999900", "99999999999", "999999999999", "9999999999999", "99999999999999"
};

// STREAM TEST
static void BM_sstream(benchmark::State& state)
{
    unsigned long a = 0;
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range(0); ++i)
        {
            benchmark::DoNotOptimize(a = atoul_stream(num_strings[i]));
        }
    }
}
BENCHMARK(BM_sstream)->Arg(num_strings.size());

// STDLIB ATOL TEST
static void BM_stdlib(benchmark::State& state)
{
    unsigned long a = 0;
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range(0); ++i)
        {
            benchmark::DoNotOptimize(a = atoul_std(num_strings[i].c_str()));
        }
    }
}
BENCHMARK(BM_stdlib)->Arg(num_strings.size());

// STDLIB ATOUL_O0 TEST
static void BM_atoul_O0(benchmark::State& state)
{
    unsigned long a = 0;
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range(0); ++i)
        {
            benchmark::DoNotOptimize(a = atoul_O0(num_strings[i].c_str(), &(*num_strings[i].end())));
        }
    }
}
BENCHMARK(BM_atoul_O0)->Arg(num_strings.size());

// STDLIB ATOUL_O1 TEST
static void BM_atoul_O1(benchmark::State& state)
{
    unsigned long a = 0;
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range(0); ++i)
        {
            benchmark::DoNotOptimize(a = atoul_O1(num_strings[i].c_str(), &(*num_strings[i].end())));
        }
    }
}
BENCHMARK(BM_atoul_O1)->Arg(num_strings.size());

// STDLIB ATOUL_O2 TEST
static void BM_atoul_O2(benchmark::State& state)
{
    unsigned long a = 0;
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range(0); ++i)
        {
            benchmark::DoNotOptimize(a = atoul_O2(num_strings[i].c_str(), &(*num_strings[i].end())));
        }
    }
}
BENCHMARK(BM_atoul_O2)->Arg(num_strings.size());

// run all registered benchmarks
BENCHMARK_MAIN();
