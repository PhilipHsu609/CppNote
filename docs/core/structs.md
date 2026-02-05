---
title: "Structures"
---

# Structures

Aggregate types grouping related data.

## Basic Struct

```cpp
struct Foo {
    int a;
    int b;
};

Foo foo{1, 2}; // aggregate initialization
```

## Anonymous Struct

```cpp
// Named variable with unnamed type
struct {
    int c;
    int d;
} Bar;

Bar.c = 1;
```

Note: C++ doesn't allow truly anonymous structs (C11 does).

## Structured Bindings (C++17)

```cpp
Foo get_foo() { return {1, 2}; }

void example() {
    Foo foo{1, 2};
    auto [a, b] = foo;          // copy
    auto& [x, y] = foo;         // reference
    auto [c, d] = get_foo();    // from return value

    int arr[2] = {1, 2};
    auto& [p, q] = arr;         // works with arrays too
}
```

## Struct vs Class

In C++, `struct` and `class` are nearly identical:
- `struct`: members default to `public`
- `class`: members default to `private`

```cpp
struct S { int x; };  // x is public
class C { int x; };   // x is private
```

## Key Points

- Structs are aggregates when they have no user-declared constructors
- Aggregate initialization uses braces
- Structured bindings decompose structs into named variables
- Prefer `struct` for plain data, `class` for types with invariants

## See Also

- [bitfields](bitfields.md) - packed bit-level fields
- [unions](unions.md) - overlapping storage
- [classes](../classes/basics.md) - full class features
