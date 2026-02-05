---
title: "std::chrono"
since: "C++11"
---

# Chrono

Time utilities and clocks.

## Time Types

- **Wall-clock time**: Real-world elapsed time
- **CPU time**: Time spent executing on CPU
- **System time**: Time spent in kernel (syscalls, I/O)

## Clocks

```cpp
#include <chrono>
using namespace std::chrono;

// system_clock: wall-clock, can be adjusted
auto t1 = system_clock::now();

// steady_clock: monotonic, for measuring durations
auto t2 = steady_clock::now();

// high_resolution_clock: highest precision available
auto t3 = high_resolution_clock::now();
```

## Measuring Duration

```cpp
using namespace std::chrono;

auto start = steady_clock::now();
// ... work ...
auto end = steady_clock::now();

duration<double> diff = end - start;
auto ms = duration_cast<milliseconds>(diff);
auto us = duration_cast<microseconds>(diff);
```

## Duration Literals (C++14)

```cpp
using namespace std::chrono_literals;

auto hour = 1h;
auto minute = 30min;
auto second = 45s;
auto milli = 100ms;
auto micro = 500us;
auto nano = 1000ns;
```

## CPU Time (C-style)

```cpp
#include <ctime>

clock_t start = std::clock();
// ... work ...
clock_t end = std::clock();

double cpu_time = double(end - start) / CLOCKS_PER_SEC;
```

## Key Points

- Use `steady_clock` for measuring durations (monotonic)
- Use `system_clock` for wall-clock time
- Duration literals make code readable
- `duration_cast` for conversions
- C++20 adds calendar and time zone support

## See Also

- [threads](../concurrency/threads.md) - `sleep_for` uses chrono
