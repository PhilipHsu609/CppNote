---
title: "std::any"
since: "C++17"
---


Type-erased container for any single value.

## Basic Usage

```cpp
#include <any>
#include <string>

std::any a = 42;
a = std::string{"Hello"};
a = 3.14;
```

## Accessing Values

```cpp
std::any a = std::string{"Hello"};

// Check type
if (a.type() == typeid(std::string)) {
    std::string s = std::any_cast<std::string>(a);
}

// any_cast throws std::bad_any_cast if wrong type
try {
    int x = std::any_cast<int>(a);
} catch (std::bad_any_cast&) { }

// Pointer version returns nullptr if wrong type
if (auto* p = std::any_cast<std::string>(&a)) {
    // *p is the string
}
```

## Checking State

```cpp
std::any a = 42;

a.has_value();  // true
a.type();       // typeid(int)

a.reset();      // clear
a.has_value();  // false
```

## Key Points

- Holds any copyable type
- Uses type erasure (heap allocation for large types)
- Runtime type checking via `type()` and `any_cast`
- Less efficient than `variant` (no compile-time type info)
- Use when types are truly unknown at compile time

## Comparison

| Feature | `optional` | `variant` | `any` |
|---------|------------|-----------|-------|
| Types | 1 or none | fixed set | any |
| Type safety | compile-time | compile-time | runtime |
| Overhead | minimal | minimal | heap possible |

## See Also

- [optional](optional.md) - nullable single type
- [variant](variant.md) - known set of types
