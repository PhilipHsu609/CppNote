---
title: "Class Basics"
---


Fundamental class concepts in C++.

## Member Functions

Every member function has an implicit `this` parameter:

```cpp
class A {
public:
    void foo(int x) {} // Actually: void foo(A* this, int x)
};

A a;
a.foo(1); // Equivalent to A::foo(&a, 1)
```

### this Keyword

```cpp
struct A {
    int x;
    void f(int x) { this->x = x; }  // disambiguate member from parameter
    const A& g() { return *this; }  // return reference to self
};
```

### const Member Functions

```cpp
struct C {
    int x = 3;
    int* p;

    // const member function - cannot modify logical state
    int get() const {
        // x = 4;       // error: can't modify member
        // p = nullptr; // error: can't modify pointer
        p[0] = 1;       // ok: modifying what p points to
        return x;
    }

    // non-const overload
    int get() { return x; }
};
```

### mutable Keyword

Allows modification in const context (useful for caching):

```cpp
struct D {
    mutable int cache = -1;

    int compute() const {
        if (cache == -1) {
            // expensive computation
            cache = 42;  // ok: mutable
        }
        return cache;
    }
};
```

### static Members

```cpp
struct B {
    // static member function - can only access static members
    static int f() { return 0; }

    // static constants - can initialize in class
    static const int x = 1;
    static constexpr int y = 2;
    static constexpr float z = 1.2f;

    // static mutable - must define outside class (or use inline)
    static int a;            // declaration
    static inline int b = 1; // C++17: inline allows initialization
};
int B::a = 1; // definition outside class
```

### using to Change Access

```cpp
struct E : C {
    using value_type = int;  // type alias

  private:
    using C::x;  // change x from public to private
};
```

## Access Specifiers

```cpp
class Base {
public:
    int a;    // accessible everywhere
protected:
    int b;    // accessible in class and derived classes
private:
    int c;    // accessible only in this class
};
```

## Inheritance Access

```cpp
class PublicDerived : public Base {
    // a is public, b is protected, c is inaccessible
};

class ProtectedDerived : protected Base {
    // a is protected, b is protected, c is inaccessible
};

class PrivateDerived : private Base {
    // a is private, b is private, c is inaccessible
};
```

## Construction/Destruction Order

```cpp
struct Base {};
struct Derived : Base {};
struct MoreDerived : Derived {};

MoreDerived obj;
// Construction: Base -> Derived -> MoreDerived
// Destruction:  MoreDerived -> Derived -> Base
```

## Virtual Inheritance (Diamond Problem)

```cpp
struct A { void f() {} };
struct B : virtual A {};  // share A
struct C : virtual A {};  // share A
struct D : B, C {};       // only one A subobject

//     A
//    / \
//   B   C   (Diamond)
//    \ /
//     D

D d;
d.f(); // Unambiguous: only one A::f()
```

## Member Function Overloading

Can overload on qualifiers (8 combinations):

```cpp
struct A {
    void f() & {}              // lvalue
    void f() && {}             // rvalue
    void f() const & {}        // const lvalue
    void f() const && {}       // const rvalue
    void f() volatile & {}     // volatile lvalue
    void f() volatile && {}    // volatile rvalue
    void f() const volatile & {}
    void f() const volatile && {}
};
```

## Key Points

- `this` is an implicit pointer to the current object
- Use `public` inheritance for is-a relationships
- Virtual inheritance solves the diamond problem
- Construction is base-first, destruction is derived-first

## See Also

- [constructors](constructors.md) - constructor types
- [inheritance](inheritance.md) - inheritance details
- [virtual](virtual.md) - virtual functions
