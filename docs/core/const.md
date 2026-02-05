---
title: "const"
---


The `const` qualifier marks variables as immutable.

## Usage

```cpp
const int x = 5;
const char s[] = "Hello";
```

## Pointers and const

```cpp
int y = 10;

const int* p1 = &y;       // pointer to const int (can't modify *p1)
int* const p2 = &y;       // const pointer to int (can't modify p2)
const int* const p3 = &y; // const pointer to const int
```

## Type Alias Gotcha

```cpp
using ptr_t = int*;
const ptr_t p4 = &y; // This is: int* const (not const int*)
*p4 = 5;             // Allowed! p4 points to non-const int
```

The `const` applies to the alias as a whole, making the pointer const, not what it points to.

## Key Points

- `const` variables must be initialized at declaration
- Read pointer declarations right-to-left
- Type aliases can be surprising with `const`
- `const` member functions can be called on const objects

## See Also

- [constexpr](constexpr.md) - compile-time evaluation
- [volatile](volatile.md) - volatile qualifier
