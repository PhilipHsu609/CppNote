---
title: "Variadic Templates"
since: "C++11"
---

# Variadic Templates

Templates with variable number of arguments.

## Syntax

```cpp
template <typename... TArgs>  // template parameter pack
void f(TArgs... args) {       // function parameter pack
    auto n = sizeof...(args); // number of arguments
}

f(1, 2.0, "hello"); // TArgs = <int, double, const char*>
```

## Recursive Expansion

```cpp
// Base case
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Recursive case
template <typename T, typename... TArgs>
T add(T first, TArgs... rest) {
    return first + add(rest...);
}

add(1, 2, 3, 4); // 1 + add(2, 3, 4) -> ... -> 10
```

## Pack Expansion

```cpp
template <typename T>
T square(T x) { return x * x; }

template <typename... TArgs>
auto sum_of_squares(TArgs... args) {
    return add(square(args)...); // applies square to each
}

sum_of_squares(1, 2, 3); // square(1) + square(2) + square(3)
```

## Fold Expressions (C++17)

More elegant than recursion:

```cpp
// Unary right fold: (E1 op (E2 op (... op EN)))
template <typename... T>
auto sum_right(T... args) {
    return (args + ...);
}

// Unary left fold: (((E1 op E2) op ...) op EN)
template <typename... T>
auto sum_left(T... args) {
    return (... + args);
}

// Binary fold with init
template <typename... T>
auto sum_init(T... args) {
    return (0 + ... + args); // handles empty pack
}
```

## Stream Output with Fold

```cpp
template <typename... T>
void print(T... args) {
    (std::cout << ... << args) << '\n';
}

print(1, " + ", 2, " = ", 3); // "1 + 2 = 3"
```

## Lambda with Variadic (C++14)

```cpp
auto print_all = [](auto... args) {
    (std::cout << ... << args);
};
```

## Key Points

- `...` after type: parameter pack
- `args...`: pack expansion
- `sizeof...(args)`: number of arguments
- Fold expressions (C++17) simplify recursion
- Left vs right fold matters for non-associative operators

## See Also

- [basics](basics.md) - template fundamentals
- [metaprogramming](metaprogramming.md) - compile-time computation
