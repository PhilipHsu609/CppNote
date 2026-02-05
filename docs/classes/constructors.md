---
title: "Constructors"
---

# Constructors

Object initialization and construction.

## Default Constructor

Can be called without arguments:

```cpp
struct A {
    A() = default; // explicit default (same as A() {})
};

struct B {
    int a = 0; // has implicit default constructor
};

struct C {
    C() = delete; // deleted default constructor
};

struct D {
    D(int a) {}   // user-defined: implicit default is deleted
    int& x;       // reference member: default deleted
    const int y;  // const member: default deleted
    C c;          // member with deleted default: default deleted
};
```

**Usage:**
```cpp
A a;   // calls default constructor
A b(); // WARNING: declares a function!
A c{}; // calls default constructor (preferred)
```

## Delegating Constructor

```cpp
struct A {
    int a, b;
    float c;

    A() : A(1, 2, 3.14f) {} // delegates to other constructor
    A(int a, int b, float c) : a{a}, b{b}, c{c} {}
};
```

## Copy Constructor

Creates a deep copy:

```cpp
struct A {
    A() = default;
    A(const A&) {} // copy constructor
};

void f(A a) {}
A g(A& a) { return a; }

A a;
A b{a};    // copy constructor
A c = a;   // copy constructor
f(a);      // copy constructor (pass by value)
g(a);      // copy constructor (return)
```

**Implicitly deleted when:**
- Has non-static reference/const member
- Has member with deleted copy constructor
- Has move constructor

## Move Constructor

```cpp
class A {
public:
    A();                       // default
    A(const A& a);             // copy constructor
    A(A&& rhs);                // move constructor
    A& operator=(const A& a);  // copy assignment
    A& operator=(A&& rhs);     // move assignment
    ~A();                      // destructor
};
```

## Member Initialization

```cpp
struct A {
    int a;
    int b;
    float c = 3.14f;     // in-class initializer
    int* ptr = nullptr;  // in-class initializer
    int& ref = a;        // reference: must initialize
    const int x;         // const: must initialize

    // Member initialization list
    A() : a{1}, b{2}, x{0} {}
};
```

**Order matters:**
```cpp
struct B {
    int* array;
    int size;

    // BUG: array uses size, but size is declared after array!
    B() : size{10}, array{new int[size]} {} // WRONG
};
```
Members initialize in **declaration order**, not list order.

## explicit Keyword

Prevents implicit conversions:

```cpp
struct A {
    A(int) {}
};
struct B {
    explicit B(int) {}
};

void f(const A&);
void g(const B&);

f(1);      // OK: implicit A(1)
// g(1);   // ERROR: B(int) is explicit
g(B{1});   // OK: explicit construction
```

## Key Points

- `= default` for compiler-generated implementation
- `= delete` to forbid a constructor
- Initialization list order follows declaration order
- Use `explicit` to prevent implicit conversions
- Rule of 5: if you define one special member, consider all five

## See Also

- [destructors](destructors.md) - cleanup
- [copy-move](copy-move.md) - copy and move semantics
