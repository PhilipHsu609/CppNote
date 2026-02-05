---
title: "Template Specialization"
---


Custom implementations for specific types.

## Full Specialization

All template parameters specified:

```cpp
template <typename T>
bool equal(T a, T b) {
    return a == b;
}

// Full specialization for float
template <>
bool equal<float>(float a, float b) {
    return std::abs(a - b) < 1e-6f;
}
```

## Partial Specialization (Classes Only)

Some template parameters specified:

```cpp
template <typename T, typename U>
struct Pair {
    T first;
    U second;
};

// Partial: when U is int
template <typename T>
struct Pair<T, int> {
    T first;
    int second;
    // Completely different implementation allowed
};

// Full: both specified
template <>
struct Pair<float, double> {
    float x;
    double y;
};
```

**Note:** Functions cannot be partially specialized (use overloading instead).

## Implementing Type Traits

```cpp
// Primary template
template <typename T, typename U>
struct is_same : std::false_type {};

// Partial specialization: when T == U
template <typename T>
struct is_same<T, T> : std::true_type {};

static_assert(is_same<int, int>::value);
static_assert(!is_same<int, float>::value);
```

## Another Example: Pointer Detection

```cpp
template <typename T>
struct is_const_ptr : std::false_type {};

template <typename T>
struct is_const_ptr<const T*> : std::true_type {};

static_assert(is_const_ptr<const int*>::value);
static_assert(!is_const_ptr<int*>::value);
```

## Key Points

- Full specialization: all parameters specified
- Partial specialization: some parameters specialized
- Specialized classes are completely new types
- Functions use overloading instead of partial specialization
- Type traits leverage partial specialization patterns

## See Also

- [basics](basics.md) - template basics
- [type-traits](type-traits.md) - standard type traits
- [sfinae](sfinae.md) - conditional instantiation
