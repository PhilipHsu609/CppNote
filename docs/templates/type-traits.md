---
title: "Type Traits"
since: "C++11"
---


Compile-time type introspection and manipulation.

## Type Properties

```cpp
#include <type_traits>

// Check properties
static_assert(std::is_integral_v<int>);
static_assert(std::is_floating_point_v<double>);
static_assert(std::is_pointer_v<int*>);
static_assert(std::is_reference_v<int&>);
static_assert(std::is_const_v<const int>);
static_assert(std::is_class_v<std::string>);
static_assert(std::is_same_v<int, int>);
```

## Type Relationships

```cpp
static_assert(std::is_base_of_v<Base, Derived>);
static_assert(std::is_convertible_v<Derived*, Base*>);
```

## Type Manipulation

```cpp
// Add qualifiers
std::add_const_t<int>              // const int
std::add_pointer_t<int>            // int*
std::add_lvalue_reference_t<int>   // int&

// Remove qualifiers
std::remove_const_t<const int>     // int
std::remove_pointer_t<int*>        // int
std::remove_reference_t<int&>      // int

// Sign manipulation
std::make_signed_t<unsigned int>   // int
std::make_unsigned_t<int>          // unsigned int
```

## std::decay

Removes reference, const, and array-to-pointer decay:

```cpp
std::decay_t<int&>           // int
std::decay_t<const int&>     // int
std::decay_t<int[3]>         // int*
std::decay_t<int(int)>       // int(*)(int)
```

## Using in Templates

```cpp
template <typename T>
void process(T t) {
    if constexpr (std::is_integral_v<T>) {
        // integer handling
    } else if constexpr (std::is_floating_point_v<T>) {
        // float handling
    }
}

template <typename T>
T add(T a, T b) {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic");
    return a + b;
}
```

## Const Reference Gotcha

```cpp
// Reference to const, not const reference
// (references themselves can't be const)
static_assert(std::is_same_v<
    std::remove_const_t<const int&>,
    const int&  // const NOT removed!
>);

// Remove reference first, then const
static_assert(std::is_same_v<
    std::remove_const_t<std::remove_reference_t<const int&>>,
    int
>);

// Or use decay
static_assert(std::is_same_v<std::decay_t<const int&>, int>);
```

## decltype

Captures expression type:

```cpp
void f(int, int);

decltype(f)           // void(int, int)
decltype(f(1, 2))     // void

int x;
decltype(x)           // int
decltype((x))         // int& (parentheses -> lvalue ref)
```

## std::addressof

Gets address even with overloaded `operator&`:

```cpp
struct Evil {
    Evil* operator&() { return nullptr; }
};

Evil e;
Evil* p1 = &e;              // nullptr (overloaded!)
Evil* p2 = std::addressof(e); // actual address
```

## Key Points

- `_v` suffix: value (bool/int)
- `_t` suffix: type
- `std::decay` for "natural" type transformations
- Remove reference before const for compound types
- Use `if constexpr` with type traits for compile-time branching

## See Also

- [sfinae](sfinae.md) - conditional template instantiation
