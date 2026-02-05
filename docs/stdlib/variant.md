---
title: "std::variant"
since: "C++17"
---


Type-safe union.

## Basic Usage

```cpp
#include <variant>

std::variant<int, float, bool> v = 3.3f;

// Access by type
float f = std::get<float>(v);

// Access by index
float f2 = std::get<1>(v);  // index 1 = float

// Check current type
int idx = v.index();  // 1 (float)

// Modify
std::get<bool>(v) = true;
v.index();  // now 2 (bool)
```

## Safe Access

```cpp
// get throws std::bad_variant_access if wrong type
try {
    int x = std::get<int>(v);  // throws if not int
} catch (std::bad_variant_access&) { }

// get_if returns pointer (nullptr if wrong type)
if (auto* p = std::get_if<int>(&v)) {
    // *p is the int value
}

// holds_alternative
if (std::holds_alternative<int>(v)) {
    // v contains int
}
```

## std::visit

Apply a visitor to the current value:

```cpp
std::variant<int, float, bool> v = 3.3f;

std::visit([](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>) {
        // handle int
    } else if constexpr (std::is_same_v<T, float>) {
        // handle float
    } else if constexpr (std::is_same_v<T, bool>) {
        // handle bool
    }
}, v);
```

## Key Points

- Type-safe alternative to union
- Stores exactly one of the types at a time
- `index()` returns which type is active
- `std::visit` for type-safe access
- Prefer over raw unions

## See Also

- [optional](optional.md) - nullable value
- [any](any.md) - any type (type-erased)
