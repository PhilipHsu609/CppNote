#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iostream>

struct A {
    std::size_t s;
    int *p;
    A(std::size_t s) : s(s), p(new int[s]) {}
    ~A() { delete[] p; }
    A(A const &other) : s(other.s), p(new int[other.s]) {
        std::copy(other.p, other.p + s, this->p);
    }
    A(A &&other) : s(other.s), p(other.p) {
        other.s = 0;
        other.p = nullptr;
    }
    friend void swap(A &a, A &b) {
        using std::swap;
        swap(a.s, b.s);
        swap(a.p, b.p);
    }
#if DESIGN != 3
    A &operator=(A const &other) {
        if (this != &other) {
            delete[] p;
            p = nullptr;
            s = 0;
            p = new int[other.s];
            s = other.s;
            std::copy(other.p, other.p + s, this->p);
        }
        return *this;
    }
#endif
#if DESIGN == 1
    // Move assignment operator #1
    A &operator=(A &&other) {
        swap(*this, other);
        return *this;
    }
#elif DESIGN == 2
    // Move assignment operator #2
    A &operator=(A &&other) {
        delete[] p;
        s = other.s;
        p = other.p;
        other.s = 0;
        other.p = nullptr;
        return *this;
    }
#elif DESIGN == 3
    A &operator=(A other) {
        swap(*this, other);
        return *this;
    }
#endif
};

constexpr std::size_t size = 2 * 1024;

float test_copy() {
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<float, std::nano> NS;

    float t = 0;
    for (int i = 0; i < 100; i++) {
        A a1(size);
        A a2(size);
        auto t0 = Clock::now();
        a2 = a1;
        auto t1 = Clock::now();
        t += NS(t1 - t0).count();
    }
    return t / 100.0f;
}

float test_move() {
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<float, std::nano> NS;

    float t = 0;
    for (int i = 0; i < 100; i++) {
        A a1(size);
        A a2(size);
        auto t0 = Clock::now();
        a2 = std::move(a1);
        auto t1 = Clock::now();
        t += NS(t1 - t0).count();
    }
    return t / 100.0f;
}

int main() {
    std::cout << "----- Test copy -----\n";
    std::cout << "copy takes " << test_copy() << "ns\n";
    std::cout << "----- Test move -----\n";
    std::cout << "move takes " << test_move() << "ns\n";
}