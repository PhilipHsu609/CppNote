#include <fmt/core.h>

#include <functional> // function, bind, placeholders
#include <utility>

struct A {
    void a(int n) { fmt::print("A::a({})\n", n); }
};

void foo(int a, int b, int c, int d, int e) {
    fmt::print("a: {}, b: {}, c: {}, d: {}, e: {}\n", a, b, c, d, e);
}

// A wrapper for std::invoke
template <typename Callable, typename... Args>
decltype(auto) call(Callable &&op, Args &&...args) {
    return std::invoke(std::forward<Callable>(op), std::forward<Args>(args)...);
}

int add(int a, int b) { return a + b; }

struct Multiply {
    int operator()(int a, int b) const { return a * b; }
};

auto subtract = [](int a, int b) { return a - b; };

int main() {
    // function object is a general-purpose polymorphic function wrapper
    // f stores a lambda function
    std::function<void()> f = []() { fmt::print("Hello from function!\n"); };

    // std::bind can bind arguments to a function
    auto myfoo = std::bind(foo, 1, 2, 3, 4, 5);
    myfoo(); // equivalent to foo(1, 2, 3, 4, 5)

    // or bind with placeholders
    using namespace std::placeholders; // for _1, _2, _3, ...
    auto myfoo2 = std::bind(foo, 1, _3, 5, _2, _1);

    // equivalent to foo(1, 4, 5, 3, 2)
    // _4 is not used in bind, so it's ignored
    myfoo2(2, 3, 4, 'c');

    // function pointer to member function
    A a;
    auto a_wrap = &A::a;
    (a.*a_wrap)(1); // (a->*a_wrap)(1) for pointer

    // or use std::mem_fn, a wrapper for member function
    auto a_wrap2 = std::mem_fn(&A::a);
    a_wrap2(a, 2);

    // call function with std::invoke
    call(add, 1, 2);
    call(Multiply{}, 3, 4);
    call(subtract, 5, 6);
    call([](int a, int b) { return a / b; }, 7, 8);
}