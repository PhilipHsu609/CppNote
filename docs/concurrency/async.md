---
title: "std::async"
since: "C++11"
---

# std::async

High-level asynchronous execution.

## Basic Usage

```cpp
#include <future>

std::future<int> f = std::async([] {
    return expensive_computation();
});

// Do other work...

int result = f.get();  // blocks until ready
```

## Launch Policies

```cpp
// async: run in new thread
std::future<int> f1 = std::async(std::launch::async, task);

// deferred: run when get() is called (same thread)
std::future<int> f2 = std::async(std::launch::deferred, task);

// default: implementation chooses (async | deferred)
std::future<int> f3 = std::async(task);
```

## Gotcha: Future Destruction

The future from `std::async` **blocks on destruction**:

```cpp
// Each async blocks until complete!
std::async(std::launch::async, long_task);  // blocks here
std::async(std::launch::async, long_task);  // then blocks here
// Total time: 2x long_task

// Keep the futures to run in parallel
auto f1 = std::async(std::launch::async, long_task);
auto f2 = std::async(std::launch::async, long_task);
f1.get();
f2.get();
// Total time: 1x long_task (parallel)
```

## Hierarchy

From high to low level:

```
std::async         - simplest, manages threading
    ↓
std::packaged_task - wrap callable, get future
    ↓
std::promise       - manual value setting
```

## Key Points

- Use `std::launch::async` if you need parallelism
- `deferred` runs lazily on `get()`
- Don't discard the future (it will block!)
- For fire-and-forget, use raw threads or thread pools
- No built-in thread pool (use external library)

## See Also

- [future-promise](future-promise.md) - lower-level primitives
- [threads](threads.md) - manual thread control
