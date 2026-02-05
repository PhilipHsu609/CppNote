---
title: "Template Argument Deduction"
---


How the compiler infers template arguments.

## Basic Deduction

```cpp
template <typename T>
T max(T a, T b);

max(1, 2);       // T = int
max(1.0, 2.0);   // T = double
// max(1, 2.0);  // ERROR: T ambiguous

const int a = 1, b = 2;
max(a, b);       // T = int (const stripped)

int arr[3];
int* p;
max(&arr[0], p); // T = int*
```

## Return Type Deduction

```cpp
// Explicit return type parameter
template <typename RT, typename T1, typename T2>
RT f1(T1 a, T2 b) { return a + b; }
f1<double>(1, 2); // RT = double

// Auto return (C++14)
template <typename T1, typename T2>
auto f2(T1 a, T2 b) { return a + b; }

// Trailing return type (C++11)
template <typename T1, typename T2>
auto f3(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// std::common_type
template <typename T1, typename T2>
std::common_type_t<T1, T2> f4(T1 a, T2 b) {
    return a + b;
}
```

## Arrays and C-Strings

```cpp
template <typename T>
void foo(const T& t);  // reference: preserves array type

template <typename T>
void bar(T t);         // value: array decays to pointer

int arr[3];
foo(arr);     // T = int[3]
bar(arr);     // T = int* (decay!)

foo("hello"); // T = char[6]
bar("hello"); // T = const char* (decay!)
```

## Preserving Array Size

```cpp
template <typename T, std::size_t N>
void process(const T (&arr)[N]);

int arr[5];
process(arr);    // T = int, N = 5
process("hi");   // T = char, N = 3
```

## Class Template Argument Deduction (CTAD, C++17)

```cpp
std::pair p(1, 3.14);        // pair<int, double>
std::vector v{1, 2, 3};      // vector<int>
std::array a{1, 2, 3};       // array<int, 3>
```

## Deduction Guides

```cpp
template <typename T>
struct Container {
    Container(T) {}
};

// Deduction guide: const char* -> std::string
Container(const char*) -> Container<std::string>;

Container c("hello"); // Container<std::string>
```

## Key Points

- Deduction strips top-level const/reference
- Arrays decay to pointers when passed by value
- Use references to preserve array types
- `decltype` and `auto` help with return types
- CTAD eliminates explicit template arguments for classes
- Deduction guides customize CTAD behavior

## See Also

- [basics](basics.md) - template fundamentals
- [type-traits](type-traits.md) - type manipulation
