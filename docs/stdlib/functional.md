---
title: "std::function and Functional"
since: "C++11"
---


Function wrappers, binding, and invocation.

## std::function

Polymorphic function wrapper:

```cpp
#include <functional>

// Store any callable with matching signature
std::function<int(int, int)> f;

f = [](int a, int b) { return a + b; };  // lambda
f = add;                                   // function pointer
f = Functor{};                            // functor

int result = f(2, 3);
```

## std::bind

Bind arguments to a callable:

```cpp
void foo(int a, int b, int c, int d, int e);

// Bind all arguments
auto f1 = std::bind(foo, 1, 2, 3, 4, 5);
f1(); // calls foo(1, 2, 3, 4, 5)

// Bind with placeholders
using namespace std::placeholders;
auto f2 = std::bind(foo, 1, _3, 5, _2, _1);
f2(2, 3, 4); // calls foo(1, 4, 5, 3, 2)
```

## std::invoke

Uniform call syntax for any callable:

```cpp
#include <functional>

int add(int a, int b) { return a + b; }

struct Multiply {
    int operator()(int a, int b) const { return a * b; }
};

std::invoke(add, 1, 2);           // function
std::invoke(Multiply{}, 3, 4);    // functor
std::invoke([](int a, int b) { return a - b; }, 5, 6); // lambda
```

## std::mem_fn

Wrap member function pointer:

```cpp
struct A {
    void method(int n);
};

A a;

// Raw member function pointer
auto ptr = &A::method;
(a.*ptr)(1);

// With mem_fn
auto wrapped = std::mem_fn(&A::method);
wrapped(a, 2);  // cleaner syntax
```

## Key Points

- `std::function` has overhead (type erasure, possible heap)
- Prefer lambdas over `std::bind` (more readable)
- `std::invoke` enables generic callable handling
- Use templates for zero-overhead function parameters

## See Also

- [lambdas](../core/lambdas.md) - lambda expressions
