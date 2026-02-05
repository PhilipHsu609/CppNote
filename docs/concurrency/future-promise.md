---
title: "Future and Promise"
since: "C++11"
---

# Future and Promise

Asynchronous result communication.

## Concept

- **Promise**: producer sets the value
- **Future**: consumer waits for and retrieves the value

```cpp
#include <future>

std::promise<int> p;
std::future<int> f = p.get_future();

// Producer thread
std::thread producer([&p] {
    p.set_value(42);
});

// Consumer
int result = f.get();  // blocks until value is set

producer.join();
```

## packaged_task

Wraps a callable, provides a future:

```cpp
std::packaged_task<int(int, int)> task([](int a, int b) {
    return a + b;
});

std::future<int> f = task.get_future();

// Run task (must be called!)
task(2, 3);

// Or move to a thread
std::thread t(std::move(task), 2, 3);
t.join();

int result = f.get();  // 5
```

## Future Operations

```cpp
std::future<int> f = /* ... */;

f.get();          // block and get result (only once!)
f.wait();         // block until ready (no result)
f.wait_for(100ms);   // wait with timeout
f.wait_until(tp);    // wait until time point

f.valid();        // true if has shared state
```

## Key Points

- `future::get()` can only be called once
- `promise::set_value()` can only be called once
- Use `shared_future` if multiple consumers need the result
- `packaged_task` bridges callables to futures
- Promise-future is one-shot communication

## See Also

- [async](async.md) - higher-level async
- [threads](threads.md) - raw threads
