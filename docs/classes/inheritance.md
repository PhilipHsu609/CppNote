---
title: "Inheritance"
---


Class hierarchies and derived types.

## Basic Inheritance

```cpp
struct Base { int x; };
struct Derived : Base { int y; };

Derived d;
d.x = 1;  // inherited from Base
d.y = 2;  // own member
```

## Implicit Conversions

Derived can be used where Base is expected:

```cpp
void f(Base& b);
void g(Base* b);
void h(Base b);   // slicing!

Derived d;
f(d);   // OK: reference to Base
g(&d);  // OK: pointer to Base
h(d);   // OK but slices: only Base part copied

Base& ref = d;  // OK
Base* ptr = &d; // OK
```

## Object Slicing

```cpp
struct Base { virtual void f() { std::cout << "Base"; } };
struct Derived : Base { void f() override { std::cout << "Derived"; } };

Derived d;
Base b = d;  // SLICED: only Base part copied
b.f();       // "Base" (not "Derived")
```

Always use pointers or references for polymorphism.

## Upcasting and Downcasting

```cpp
struct A { virtual void f() {} };
struct B : A {};
struct C : A {};

B b;

// Upcasting (safe, implicit)
A& a1 = b;
A* a2 = &b;

// Downcasting (unsafe, explicit)
B& b1 = static_cast<B&>(a1);     // unchecked
B& b2 = dynamic_cast<B&>(a1);    // checked, throws if wrong
B* b3 = dynamic_cast<B*>(a2);    // checked, nullptr if wrong

// Sidecasting (between siblings)
// C* c = static_cast<C*>(&b);   // ERROR
C* c = dynamic_cast<C*>(&b);     // nullptr (b is not C)
```

## RTTI (Run-Time Type Information)

```cpp
struct A { virtual void f() {} };
struct B : A {};

A a;
B b;
A& ref = b;

typeid(a).name();    // "A" (mangled)
typeid(b).name();    // "B"
typeid(ref).name();  // "B" (dynamic type!)

if (typeid(ref) == typeid(B)) {
    // ref's dynamic type is B
}
```

## Key Points

- Derived-to-base conversion is implicit and safe
- Base-to-derived (downcasting) requires explicit cast
- `dynamic_cast` performs runtime checking
- `static_cast` is unchecked (faster but dangerous)
- Always use references/pointers for polymorphism
- Object slicing loses derived data

## See Also

- [virtual](virtual.md) - virtual functions
- [basics](basics.md) - access specifiers
