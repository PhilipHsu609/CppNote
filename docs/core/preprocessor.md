---
title: "Preprocessor"
---


Directives processed before compilation.

## Macros

```cpp
#define VAL 10
#undef VAL

#define STR(s) #s   // stringizing: STR(hello) -> "hello"
#define CONCAT(a, b) a##b  // token pasting: CONCAT(foo, bar) -> foobar
```

## Conditional Compilation

```cpp
#if defined(DEBUG)
    // debug code
#elif !defined(RELEASE)
    // neither debug nor release
#else
    // release code
#endif

// Shorthand
#ifdef DEBUG
#ifndef RELEASE
```

## Feature Testing (C++17)

```cpp
#if __has_include(<optional>)
#include <optional>
#endif
```

## Predefined Macros

### Source Location

```cpp
__FILE__            // current filename
__LINE__            // current line number
__func__            // current function name (C99/C++11)
__FUNCTION__        // same as __func__ (common extension)
__PRETTY_FUNCTION__ // decorated function name (GCC/Clang)
```

### Language Version

```cpp
#if __cplusplus == 199711L
    // C++98
#elif __cplusplus == 201103L
    // C++11
#elif __cplusplus == 201402L
    // C++14
#elif __cplusplus == 201703L
    // C++17
#elif __cplusplus == 202002L
    // C++20
#endif
```

### Compiler Detection

```cpp
#ifdef __GNUG__     // GCC/G++
#ifdef __clang__    // Clang
#ifdef _MSC_VER     // MSVC
```

### Platform Detection

```cpp
#ifdef __linux__    // Linux
#ifdef _WIN32       // Windows (32 and 64-bit)
#ifdef _WIN64       // Windows 64-bit only
#ifdef __APPLE__    // macOS/iOS
#ifdef __unix__     // Unix-like
```

## Pragma

```cpp
#pragma once        // include guard (non-standard but universal)
#pragma message("Building module X")
```

## Code Generation

```cpp
#define FUNC_GEN(type) \
    void to_##type() { /* ... */ }

FUNC_GEN(int)   // generates: void to_int() { ... }
FUNC_GEN(float) // generates: void to_float() { ... }
```

## Key Points

- Preprocessor runs before compilation
- `#` stringizes, `##` concatenates tokens
- Use `#pragma once` or include guards
- Prefer `constexpr` and templates over macros when possible
- `__cplusplus` tells you the C++ standard version

## See Also

- [constexpr](constexpr.md) - compile-time evaluation (prefer over macros)
