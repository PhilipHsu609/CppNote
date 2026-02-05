---
title: "SFINAE"
---


Substitution Failure Is Not An Error.

## The Principle

When template argument substitution fails, the specialization is discarded (not an error) and other overloads are tried.

```cpp
template <typename T>
typename T::value_type get(T& container); // #1

template <typename T>
T get(T* ptr); // #2

int x;
get(&x); // #1 fails (int* has no value_type), #2 selected
```

## std::enable_if

Conditionally enable overloads:

```cpp
// Enable only for signed types
template <typename T, std::enable_if_t<std::is_signed_v<T>, int> = 0>
T ceil_div(T value, T div) {
    return (value > 0 && div > 0) ? (value + div - 1) / div : value / div;
}

// Enable only for unsigned types
template <typename T, std::enable_if_t<!std::is_signed_v<T>, int> = 0>
T ceil_div(T value, T div) {
    return (value + div - 1) / div;
}
```

## enable_if as Return Type

```cpp
template <typename T>
std::enable_if_t<std::is_integral_v<T>, T>
process(T value) {
    return value * 2;
}
```

## std::void_t (C++17)

Detects valid expressions:

```cpp
// Primary: false by default
template <typename T, typename = void>
struct has_member_x : std::false_type {};

// Specialization: true if T has .x
template <typename T>
struct has_member_x<T, std::void_t<decltype(std::declval<T>().x)>>
    : std::true_type {};

// Helper variable
template <typename T>
inline constexpr bool has_member_x_v = has_member_x<T>::value;

struct A { int x; };
struct B { };

static_assert(has_member_x_v<A>);
static_assert(!has_member_x_v<B>);
```

## How void_t Works

```cpp
// If decltype(T().x) is valid:
//   void_t<...> = void
//   Specialization matches (more specific)
//
// If invalid:
//   SFINAE discards specialization
//   Primary template selected (false_type)
```

## Key Points

- SFINAE: failed substitution removes overload, doesn't error
- `std::enable_if` conditionally enables templates
- `std::void_t` detects valid types/expressions
- Prefer concepts (C++20) over SFINAE when possible

## See Also

- [type-traits](type-traits.md) - type properties
- [specialization](specialization.md) - template specialization
