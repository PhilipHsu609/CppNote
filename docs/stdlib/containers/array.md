---
title: "std::array"
since: "C++11"
---

# std::array

Fixed-size array with STL interface.

## Basic Usage

```cpp
#include <array>

std::array<int, 5> arr = {1, 2, 3, 4, 5};

arr[0] = 10;           // no bounds checking
arr.at(0) = 10;        // with bounds checking

arr.front();           // first element
arr.back();            // last element
arr.data();            // raw pointer

arr.size();            // 5
arr.empty();           // false
arr.fill(0);           // set all to 0
```

## 2D Matrix

```cpp
template <typename T, size_t Row, size_t Col>
using Matrix = std::array<std::array<T, Col>, Row>;

Matrix<int, 2, 3> mat = {{{1, 2, 3}, {4, 5, 6}}};
mat[0][1] = 10;
```

## N-Dimensional Array

```cpp
template <typename T, size_t Dim, size_t... Dims>
struct MultiDimArray {
    using type = std::array<typename MultiDimArray<T, Dims...>::type, Dim>;
};

template <typename T, size_t Dim>
struct MultiDimArray<T, Dim> {
    using type = std::array<T, Dim>;
};

template <typename T, size_t... Dims>
using Array = typename MultiDimArray<T, Dims...>::type;

Array<int, 2, 3, 4> arr3d; // int[2][3][4]
```

## Key Points

- Size known at compile time (part of the type)
- No heap allocation
- Compatible with STL algorithms
- Prefer over C-style arrays
- Use `std::vector` for dynamic sizes

## See Also

- [string](string.md) - dynamic string
