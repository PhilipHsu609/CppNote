---
title: "Template Metaprogramming"
---

# Template Metaprogramming

Compile-time computation using templates.

## Classic Example: Factorial

```cpp
// Template metaprogramming approach
template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

static_assert(Factorial<5>::value == 120);
```

## Modern Alternative: constexpr

```cpp
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

static_assert(factorial(5) == 120);
```

## Log2 at Compile Time

```cpp
template <int N>
struct Log2 {
    static_assert(N > 0);
    static constexpr int value = 1 + Log2<N / 2>::value;
};

template <>
struct Log2<1> {
    static constexpr int value = 0;
};

static_assert(Log2<8>::value == 3);
static_assert(Log2<1024>::value == 10);
```

## Compile-Time Max

```cpp
template <int A, int B>
struct Max {
    static constexpr int value = (A > B) ? A : B;
};

static_assert(Max<3, 7>::value == 7);
```

## Practical Uses

Metaprogramming enables:

1. **Compile-time validation**
   ```cpp
   template <int N>
   struct Buffer {
       static_assert(N > 0 && N <= 1024);
       char data[N];
   };
   ```

2. **Type computation**
   ```cpp
   template <typename T>
   using Ptr = T*;

   template <typename T, int N>
   struct ArrayType {
       using type = T[N];
   };
   ```

3. **Conditional types**
   ```cpp
   template <bool B, typename T, typename F>
   struct conditional { using type = T; };

   template <typename T, typename F>
   struct conditional<false, T, F> { using type = F; };
   ```

## Key Points

- Templates can compute at compile time
- Base case via specialization
- Prefer `constexpr` functions for simple computations
- Template metaprogramming for type manipulation
- Modern C++ (constexpr, if constexpr) often simpler

## See Also

- [type-traits](type-traits.md) - standard metafunctions
- [variadic](variadic.md) - compile-time recursion patterns
