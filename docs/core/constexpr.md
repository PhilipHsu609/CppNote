---
title: "constexpr"
since: "C++11"
---


Enables compile-time evaluation for variables and functions.

## Usage

```cpp
constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int x = square(5); // evaluated at compile-time
    static_assert(x == 25);
}
```

## constexpr Variables

```cpp
constexpr int x = 5;
constexpr int y = x * 2; // evaluated at compile-time
constexpr int z = square(8);
```

## constexpr Functions

```cpp
constexpr int square(int x) {
    return x * x;
}
```

Evaluated at compile-time when:
- All arguments are constant expressions
- Result is used in a constant context

**Limitations:**
- No runtime features
- No `goto`, `asm`, `assert`
- No `static` variables
- No undefined behavior
- Cannot be `virtual` (until C++20)

## constexpr Classes

```cpp
struct S {
    int x{7};
    constexpr S(int x) : x(x) {}
    constexpr int f() const { return x; }
    static constexpr int g() { return 42; }
};

constexpr S s(10);
constexpr int a = s.f(); // OK: s is constexpr
```

## if constexpr (C++17)

Compile-time conditional:

```cpp
if constexpr (sizeof(int) == 4) {
    return 1;
} else if constexpr (sizeof(int) == 8) {
    return 2;
}
```

The non-taken branch is discarded entirely (useful in templates).

## Key Points

- `constexpr` *can* be evaluated at compile-time (not must)
- All arguments must be constexpr for compile-time evaluation
- C++14 added loops and local variables
- C++17 added `if constexpr`
- C++20 relaxed many restrictions

## See Also

- [const](const.md) - runtime immutability
