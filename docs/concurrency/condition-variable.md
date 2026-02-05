---
title: "Condition Variables"
since: "C++11"
---

# Condition Variables

Wait for conditions in multi-threaded code.

## Basic Pattern

```cpp
#include <condition_variable>
#include <mutex>

std::mutex m;
std::condition_variable cv;
bool ready = false;

// Producer
void producer() {
    {
        std::lock_guard lock(m);
        ready = true;
    }
    cv.notify_one();  // or notify_all()
}

// Consumer
void consumer() {
    std::unique_lock lock(m);
    cv.wait(lock, []{ return ready; });  // waits until ready
    // proceed with work
}
```

## Wait Variants

```cpp
std::unique_lock lock(m);

// Wait indefinitely
cv.wait(lock);

// Wait with predicate (handles spurious wakeups)
cv.wait(lock, []{ return condition; });

// Wait with timeout
cv.wait_for(lock, 100ms);
cv.wait_for(lock, 100ms, []{ return condition; });

cv.wait_until(lock, time_point);
cv.wait_until(lock, time_point, []{ return condition; });
```

## Why Predicate?

Condition variables can have **spurious wakeups**. Always use a predicate:

```cpp
// BAD: can wake up when condition is still false
cv.wait(lock);
if (data_ready) { /* use data */ }

// GOOD: rechecks condition after wakeup
cv.wait(lock, []{ return data_ready; });
// equivalent to:
while (!data_ready) {
    cv.wait(lock);
}
```

## Notification

```cpp
cv.notify_one();  // wake one waiting thread
cv.notify_all();  // wake all waiting threads
```

## Key Points

- Requires `unique_lock` (not `lock_guard`)
- Always use predicate form to handle spurious wakeups
- Unlock mutex before notifying (optimization)
- `notify_one` for single consumer, `notify_all` for multiple

## See Also

- [mutex](mutex.md) - locks
- [future-promise](future-promise.md) - one-shot signaling
