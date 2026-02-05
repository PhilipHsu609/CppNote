---
title: "Numeric Utilities"
---

# Numeric Utilities

Math functions and numeric limits.

## Math Functions

```cpp
#include <cmath>

auto x = std::exp2(3); // 2^3 = 8
auto y = std::log2(8); // log2(8) = 3
```

## Numeric Limits

```cpp
#include <limits>

template <typename T>
T get_max() {
    return std::numeric_limits<T>::max();
}

template <typename T>
T get_min() {
    return std::numeric_limits<T>::min();
}

template <typename T>
T get_lowest() {
    // For floating point: most negative value (e.g., -infinity)
    return std::numeric_limits<T>::lowest();
}

template <typename T>
T get_epsilon() {
    // The machine epsilon
    return std::numeric_limits<T>::epsilon();
}
```

## Machine Epsilon

The difference between 1 and the next larger floating point number:

```cpp
// Interval machine epsilon (not relative machine epsilon)
// - interval machine epsilon = 2 * relative machine epsilon
// - interval machine epsilon = ulp of 1.0

// float: approx 1.19e-7
std::numeric_limits<float>::epsilon();   // 0.00000011920928955078125

// double: approx 2.22e-16
std::numeric_limits<double>::epsilon();  // 0.00000000000000022204460492503131
```

## Lowest vs Min

```cpp
// For integers: min() == lowest()
// For floats: min() is smallest positive, lowest() is most negative

std::numeric_limits<float>::min();     // ~1.17e-38 (smallest positive)
std::numeric_limits<float>::lowest();  // ~-3.40e+38 (most negative)
```

## Key Points

- `max()` - largest finite value
- `min()` - smallest positive value (floats) or most negative (integers)
- `lowest()` - most negative finite value
- `epsilon()` - machine precision for floating point
- Use `<cmath>` for math functions, `<limits>` for numeric limits

## See Also

- [types](../core/types.md) - fundamental types
