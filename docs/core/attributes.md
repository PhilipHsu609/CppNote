---
title: "Attributes"
since: "C++11"
---

# Attributes

Compiler hints and metadata using `[[attribute]]` syntax.

## Standard Attributes

### [[noreturn]]

Function never returns (throws, terminates, or loops forever):

```cpp
[[noreturn]] void fatal_error() {
    throw std::runtime_error("fatal");
}
```

### [[deprecated]] (C++14)

Mark as deprecated with optional message:

```cpp
[[deprecated("use new_function() instead")]]
void old_function() { }
```

### [[nodiscard]] (C++17)

Warn if return value is ignored:

```cpp
[[nodiscard]] int* allocate() {
    return new int;
}

allocate(); // warning: ignoring return value
```

### [[maybe_unused]]

Suppress unused warnings:

```cpp
[[maybe_unused]] void debug_only() { }
[[maybe_unused]] int x = compute();
```

### [[fallthrough]] (C++17)

Indicate intentional fallthrough in switch:

```cpp
switch (x) {
case 1:
    do_something();
    [[fallthrough]];
case 2:
    do_more(); // no warning about fallthrough
    break;
}
```

## Key Points

- Attributes provide hints to compiler and tools
- Standard attributes are portable across compilers
- Compilers may define additional attributes
- Use `[[nodiscard]]` for functions returning allocated memory or error codes
- Use `[[deprecated]]` to guide users away from old APIs

## See Also

- [enums](enums.md) - attributes on enum values
- [namespaces](namespaces.md) - deprecated namespaces
