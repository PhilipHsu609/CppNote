---
title: "Types"
---


C++ type system: fundamental types, compound types, and type conversions.

## Fundamental Types

```cpp
#include <type_traits>

// Arithmetic types: bool, char, int, float, double
static_assert(std::is_arithmetic_v<bool>);
static_assert(std::is_arithmetic_v<char>);
static_assert(std::is_arithmetic_v<int>);
static_assert(std::is_arithmetic_v<float>);
static_assert(std::is_arithmetic_v<double>);

// void and std::nullptr_t
static_assert(std::is_fundamental_v<void>);
static_assert(std::is_fundamental_v<std::nullptr_t>);
```

## Compound Types

```cpp
// Compound types include:
// pointers, references, enumerators, arrays, structures, unions, classes, functions

enum class Color { Red, Green, Blue };
struct Point { int x, y; };
union Data { int i; float f; };

static_assert(std::is_compound_v<int*>);
static_assert(std::is_compound_v<int&>);
static_assert(std::is_compound_v<int[10]>);
static_assert(std::is_compound_v<Color>);
static_assert(std::is_compound_v<Point>);
```

## nullptr

```cpp
void foo(int* ptr);
void foo(std::nullptr_t);

int main() {
    int* p{};
    foo(p);       // calls foo(int*)
    foo(nullptr); // calls foo(std::nullptr_t)
    // foo(0) or foo(NULL) would be ambiguous
}
```

## Type Conversions

### Promotion Rules

Applied top to bottom (first match wins):

```cpp
// 1. Floating point promotion
static_assert(std::is_same_v<decltype(1.0f + 1), float>);

// 2. Integral promotion (small types -> int)
static_assert(std::is_same_v<decltype('a' + 'b'), int>);
std::uint8_t a = 255, b = 255;
auto c = a + b; // = 510, no overflow (promoted to int)

// 3. Size promotion
static_assert(std::is_same_v<decltype(1 + 1ll), long long>);

// 4. Signedness promotion (same size: unsigned wins)
static_assert(std::is_same_v<decltype(1u + 1), unsigned int>);
```

### Cast Operators

```cpp
int a = 5;

// static_cast - compile-time type check
float f = static_cast<float>(a);

// const_cast - add/remove const/volatile
const int b = 10;
int* p = const_cast<int*>(&b);
*p = 20; // undefined behavior!

// reinterpret_cast - bit-level conversion
int c = reinterpret_cast<int&>(f);     // float bits as int
auto addr = reinterpret_cast<std::size_t>(&f); // pointer to integer

// Array reshape
int arr[3][4] = {};
int (&arr2)[2][6] = reinterpret_cast<int(&)[2][6]>(arr);
```

## Size Types

```cpp
#include <cstddef>

static_assert(std::is_same_v<std::size_t, unsigned long>);
static_assert(std::is_signed_v<std::ptrdiff_t>);
```

- `std::size_t` - unsigned type for sizes and counts
- `std::ptrdiff_t` - signed type for pointer differences

## Operator Associativity

```cpp
// Assignment has right-to-left associativity
int b;
int a = b = 1; // b=1, then a=1

// Comma operator has left-to-right associativity
int x = (1, 2, 3);  // x=3 (last value)
int y = (b = 2, 4); // b=2, y=4
```

## C-Style Cast

```cpp
// Old style (avoid)
int a = 5;
float f = (float)a;

// Prefer static_cast
float f2 = static_cast<float>(a);

// Note: static_cast cannot cast pointer to integer
// int v = static_cast<int>(ptr); // error
auto addr = reinterpret_cast<std::size_t>(ptr); // use reinterpret_cast
```

## Key Points

- Fundamental types: arithmetic types + `void` + `std::nullptr_t`
- Compound types: everything built from fundamental types
- Use `nullptr` instead of `NULL` or `0` for null pointers
- Integral promotion prevents overflow for small types
- Prefer `static_cast` over C-style casts
- Assignment is right-to-left, comma is left-to-right

## See Also

- [const](const.md) - const qualifier
- [initialization](initialization.md) - variable initialization
