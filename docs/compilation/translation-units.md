---
title: "Translation Units"
---


The unit of compilation in C++.

## What is a Translation Unit?

A source file after preprocessing:
- Original `.cpp` file
- Plus all `#include`d headers (recursively)
- With macros expanded

```
source.cpp + headers = translation unit → object file
```

## Compilation Model

```
source1.cpp  →  [compile]  →  source1.o  ↘
source2.cpp  →  [compile]  →  source2.o  →  [link]  →  executable
source3.cpp  →  [compile]  →  source3.o  ↗
```

Each `.cpp` compiles independently, then linker combines.

## One Definition Rule (ODR)

1. **One definition per TU**: Variables, functions can only be defined once in a TU
2. **One definition per program**: Non-inline functions/variables defined once total
3. **Multiple definitions allowed**: `inline` functions, templates, class definitions (must be identical)

```cpp
// ODR violation: defined twice in program
// file1.cpp
int x = 1;
// file2.cpp
int x = 2;  // ERROR at link time

// OK: inline allows multiple definitions
// header.hpp
inline int y = 1;  // same definition in all TUs
```

## Header Guards

Prevent multiple inclusion within one TU:

```cpp
// myheader.hpp
#ifndef MYHEADER_HPP
#define MYHEADER_HPP

// declarations here

#endif

// Or modern (non-standard but universal)
#pragma once
```

## Include vs Forward Declaration

```cpp
// Forward declaration (faster compile)
class Foo;
void use_foo(Foo* f);

// Full include (required for size/members)
#include "foo.hpp"
Foo create_foo();
```

## Key Points

- Each `.cpp` is its own translation unit
- ODR: one definition rule
- Headers are copy-pasted by preprocessor
- Use header guards or `#pragma once`
- Minimize includes for faster compilation

## See Also

- [linkage](linkage.md) - internal vs external linkage
- [inline](inline.md) - multiple definition exception
