---
title: "Linkage"
---

# Linkage

How names are visible across translation units.

## Linkage Types

- **No linkage**: Local variables, visible only in their scope
- **Internal linkage**: Visible only within the translation unit
- **External linkage**: Visible across translation units

## Internal Linkage

Only visible within the current translation unit:

```cpp
// Anonymous namespace (preferred)
namespace {
    void internal_func() {}
    int internal_var = 0;
}

// static keyword (older style)
static int static_var = 0;
static int static_func() { return 1; }

// const/constexpr at namespace scope (implicitly internal)
const int const_var = 42;
constexpr int constexpr_var = 43;
```

## External Linkage

Visible from other translation units:

```cpp
// lib.hpp (header)
extern int extern_var;      // declaration
int func();                 // declaration

// lib.cpp (implementation)
int extern_var = 77;        // definition
int func() { return 66; }   // definition
```

## Declarations vs Definitions

```cpp
// Declarations (can appear in headers)
extern int x;           // variable declaration
void func();            // function declaration
class Foo;              // class declaration

// Definitions (one per program)
int x = 10;             // variable definition
void func() { }         // function definition
class Foo { };          // class definition
```

## What Has External Linkage

- Non-static functions
- Non-static global variables
- Classes, structs, enums
- Template instantiations
- Inline variables/functions (C++17)

## What Has Internal Linkage

- `static` functions and variables
- Anonymous namespace members
- `const`/`constexpr` at namespace scope (without `extern`)

## Key Points

- Prefer anonymous namespaces over `static`
- `extern` declares without defining
- Each definition must appear exactly once (ODR)
- Templates are special (see inline)

## See Also

- [inline](inline.md) - inline functions and variables
- [translation-units](translation-units.md) - compilation model
