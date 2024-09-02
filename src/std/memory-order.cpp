#include <atomic>
#include <cassert>
#include <thread>

#include <fmt/core.h>

namespace sequential_consistency {
/*
    The behavior is same as if all operations were performed in some sequence by a single
    thread.
*/
std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() { x.store(true, std::memory_order_seq_cst); }
void write_y() { y.store(true, std::memory_order_seq_cst); }

void read_x_then_y() {
    while (!x.load(std::memory_order_seq_cst)) // wait for x to be set
        ;
    if (y.load(std::memory_order_seq_cst)) {
        ++z;
        return;
    }
    /*
        If the thread reaches this point, we know that x.store happened before y.store.
    */
}

void read_y_then_x() {
    while (!y.load(std::memory_order_seq_cst)) // wait for y to be set
        ;
    if (x.load(std::memory_order_seq_cst)) {
        ++z;
        return;
    }
    /*
        If the thread reaches this point, we know that y.store happened before x.store.
    */
}

void test() {
    x = false;
    y = false;
    z = 0;

    std::thread a(write_x);
    std::thread b(write_y);

    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();

    // z will be 1 or 2
    assert(z.load() != 0);
}
} // namespace sequential_consistency

namespace non_sequential_consistency::relaxed_ordering {
/*
    No synchronization or ordering constraints, only atomicity is guaranteed.
*/
std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y() {
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
    while (!y.load(std::memory_order_relaxed))
        ;

    //
    if (x.load(std::memory_order_relaxed)) {
        ++z;
    }
}

void test() {
    x = false;
    y = false;
    z = 0;

    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);

    a.join();
    b.join();

    assert(z.load() != 0);
}
} // namespace non_sequential_consistency::relaxed_ordering