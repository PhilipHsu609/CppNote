---
title: "Pimpl Idiom"
---

# Pimpl (Pointer to Implementation)

Hide implementation details to reduce compile dependencies.

## The Problem

```cpp
// widget.hpp - changes here recompile all users
class Widget {
    ComplexType member1;  // must include ComplexType.hpp
    AnotherType member2;  // must include AnotherType.hpp
public:
    void draw();
};
```

Every file including `widget.hpp` depends on `ComplexType.hpp` and `AnotherType.hpp`.

## The Solution

```cpp
// widget.hpp - minimal dependencies
class Widget {
    class Impl;                    // forward declaration
    std::unique_ptr<Impl> pImpl;   // pointer to implementation

public:
    Widget();
    ~Widget();
    void draw();
};
```

```cpp
// widget.cpp - implementation hidden here
#include "widget.hpp"
#include "ComplexType.hpp"
#include "AnotherType.hpp"

class Widget::Impl {
    ComplexType member1;
    AnotherType member2;
public:
    void draw() { /* ... */ }
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() = default;  // must be in .cpp for unique_ptr
void Widget::draw() { pImpl->draw(); }
```

## Template Pimpl

```cpp
template <typename Impl>
class Widget {
    std::unique_ptr<Impl> pImpl;
public:
    Widget() : pImpl(std::make_unique<Impl>()) {}
    ~Widget() = default;
    void draw() { pImpl->draw(); }
};

class DefaultImpl {
public:
    void draw() { std::cout << "Default\n"; }
};

class FancyImpl {
public:
    void draw() { std::cout << "Fancy\n"; }
};

Widget<DefaultImpl> w1;
Widget<FancyImpl> w2;
```

## Benefits

1. **Reduced compile time**: Changes to Impl don't recompile users
2. **Binary compatibility**: Can change Impl without breaking ABI
3. **Hidden implementation**: Users can't access private details
4. **Cleaner headers**: No need to include implementation headers

## Costs

- Extra indirection (pointer dereference)
- Extra allocation (heap for Impl)
- Must define destructor in .cpp

## Key Points

- Forward declare Impl class in header
- Define Impl in .cpp file
- Destructor must be in .cpp (for unique_ptr)
- Common in library interfaces
- Trade-off: compile time vs runtime performance

## See Also

- [adapter](adapter.md) - interface conversion
- [linkage](../../compilation/linkage.md) - translation units
