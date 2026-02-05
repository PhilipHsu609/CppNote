---
title: "Atomic Operations"
since: "C++11"
---


Lock-free thread-safe operations.

## Basic Usage

```cpp
#include <atomic>

std::atomic<int> counter{0};

counter++;              // atomic increment
counter.load();         // atomic read
counter.store(10);      // atomic write
counter.exchange(20);   // atomic swap, returns old value
```

## atomic_flag

Simplest atomic type (guaranteed lock-free):

```cpp
std::atomic_flag flag = ATOMIC_FLAG_INIT;

flag.test_and_set();  // set and return previous value
flag.clear();         // clear the flag
```

## Spinlock with atomic_flag

```cpp
std::atomic_flag lock = ATOMIC_FLAG_INIT;

void acquire() {
    while (lock.test_and_set(std::memory_order_acquire))
        ; // spin
}

void release() {
    lock.clear(std::memory_order_release);
}
```

## Compare-and-Swap

```cpp
std::atomic<int> value{5};
int expected = 5;

// If value == expected, set value to 10
bool success = value.compare_exchange_strong(expected, 10);
// If failed, expected now contains actual value

// Weak version may fail spuriously (use in loops)
while (!value.compare_exchange_weak(expected, 10)) {
    // expected updated with current value
}
```

## Memory Order

```cpp
// Default: sequential consistency (safest, slowest)
x.store(1);  // same as x.store(1, std::memory_order_seq_cst)

// Relaxed: only atomicity, no ordering
x.store(1, std::memory_order_relaxed);

// Acquire-Release: synchronizes between threads
x.store(1, std::memory_order_release);  // writer
x.load(std::memory_order_acquire);       // reader
```

## Key Points

- Atomic operations are indivisible
- `atomic_flag` is always lock-free
- `std::atomic<T>` may use locks for large T
- Use `memory_order_seq_cst` unless you need performance
- Acquire-release for producer-consumer patterns

## See Also

- [memory-order](../memory/memory-order.md) - memory ordering details
- [mutex](mutex.md) - when atomics aren't enough
