---
title: "Memory Ordering"
since: "C++11"
---


Control how atomic operations are ordered across threads.

## Memory Order Options

```cpp
std::memory_order_relaxed      // no ordering, only atomicity
std::memory_order_acquire      // read barrier
std::memory_order_release      // write barrier
std::memory_order_acq_rel      // both acquire and release
std::memory_order_seq_cst      // sequential consistency (default)
```

## Sequential Consistency

All threads see operations in the same order:

```cpp
std::atomic<bool> x{false}, y{false};
std::atomic<int> z{0};

// Thread 1
x.store(true, std::memory_order_seq_cst);

// Thread 2
y.store(true, std::memory_order_seq_cst);

// Thread 3
while (!x.load(std::memory_order_seq_cst));
if (y.load(std::memory_order_seq_cst)) ++z;

// Thread 4
while (!y.load(std::memory_order_seq_cst));
if (x.load(std::memory_order_seq_cst)) ++z;

// z is always 1 or 2, never 0
```

## Relaxed Ordering

Only guarantees atomicity, no ordering:

```cpp
std::atomic<bool> x{false}, y{false};

// Thread 1
x.store(true, std::memory_order_relaxed);
y.store(true, std::memory_order_relaxed);

// Thread 2
while (!y.load(std::memory_order_relaxed));
// x might still be false! (reordering allowed)
```

## Acquire-Release

Synchronizes producer and consumer:

```cpp
std::atomic<bool> ready{false};
int data;

// Producer
data = 42;
ready.store(true, std::memory_order_release);

// Consumer
while (!ready.load(std::memory_order_acquire));
// data is guaranteed to be 42
```

Release ensures all prior writes are visible.
Acquire ensures all subsequent reads see those writes.

## When to Use What

| Use Case | Memory Order |
|----------|--------------|
| Simple counter | `relaxed` |
| Flag/condition | `acquire`/`release` |
| Default (safe) | `seq_cst` |

## Key Points

- `seq_cst` is safest but slowest
- `relaxed` is fastest but provides no ordering
- `acquire`/`release` pairs synchronize specific operations
- Most code should use `seq_cst` unless performance-critical
- Memory ordering bugs are extremely hard to debug

## See Also

- [atomic](../concurrency/atomic.md) - atomic operations
