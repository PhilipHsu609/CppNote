---
title: "Template Basics"
---


Generic programming with function, class, and variable templates.

## Function Templates

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}

add(1, 2);     // T = int (deduced)
add(1.0, 2.0); // T = double (deduced)
add<float>(1, 2); // T = float (explicit)
```

## Template Parameters

```cpp
// 1. Types
template <typename T> void f();

// 2. Integral values
template <int N> int square() { return N * N; }

// 3. auto (C++17)
template <auto V> auto get() { return V; }

// 4. Enums
enum class Dir { LEFT, RIGHT };
template <Dir dir = Dir::RIGHT>
void move();

// 5. Mixed
template <int A, typename T>
T ceil_div(T b) { return (A + b - 1) / b; }
```

## Class Templates

```cpp
template <typename T, typename U>
struct Pair {
    T first;
    U second;
};

Pair<int, double> p{1, 3.14};
```

## Variable Templates (C++14)

```cpp
template <typename T>
constexpr T pi = T(3.14159265358979L);

float area = pi<float> * r * r;
double area = pi<double> * r * r;
```

## Template Instantiation

```cpp
// Implicit: generated when used
add(1, 2);

// Explicit: force generation
template int add<int>(int, int);

// Explicit specialization
template <>
std::string add<std::string>(std::string a, std::string b) {
    return a + b;
}
```

## Key Points

- Templates are compile-time code generation
- Type deduction infers template arguments
- Explicit instantiation useful for libraries
- Specialization provides custom implementations
- C++17 added CTAD for classes

## See Also

- [deduction](deduction.md) - argument deduction rules
- [specialization](specialization.md) - partial and full specialization
