---
title: "Lambda Expressions"
since: "C++11"
---


Anonymous function objects.

## Syntax

```cpp
auto lambda = [capture](parameters) { body };
```

## Basic Usage

```cpp
auto add = [](int a, int b) { return a + b; };
int result = add(2, 3); // 5
```

## Generic Lambdas (C++14)

```cpp
auto g = [](auto x, auto y) { return x + y; };
g(1, 2);     // int
g(1.5, 2.5); // double
```

## Default Parameters (C++14)

```cpp
auto h = [](int x = 0) { return x; };
h();  // 0
h(5); // 5
```

## constexpr Lambdas (C++17)

```cpp
auto factorial = [](int n) constexpr {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
};

constexpr int f10 = factorial(10); // compile-time
```

## Capture Modes

```cpp
int x = 10;

[x]  { return x; }     // by value (const copy)
[&x] { return x; }     // by reference
[=]  { return x; }     // all by value
[&]  { return x; }     // all by reference
[=, &x] { }            // all by value, x by reference
[&, x]  { }            // all by reference, x by value
```

## Mutable Lambdas

By default, captured values are const. Use `mutable` to modify:

```cpp
int x = 0;
auto f = [x]() mutable {
    x = 1;      // OK: mutable allows modification
    return x;
};
f(); // returns 1
// x is still 0 (captured by value)
```

## Key Points

- Lambdas are syntactic sugar for anonymous functor classes
- Capture by value creates const copies by default
- Use `mutable` to modify value-captured variables
- Generic lambdas use `auto` parameters
- C++20 adds template lambdas: `[]<typename T>(T x) { }`

## See Also

- [functions](functions.md) - regular functions
- [functional](../stdlib/functional.md) - std::function wrapper
