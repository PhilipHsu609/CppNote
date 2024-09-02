/*
    Time
    - Wall-clock/Real time
        - Time elapsed in the real world
    - User/CPU time
        - Time spent in the CPU
        - For multiple threads, it's the sum of all threads
    - System time
        - Time spent in the kernel (syscall, io, etc)
*/

#include <fmt/chrono.h>

// Only for Unix
#include <sys/time.h> // gettimeofday
#include <time.h>     // struct timeval

void test_wall_clock1() {
    struct timeval start, end;

    ::gettimeofday(&start, nullptr);

    // Code to measure

    ::gettimeofday(&end, nullptr);

    long start_time = start.tv_sec * 1'000'000 + start.tv_usec;
    long end_time = end.tv_sec * 1'000'000 + end.tv_usec;

    [[maybe_unused]]
    long elapsed_time = end_time - start_time;
}

// Only for Unix
#include <sys/times.h> // struct tms
#include <unistd.h>    // sysconf, _SC_CLK_TCK

void test_user_system_time() {
    struct ::tms start_time, end_time;
    ::times(&start_time);

    // Code to measure

    ::times(&end_time);

    auto user_time = end_time.tms_utime - start_time.tms_utime;
    auto system_time = end_time.tms_stime - start_time.tms_stime;

    [[maybe_unused]]
    float user = static_cast<float>(user_time) / ::sysconf(_SC_CLK_TCK);
    [[maybe_unused]]
    float system = static_cast<float>(system_time) / ::sysconf(_SC_CLK_TCK);
}

#include <chrono>

void test_wall_clock2() {
    using namespace std::chrono;

    // system_clock is not monotonic increasing (like a watch, depends on the time zone)
    auto start_time = system_clock::now();

    // Code to measure

    auto end_time = system_clock::now();

    duration<double> diff = end_time - start_time;

    [[maybe_unused]]
    auto seconds = duration_cast<std::chrono::seconds>(diff);
    [[maybe_unused]]
    auto milliseconds = duration_cast<std::chrono::milliseconds>(diff);
}

void test_wall_clock3() {
    using namespace std::chrono;

    // POSIX
    // steady_clock is monotonic increasing (like a stopwatch)
    auto start_time = steady_clock::now();

    // Code to measure

    auto end_time = steady_clock::now();

    duration<double> diff = end_time - start_time;

    [[maybe_unused]]
    auto seconds = duration_cast<std::chrono::seconds>(diff);
    [[maybe_unused]]
    auto milliseconds = duration_cast<std::chrono::milliseconds>(diff);
}

void test_user_time() {
    // POSIX
    clock_t start = std::clock();

    // Code to measure

    clock_t end = std::clock();

    [[maybe_unused]]
    float elapsed_time = static_cast<float>(end - start) / CLOCKS_PER_SEC;
}

void time_literals() {
    using namespace std::chrono_literals;

    // from hour(h) to nanosecond(ns)
    fmt::print("1h = {}ns\n", 1h);
    fmt::print("1min = {}ns\n", 1min);
    fmt::print("1s = {}ns\n", 1s);
    fmt::print("1ms = {}ns\n", 1ms);
    fmt::print("1us = {}ns\n", 1us);
    fmt::print("1ns = {}ns\n", 1ns);
}