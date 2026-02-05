---
title: "Unions"
---

# Unions

Overlapping storage where all members share the same memory location.

## Basic Usage

```cpp
union Data {
    int i;
    float f;
};

Data d;
d.i = 42;       // write as int
d.f = 3.14f;    // overwrites, now contains float
// d.i is now garbage (reading inactive member is UB)
```

## Size

Union size equals its largest member:

```cpp
union Example {
    char c;      // 1 byte
    int i;       // 4 bytes
    double d;    // 8 bytes
}; // sizeof(Example) == 8
```

## Type Punning (Caution!)

```cpp
union Bits {
    float f;
    uint32_t i;
};

Bits b;
b.f = 1.0f;
// Reading b.i is technically UB in C++
// (though often works in practice)
```

For safe type punning, use `std::bit_cast` (C++20) or `memcpy`.

## Key Points

- All members share the same memory address
- Only one member is "active" at a time
- Reading inactive member is undefined behavior
- Size equals largest member (plus padding)
- Prefer `std::variant` (C++17) for type-safe unions

## See Also

- [structs](structs.md) - non-overlapping storage
- [variant](../stdlib/variant.md) - type-safe discriminated union
