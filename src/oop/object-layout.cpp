/*
    layout refers to how an object is stored in memory.
        - aggregate
        - trivial copyable
        - standard layout
        - plain old data
*/
#include <type_traits>

namespace Aggregates {
/*
    An aggregate is an array, struct, or class which supports aggregate initialization
    (form of list-initialization) through curly braces syntax.

    1. No user-provided, inherited or explicit constructors.
        - user-provided if user-declared and not explicitly defaulted or deleted
    2. No private or protected non-static data members.
    3. No virtual base classes.
    4. No private or protected direct base classes.
    5. No virtual member functions.

    Apply those rules recursively to all non-static data members and base classes.
*/
struct A {
    int a;
    int b[3];
    int c{2};

    A() = default; // ok, user-declared but not user-provided
    void f();

  private:
    void g();
};

struct B {
    explicit B() {} // user-provided and explicit constructor (1)
};

struct C : B {
    using B::B; // inherited constructor (1)
    int a;

  private:
    int b; // private non-static data member (2)
};

struct D : protected A { // protected direct base class (4)
    virtual void f();    // virtual member function (5)
};

void test() {

    static_assert(std::is_aggregate_v<A>, "A is an aggregate");

    static_assert(!std::is_aggregate_v<B>,
                  "B is not an aggregate (user-provided and explicit constructor)");

    static_assert(!std::is_aggregate_v<C>,
                  "C is not an aggregate (inherited constructor and "
                  "private non-static data member )");

    static_assert(!std::is_aggregate_v<D>,
                  "D is not an aggregate (protected direct base class)");
}
} // namespace Aggregates

namespace TrivialCopyable {
/*
    A trivial class is a class trivial copyable (supports memcpy)

    1. No user-provided copy/move/default constructor and copy/move assignment operator.
    2. No virtual functions.

    Apply those rules recursively to all non-static data members and base classes.
*/
struct A {
    A() = default;
    A(int) {}
    static int x;
    void f();

  private:
    static int y;
    int z;
    void g();
};

struct B {
    virtual void f(); // virtual function (2)
};

struct C {
    C(const C &) {} // user-provided copy constructor (1)
};

void test() {
    static_assert(std::is_trivially_copyable_v<A>, "A is trivially copyable");

    static_assert(!std::is_trivially_copyable_v<B>,
                  "B is not trivially copyable (virtual function)");

    static_assert(!std::is_trivially_copyable_v<C>,
                  "C is not trivially copyable (user-provided copy constructor)");
}
} // namespace TrivialCopyable

namespace StandardLayout {
/*
    A standard layout class is a class with the same memory layout of the equivalent C
    struct or union.

    1. No virtual functions.
    2. Only one control access specifier for all non-static data members.
    3. No base classes with non-static data members.
    4. No base classes of the same type as the first non-static data member.

    Apply those rules recursively to all non-static data members and base classes.
*/
struct A {
    A() {}
    int a;
    int b;
    void f();

  private:
    static int x;
};

struct B : A { // base class with non-static data members (3)
    int a;
};

struct C {
    C();
    void f();
};

struct D : C {
    C c; // base class of the same type as the first non-static data member (4)
};

struct E : C {
    int a;
    C c; // not the first non-static data member
};

void test() {
    static_assert(std::is_standard_layout_v<A>, "A is standard layout");

    static_assert(!std::is_standard_layout_v<B>,
                  "B is not standard layout (base class with non-static data members)");

    static_assert(std::is_standard_layout_v<C>, "C is standard layout");

    static_assert(!std::is_standard_layout_v<D>,
                  "D is not standard layout (base class of the same type as the first "
                  "non-static data member)");

    static_assert(std::is_standard_layout_v<E>, "E is standard layout");
}
} // namespace StandardLayout

namespace POD {
/*
    POD = Trivial copyable + Standard layout

    * POD is deprecated in C++20
    * Use the narrower concepts instead.
    * Use is_trivially_copyable and is_standard_layout.
*/
}