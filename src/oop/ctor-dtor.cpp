namespace Default_constructors {
/*
    A default constructor is a constructor that can be called without any arguments.

    Every class has always either
        explicit, implicit, or deleted default constructor.
*/
struct A {
    A() = default; // explicit default constructor
    // same behavior as A() {}
};

struct B {
    // B has an implicit default constructor
    int a = 0;
};

struct C {
    C() = delete; // deleted default constructor
};

struct D {
    // The implicit default constructor is deleted if
    D(int a) {}  // it has any user-defined constructor
    int &x;      // it has any reference member
    const int y; // it has any const member
    C c;         // it has any class member with deleted default constructor
};

int test() {
    A a;   // call the default constructor
    A b(); // declare a function named b that returns A
    A c{}; // call the default constructor (list initialization)
}
} // namespace Default_constructors

namespace Delegate_constructors {
struct A {
    int a;
    int b;
    float c;

    A() : A(1, 2, 3.14f) {} // delegate constructor
    A(int a, int b, float c) : a{a}, b{b}, c{c} {}
};
} // namespace Delegate_constructors

namespace Copy_constructors {
/*
    Copy constructor creates a **DEEP COPY** of the object.

    The implicit copy constructor is deleted if
        - has a non-static referece/const member
        - has a non-static member of a class with deleted copy constructor
        - has the move constructor
*/
struct A {
    A() = default;  // copy constructor is a user-defined constructor
                    //     (the implicit default constructor is deleted)
    A(const A &){}; // copy constructor
};

void f(A a) {}
A g1() { return A(); }
A g2(A &a) { return a; }

void test() {
    A a;
    A b{a};  // copy constructor (list initialization)
    A c = a; // copy constructor (assignment)
    g2(a);   // copy constructor (return value)
    f(a);    // copy constructor (argument)

    b = c;      // copy assignment
    A d = g1(); // see RVO optimization
}
} // namespace Copy_constructors

namespace Move_constructors {
class A {
  public:
    A();                      // default constructor
    A(const A &a);            // copy constructor
    A(A &&rhs);               // move constructor
    A &operator=(const A &a); // copy assignment
    A &operator=(A &&rhs);    // move assignment
    ~A();
};
} // namespace Move_constructors

namespace Member_initialization {
struct A {
    int a;
    int b;
    float c = 3.14f;    // in-class member initializer
    int *ptr = nullptr; // in-class member initializer

    // Const and reference members must be initialized by
    //     - member initialization list
    //     - in-class member initializer
    int &ref = a;
    const int x;

    // Member initialization list (NOT std::initializer_list)
    A() : a{1}, b{2}, x{0} {}
};

struct B {
    int *array;
    int size;

    // Class member initialize follows **the order of declaration**
    B() : size{10}, array{new int[size]} {} //! WRONG
};
} // namespace Member_initialization

namespace Explicit {
/*
    Explicit keyword specifies that a constructor or conversion operator
    does not allow implicit conversions or copy-initialization.
*/
struct A {
    A() {}
    A(int) {}
    A(int, int) {}
};
struct B {
    explicit B() {}
    explicit B(int) {}
    explicit B(int, int) {}
};

void f(const A &) {}
void g(const B &) {}

void test_no_explicit() {
    A a1 = {}; // implicit
    A a2(2);
    A a3 = 1; // implicit
    A a4{1, 2};
    A a5 = {3, 4}; // implicit

    // All implicit
    f({});
    f(1);
    f({1});
    f({1, 2});
}

void test_explicit() {
    // B b1 = {}; // implicit
    B b2(2);
    // B b3 = 1; // implicit
    B b4{1, 2};
    // B b5 = {3, 4}; // implicit

    // All implicit
    // g({});
    // g(1);
    // g({1});
    // g({1, 2});

    g(B{1});
    g(B{1, 2});
}
} // namespace Explicit

namespace Class_keywords {
/*
    this
    Use this when
    - the name of a local variable is equal to some member name
    - return reference to the calling object
*/
struct A {
    int x;
    void f(int x) { this->x = x; }
    const A &g() { return *this; }
};
/*
    static declares members that are not bound to class instances.
*/
struct B {
    // static member function
    //  - can only access static members
    static int f() { return 0; }

    // static constant members
    static const int x = 1;
    static constexpr int y = 2;
    static constexpr float z = 1.2f;
    static constexpr int g() { return 1; }

    // static mutable members (cannot be initialized in class declaration)
    static int a;            // declaration
    static inline int b = 1; // ok
};
int B::a = 1; // definition
/*
    const member functions (inspectors or observers)
        - not allowed to change the object logical state
*/
struct C {
    int x = 3;
    int *p;

    // const member function
    // - all members are marked with const, including this pointer
    int get() const {
        // x = 4; // error
        // p = nullptr; // error
        p[0] = 1; // ok
        return x;
    }

    // non-const member function (mutators or modifiers)
    int get() { return x; }
};
/*
    mutable data members can be modified
        - in const class instance
        - in const member function

    mutable is useful for caching or lazy evaluation.
        - caching the result of a computation in a const instance or const member function
*/
struct D {
    mutable int cache = -1;
    int get() const {
        if (cache == -1) {
            // do some expensive computation and cache the result
            cache = 1;
        }
        return cache;
    }
};
/*
    using keyword
    - aliasing a type
    - change the inheritance access level
*/
struct E : C {
    using value_type = int;

  private:
    using C::x; // change the access level from public to private
};
typename E::value_type e = 1; // typename is required for dependent names
E::value_type f = 2;          // without typename, E::value_type is static member
} // namespace Class_keywords