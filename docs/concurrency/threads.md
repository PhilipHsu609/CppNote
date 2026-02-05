---
title: "Threads"
since: "C++11"
---

# Threads

Thread creation and management.

## Basic Usage

```cpp
#include <thread>

void task() {
    // work
}

std::thread t(task);
t.join();  // wait for completion
// or
t.detach(); // run independently
```

## Thread Information

```cpp
// Hardware concurrency (hint for thread count)
unsigned int n = std::thread::hardware_concurrency();

// Current thread ID
std::this_thread::get_id();

// Sleep
using namespace std::chrono_literals;
std::this_thread::sleep_for(100ms);
std::this_thread::sleep_until(time_point);

// Yield
std::this_thread::yield();
```

## Passing Arguments

```cpp
void func(int x, std::string& s);

int n = 42;
std::string str = "hello";

// Arguments are copied by default
std::thread t1(func, n, std::ref(str));  // std::ref for reference

// Move-only types
std::thread t2(func, 1, std::move(str));
```

## RAII Wrapper (C++20: jthread)

```cpp
// C++20: automatically joins on destruction
std::jthread t(task);
// No need to call join() - destructor handles it

// Also supports stop_token for cancellation
std::jthread t2([](std::stop_token token) {
    while (!token.stop_requested()) {
        // work
    }
});
t2.request_stop();
```

## Key Points

- Always `join()` or `detach()` before thread destructor
- Pass references with `std::ref()`
- `hardware_concurrency()` is a hint, not guaranteed
- Prefer `std::jthread` (C++20) for automatic joining
- Threads are move-only (cannot copy)

## See Also

- [mutex](mutex.md) - synchronization
- [async](async.md) - higher-level async
