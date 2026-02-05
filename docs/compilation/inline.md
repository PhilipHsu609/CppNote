---
title: "Inline"
---


Multiple definitions allowed across translation units.

## Inline Functions

```cpp
// In header file
inline int square(int x) {
    return x * x;
}
```

The compiler may:
1. Replace call with function body (inlining)
2. Or keep as regular function call

Key: **definition can appear in multiple TUs** without ODR violation.

## Inline Variables (C++17)

```cpp
// In header file
inline int counter = 0;
inline const int config_value = 42;
inline constexpr int compile_time = 100;
```

All translation units share the same variable.

## constexpr Functions

Implicitly inline:

```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}
// Can be in header, included multiple times
```

## Templates

Template definitions must be visible at instantiation, so they're effectively inline:

```cpp
// In header file
template <typename T>
T add(T a, T b) {
    return a + b;
}

template <typename T>
constexpr T pi = T(3.14159265358979L);
```

## Static Class Members

```cpp
class Config {
public:
    // Declaration only
    static int value;

    // Inline definition (C++17)
    static inline int inline_value = 42;
    static constexpr int const_value = 100; // implicitly inline
};

// In .cpp file (without inline)
int Config::value = 0;
```

## Header-Only Libraries

`inline` enables header-only libraries:

```cpp
// mylib.hpp
inline void helper() { /* ... */ }
inline int global_counter = 0;

class MyClass {
    // Member functions defined in class are implicitly inline
    void method() { /* ... */ }
};
```

## Key Points

- `inline` is about linkage, not performance
- Multiple definitions must be identical
- `constexpr` functions are implicitly inline
- C++17 `inline` variables solve static member initialization
- Templates are effectively inline

## See Also

- [linkage](linkage.md) - internal vs external linkage
- [translation-units](translation-units.md) - compilation units
