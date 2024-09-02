#include <fmt/core.h>

namespace Casting {
/*
    Class casting

    C -> A <- B

    1. Upcasting
        - Derived to Base (B -> A or C -> A)
        - Implicit or explicit
        - It's safe
        - static_cast or dynamic_cast
    2. Downcasting
        - Base to Derived (A -> B or A -> C)
        - Explicit
        - It's unsafe
        - static_cast or dynamic_cast
    3. Sidecasting
        - Between siblings (B <-> C)
        - Explicit
        - It's unsafe
        - dynamic_cast
*/
struct A {
    virtual void f() { fmt::println("A::f"); }
};
struct B : A {
    int x = 1;
    void f() override { fmt::println("B::f"); }
};
struct C : A {
    int y = 2;
    void f() override { fmt::println("C::f"); }
};
void test() {
    A a;
    B b;
    C c;

    // Upcasting
    A &a1 = b;                // Implicit upcasting
    static_cast<A &>(b).f();  // B::f
    dynamic_cast<A &>(b).f(); // B::f

    // Downcasting
    static_cast<B &>(a).f(); // A::f
    // dynamic_cast<B &>(a).f(); // throw std::bad_cast
    fmt::println("Indeterminate value: {}", static_cast<B &>(a).x);

    // Sidecasting
    // dynamic_cast<C &>(b).f(); // throw std::bad_cast
    // static_cast<C &>(b).f();  // Compile error
}
} // namespace Casting

namespace RTTI {
/*
    Run-Time Type Information (RTTI) is a mechanism that allows the type of an object to
    be determined during runtime.
        - dynamic_cast
        - typeid: keyword
        - type_info: a class returned by typeid
*/
struct A {
    virtual void f() {}
};
struct B : A {};
struct C : A {};
void test() {
    A a;
    B b;
    A &a_ref = b;

    fmt::println("typeid(a).name(): {}", typeid(a).name());     // N4RTTI1AE (A)
    fmt::println("typeid(b).name(): {}", typeid(b).name());     // N4RTTI1BE (B)
    fmt::println("typeid(c).name(): {}", typeid(a_ref).name()); // N4RTTI1BE (B)

    if (typeid(a) == typeid(a_ref)) {
        fmt::println("a and a_ref are the same type");
    } else {
        fmt::println("a and a_ref are different types"); // printed
    }

    // dynamic_cast happens at runtime and it's expensive.
    A &a_ref2 = dynamic_cast<A &>(b); // upcasting

    try {
        B &b_ref =
            dynamic_cast<B &>(a); // downcasting / cannot be converted when references
    } catch (std::bad_cast &e) {
        fmt::println("Exception: {}", e.what());
    }

    C *c = dynamic_cast<C *>(&a); // nullptr / cannot be converted when pointers
    if (c == nullptr) {
        fmt::println("c is nullptr");
    }
}
} // namespace RTTI

int main() {
    Casting::test();
    RTTI::test();
    return 0;
}