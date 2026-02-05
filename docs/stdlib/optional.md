---
title: "std::optional"
since: "C++17"
---


Nullable value wrapper.

## Basic Usage

```cpp
#include <optional>

std::optional<int> opt{42};
std::optional<int> none{std::nullopt};

if (opt.has_value()) {
    int x = *opt;        // dereference
    int y = opt.value(); // with exception if empty
}

// value_or: default if empty
int z = none.value_or(0); // z = 0
```

## Creating Optional

```cpp
std::optional<std::string> a = "hello";     // implicit
std::optional<std::string> b{"hello"};      // direct
auto c = std::make_optional("hello");       // deduced
std::optional<std::string> d = std::nullopt; // empty
std::optional<std::string> e;               // empty
```

## Checking and Accessing

```cpp
std::optional<int> opt = 42;

// Check if has value
if (opt) { }              // contextual bool
if (opt.has_value()) { }  // explicit

// Access value
*opt;                     // UB if empty
opt.value();              // throws if empty
opt.value_or(default);    // safe default
```

## Modifying

```cpp
opt = 100;          // assign new value
opt = std::nullopt; // clear
opt.reset();        // clear
opt.emplace(200);   // construct in-place
```

## Key Points

- Replaces "magic values" (like -1 for not found)
- Safer than raw pointers for optional values
- Zero overhead when value is present
- Use `value_or()` for safe access with defaults
- Great for function return types

## See Also

- [variant](variant.md) - multiple types
- [any](any.md) - any type
