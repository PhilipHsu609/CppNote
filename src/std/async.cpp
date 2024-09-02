#include <chrono> // chrono_literals
#include <future> // future, async, packaged_task, promise
#include <thread> // thread

#include <fmt/core.h>
#include <fmt/std.h>

/*
    From high level to low level:

    1. std::async
    2. std::packaged_task
    3. std::promise

    A higher level can be implemented by a lower level.
*/

void long_task() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

void basic_async() {
    fmt::print("Main thread: {}\n", std::this_thread::get_id());

    // async policy (potentially run in a separate thread)
    std::future<int> f = std::async(std::launch::async, [] {
        fmt::println("Async thread: {}", std::this_thread::get_id());
        return 1;
    });
    fmt::print("The answer is: {}\n", f.get());

    // deferred policy (will run when get() is called)
    std::future<int> f2 = std::async(std::launch::deferred, [] {
        fmt::println("Deferred thread: {}", std::this_thread::get_id());
        return 2;
    });
    fmt::print("The answer is: {}\n", f2.get());

    // default policy (either async or deferred, actually an undefined behavior)
    std::future<int> f3 = std::async([] { return 42; });
    f3.wait(); // wait for the future to be ready

    //! Special behavior for future
    // The future returned by async has a shared state,
    // which demands ~future() to block
    //
    // We discard the future, so after each std::async call, the returned future
    // destructs, and it blocks until the task is done.
    namespace stdc = std::chrono;
    stdc::time_point start{stdc::steady_clock::now()};
    std::async(std::launch::async, long_task);
    std::async(std::launch::async, long_task);
    stdc::time_point end{stdc::steady_clock::now()};
    fmt::print("Time elapsed: {}ms\n", // 2000ms
               stdc::duration_cast<stdc::milliseconds>(end - start).count());
}

void packaged_task() {
    // packaged_task will not run until it is called
    std::packaged_task<void()> task(long_task);

    // future is associated with the packaged_task
    std::future<void> f = task.get_future();

    // We have to call the task, otherwise future will not be ready
    task();

    // Instead of calling the task, we move the task to a specific std::thread
    std::thread(std::move(task)).detach();

    // Get the future
    f.get();
}

void promise() {
    // promise is used to set the value of the future
    // so we always have a promise and future pair.

    std::promise<int> p;
    std::future<int> f = p.get_future();

    // Inorder to achieve async behavior, we can move the promise to a thread
    std::thread([&p] {
        p.set_value(42); // this thread promises to set the value of the future
    }).detach();

    fmt::print("The answer is: {}\n", f.get());
}