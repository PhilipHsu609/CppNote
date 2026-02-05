---
title: "Bit Fields"
---


Variables with predefined bit widths within a struct.

## Basic Usage

```cpp
struct Foo {
    unsigned int b1 : 10; // 10 bits [0, 1023]
    unsigned int b2 : 10; // 10 bits [0, 1023]
    unsigned int b3 : 8;  // 8 bits  [0, 255]
}; // sizeof(Foo) == 4 bytes (packed into 28 bits)
```

## Padding and Alignment

```cpp
struct Bar {
    unsigned int b1 : 10; // 10 bits
    unsigned int : 0;     // force alignment to next unit
    unsigned int b2 : 10; // 10 bits (starts new unit)
    unsigned int : 6;     // skip 6 bits
    unsigned int b3 : 10; // 10 bits
}; // sizeof(Bar) == 8 bytes
```

## Mixed Types

```cpp
struct Baz {
    unsigned char b1 : 3;
    unsigned char : 2;    // 2-bit padding
    unsigned char b2 : 6;
    unsigned char b3 : 2;
}; // sizeof(Baz) == 2 bytes
```

## Key Points

- Bit width cannot exceed underlying type size
- Anonymous bit fields create padding
- `: 0` forces alignment to next storage unit
- Actual layout is implementation-defined
- Cannot take address of bit field members
- Useful for hardware registers, protocols, memory optimization

## See Also

- [structs](structs.md) - basic structures
- [unions](unions.md) - overlapping storage
