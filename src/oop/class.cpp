namespace Hierarchy {
struct Base {};
struct Derived : Base {};
struct MoreDerived : Derived {};

void f(Base a) {}
void g(Derived b) {}

void f_ref(Base &a) {}    // same for Base *a
void g_ref(Derived &b) {} // same for Derived *b

void test() {
    Base a;
    f(a);
    // g(a);      // error
    f_ref(a);
    // g_ref(a);  // error

    Derived b; // Derived class can be used as Base class
    f(b);
    g(b);
    f_ref(b);
    g_ref(b);

    Base c = b;
    Base &d = b;

    // Derived e = a;   // error
    // Derived &f = a;  // error
}

void order() {
    MoreDerived a;
    // The construction order of a is
    //     Base -> Derived -> MoreDerived

    // The destruction order of a is
    //     MoreDerived -> Derived -> Base
}
} // namespace Hierarchy

namespace Specifiers {
class Base {
  public:
    int a;

  protected:
    int b;

  private:
    int c;
};

class Public_Derived : public Base {
    /*
        a is public.
        b is protected.
        c is not accessible.
    */
};

class Protected_Derived : protected Base {
    /*
        a is protected.
        b is protected.
        c is not accessible.
    */
};

class Private_Derived : private Base {
    /*
        a is private.
        b is private.
        c is not accessible.
    */
};
} // namespace Specifiers

namespace VirtualClasses {
struct A {
    void f() {}
};
struct B : virtual A {};
struct C : virtual A {};
struct D : B, C {};
/*
    Inheritance hierarchy of D:

        A
       / \
      B   C    "Dreaded Diamond"
       \ /
        D

    An instance of D will be made up of B and C, which both have an A subobject.
    So when calling D::f(), which A::f() is called?

    This is when virtual inheritance comes into play.
        B: virtual A
        C: virtual A  will tell the compiler to share the A subobject between B and C.
*/
void test() {
    D d;
    d.f();
}
} // namespace VirtualClasses

namespace ClassMemberOverloading {
/*
    Besides overloading with different parameters,
    you can also overload with different **qualifiers**.
    - ref-qualifiers
    - cv-qualifiers

    There are 8 combinations
*/
struct A {
    void f() & {}
    void f() && {}
    void f() const & {}
    void f() const && {}
    void f() volatile & {}
    void f() volatile && {}
    void f() const volatile & {}
    void f() const volatile && {}
};
} // namespace ClassMemberOverloading