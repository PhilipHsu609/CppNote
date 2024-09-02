#include <atomic>             // atomic
#include <chrono>             // chrono_literals
#include <condition_variable> // condition_variable
#include <fmt/core.h>         // print
#include <fmt/std.h>          // formater for std things
#include <mutex>              // mutex, call_once, once_flag
#include <shared_mutex>       // shared_mutex, shared_lock
#include <thread>             // thread
#include <vector>             // vector

static int counter = 0;
std::mutex m;
std::condition_variable cv;

std::mutex lock1, lock2;
std::shared_mutex shared_mutex;       // shared_mutex is a reader-writer mutex
std::recursive_mutex recursive_mutex; // recursive_mutex is a mutex that can be locked
                                      // multiple times by the same thread

void call_once_task() { fmt::print("I should only be called once.\n"); }

void normal_task() {
    using namespace std::chrono_literals;
    fmt::print("Hello from task!\n");

    // call_once will only call the function once even if it's called by multiple threads
    // It's useful for lazy initialization.
    std::once_flag flag;
    std::call_once(flag, call_once_task);

    {
        std::lock_guard lock(m);
        counter++;
        // lock_guard will unlock the mutex when it goes out of scope

        std::shared_lock shared_lock(shared_mutex); // obtain shared access for readers
        std::lock_guard lock2(shared_mutex);        // obtain exclusive access for writers
    }

    {
        // Since C++17, scoped_lock can owning zero or more locks
        // Will unlock all locks when it goes out of scope
        std::scoped_lock lock(lock1, lock2);

        // Equivalent code 1:
        std::lock(lock1, lock2); // acquire lock1 and lock2 and prevent deadlock
        std::lock_guard lock1_guard(lock1, std::adopt_lock); // lock wrapper for RAII
        std::lock_guard lock2_guard(lock2, std::adopt_lock); // lock wrapper for RAII

        // Equivalent code 2:
        std::unique_lock lock1_uguard(lock1, std::defer_lock); // Wrap a lock first
        std::unique_lock lock2_uguard(lock2, std::defer_lock);
        std::lock(lock1_uguard, lock2_uguard); // Then lock them
    }

    fmt::print("{}\n", std::this_thread::get_id());
    std::this_thread::sleep_for(100ms);
}

void atomic() {
    // The simpliest atomic type
    std::atomic_flag flag = ATOMIC_FLAG_INIT; // MUST BE INITIALIZED

    bool ret = flag.test_and_set(); // Set the flag
    flag.clear();                   // Clear the flag

    // atomic_flag can used to implement spinlock
    while (flag.test_and_set(std::memory_order_acquire))
        ;                                  // lock()
    flag.clear(std::memory_order_release); // unlock()

    std::atomic<bool> b(true);
    b = false;

    bool x = b.load(std::memory_order_acquire);
    b.store(true);
    x = b.exchange(false, std::memory_order_acq_rel);

    b.compare_exchange_strong(x, true); // if x == b, set b to true

    // if x == b, set b to true, but may fail
    // so we a loop
    while (!b.compare_exchange_weak(x, true) && !x)
        ;
}

int main() {
    std::vector<std::thread> threads;

    fmt::print("Hardware concurrency: {}\n", std::thread::hardware_concurrency());

    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread(normal_task));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    fmt::print("Counter: {}\n", counter);
    threads.clear();

    bool done = false;
    std::thread producer([&]() {
        using namespace std::chrono_literals;
        std::unique_lock lock(m);

        std::this_thread::sleep_for(1s);

        done = true;
        cv.notify_one(); // or cv.notify_all();
    });

    std::thread consumer([&]() {
        std::unique_lock lock(m);

        if (!done) {
            cv.wait(lock);
        }
    });

    producer.join();
    consumer.join();

    return 0;
}