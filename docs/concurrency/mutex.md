---
title: "Mutex and Locks"
since: "C++11"
---


Thread synchronization primitives.

## Basic Mutex

```cpp
#include <mutex>

std::mutex m;

void safe_increment(int& counter) {
    std::lock_guard<std::mutex> lock(m);
    counter++;
    // automatically unlocks when lock goes out of scope
}
```

## Lock Types

```cpp
// lock_guard: simple RAII lock
std::lock_guard<std::mutex> lg(m);

// unique_lock: more flexible (can unlock/relock)
std::unique_lock<std::mutex> ul(m);
ul.unlock();
ul.lock();

// scoped_lock (C++17): locks multiple mutexes, prevents deadlock
std::scoped_lock lock(mutex1, mutex2);

// shared_lock: for reader-writer scenarios
std::shared_lock<std::shared_mutex> sl(shared_m);
```

## Mutex Types

```cpp
std::mutex m;              // basic mutex
std::recursive_mutex rm;   // same thread can lock multiple times
std::timed_mutex tm;       // supports try_lock_for/until
std::shared_mutex sm;      // reader-writer (C++17)
```

## Avoiding Deadlock

```cpp
std::mutex m1, m2;

// BAD: potential deadlock
void bad() {
    std::lock_guard l1(m1);
    std::lock_guard l2(m2);  // if another thread locks m2 then m1...
}

// GOOD: std::lock acquires both atomically
void good() {
    std::lock(m1, m2);
    std::lock_guard l1(m1, std::adopt_lock);
    std::lock_guard l2(m2, std::adopt_lock);
}

// BETTER (C++17): scoped_lock
void better() {
    std::scoped_lock lock(m1, m2);
}
```

## call_once

Ensure code runs exactly once (thread-safe):

```cpp
std::once_flag flag;

void init() {
    std::call_once(flag, []() {
        // initialization code
        // runs exactly once, even from multiple threads
    });
}
```

## Key Points

- Always use RAII locks (`lock_guard`, `scoped_lock`)
- Never call `lock()` / `unlock()` manually
- Use `scoped_lock` for multiple mutexes
- `shared_mutex` for read-heavy workloads
- `call_once` for thread-safe initialization

## See Also

- [condition-variable](condition-variable.md) - waiting for conditions
- [atomic](atomic.md) - lock-free operations
