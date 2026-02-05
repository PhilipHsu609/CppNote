---
title: "Enumerations"
---

# Enumerations

Type-safe enumerated constants.

## Traditional enum (Unscoped)

```cpp
enum Color { RED, GREEN, BLUE };
enum Fruit { APPLE, BANANA, CHERRY };

Color c = RED;
Fruit f = APPLE;

// Problem: implicitly converts to int, allows comparison
if (c == f) { } // Compiles! RED == APPLE (both are 0)
int x = GREEN + CHERRY; // Compiles! 1 + 2 = 3
```

## enum class (Scoped, C++11)

```cpp
enum class Animal { dog, deer, cat, bird, human };
enum class Mammal { kangaroo, deer, human };

Animal a = Animal::dog;
// Animal b = dog;        // Error: must use scope
// if (a == Mammal::deer) // Error: different types
```

## Features

```cpp
// Automatic values starting from 0
static_assert(static_cast<int>(Animal::bird) == 3);

// Comparison within same enum
static_assert(Animal::dog < Animal::deer);

// Explicit underlying type and values
enum class Foo : uint8_t {
    A = 1,
    B = 4,
    C [[deprecated]] = 255, // with attributes
    D = 0,
    E = 1  // aliasing allowed (E == A)
};

static_assert(std::is_same_v<std::underlying_type_t<Foo>, uint8_t>);
static_assert(Foo::A == Foo::E);
```

## Key Points

- Prefer `enum class` over plain `enum`
- Scoped enums require explicit conversion to integers
- Can specify underlying type (default is `int`)
- Supports attributes like `[[deprecated]]`
- Values can alias (multiple names for same value)

## See Also

- [types](types.md) - type system overview
- [attributes](attributes.md) - C++ attributes
