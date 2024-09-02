/*
    Polymorphism is the capability of an object of mutating its behavior in accordance
    with the specific usage context.

    Polymorphism vs Overloading:
    - Overloading is a form of static polymorphism (compile-time polymorphism)
    - Polymorphism is a form of dynamic polymorphism (run-time polymorphism)

    Function binding:
    - Static binding (early binding): The function call is resolved at compile time
    - Dynamic binding (late binding): The function call is resolved at run time
        - C++ achieves dynamic binding through virtual functions
*/
#include <fmt/core.h>
#include <fmt/format.h>

#include <cassert>
#include <cstdint>

namespace Virtual {
struct Base {
    virtual void print() const { fmt::println("Base::print"); }

    // Default parameters are not inherited in virtual functions.
    virtual void f1(int i = 8) { fmt::println("Base::f1(int i = {})", i); }
    virtual void f2() { fmt::println("Base::f2"); }

    // All classes with at least one virtual function should have a virtual destructor.
    virtual ~Base() { fmt::println("Base destructor"); }
};
struct Derived final : Base {
    // Override keyword ensures that the function is virtual and overrides a base class
    // function. (override implies virtual, and virtual should be omitted)
    void print() const override { fmt::println("Derived::print"); }

    // Final keyword prevents a virtual function from being overridden in derived classes.
    // (this is the end, no more overriding)
    void f1(int i = 7) override final { fmt::println("Derived::f1(int i = {})", i); }

    // Without this virtual destructor, the base class destructor may be called.
    virtual ~Derived() { fmt::println("Derived destructor"); }
};

void f(Base &b) { b.print(); }
void g(Base *b) { b->print(); }
void h(Base b) { b.print(); }

void test() {
    Base b;
    f(b);  // Base
    g(&b); // Base
    h(b);  // Base

    Derived d;
    f(d);  // Derived
    g(&d); // Derived
    h(d);  // Base

    Base &b2 = d;
    d.f1(); // Derived::f1(int i = 7)

    b2.f1(); // Derived::f1(int i = 8) ?!
    // Base's vtable contains the function signature of Base::f1(int i = 8) including the
    // default, but it points to Derived implementations.
}

void print_vtable(std::uint64_t **vptr) {
    fmt::print("vptr: {}\n", fmt::ptr(vptr));
    fmt::print("vtable: {}\n", fmt::ptr(*vptr));

    fmt::print("vtable[0]: {:#x}\n", *(*vptr));
    fmt::print("vtable[1]: {:#x}\n", *(*vptr + 1));
    fmt::print("vtable[2]: {:#x}\n", *(*vptr + 2));
}

void vtable() {
    /*
        Virtual table (vtable) is a lookup table of functions used to resolve function
        calls and support dynamic dispatch.

        Each class has a pointer vptr that points to the vtable of the class.
            vptr usually resides at the beginning of the object.
            vtable is an array of pointers point to virtual functions.

           Base             vtable
        +--------+        +--------+
        |  vptr  | ---->  |  print |
        +--------+        +--------+
        |  data  |        |  f1    |
        +--------+        +--------+
                          |  f2    |
                          +--------+
    */
    Base b;
    std::uint64_t **vptr = reinterpret_cast<std::uint64_t **>(&b);
    print_vtable(vptr);

    auto print = reinterpret_cast<void (*)()>(**vptr);
    print(); // Base::print

    auto f1 = reinterpret_cast<void (*)(int)>(*(*vptr + 1));
    f1(123); // Base::f1

    auto f2 = reinterpret_cast<void (*)()>(*(*vptr + 2));
    f2(); // Base::f2

    Derived d;
    vptr = reinterpret_cast<std::uint64_t **>(&d);
    print_vtable(vptr);

    print = reinterpret_cast<void (*)()>(**vptr);
    print(); // Derived::print

    f1 = reinterpret_cast<void (*)(int)>(*(*vptr + 1));
    f1(456); // Derived::f1

    f2 = reinterpret_cast<void (*)()>(*(*vptr + 2));
    f2(); // Base::f2
}
} // namespace Virtual

namespace Pure_virtual {
/*
    A class is interface if it has only pure virtual functions and optionally a virtual
   destructor.
*/
struct Interface {
    virtual void f() = 0; // Pure virtual function
    virtual ~Interface();
};
/*
    A class is abstract if it has at least one pure virtual function.
*/
struct Abstract {
    Abstract(); // maybe have a constructor
    int data;   // additional data
    virtual void f() = 0;
};
} // namespace Pure_virtual

int main() {
    Virtual::vtable();
    return 0;
}

namespace StaticPolymorphism {
/*
    Static polymorphism is achieved through templates and inheritance.
    - A use case of **Curiously recurring template pattern**
    - Templates: Compile-time polymorphism
    - Inheritance: Run-time polymorphism
*/
template <typename T>
struct Base {
    void f() { static_cast<T *>(this)->f(); }
};

struct Derived : Base<Derived> {
    void f() { fmt::println("Derived::f"); }
};

void test() {
    Base<Derived> *b = new Derived;
    b->f();
    delete b;
}
} // namespace StaticPolymorphism