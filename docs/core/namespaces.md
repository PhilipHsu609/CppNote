---
title: "Namespaces"
---

# Namespaces

Organize code and prevent name collisions.

## Nested Namespaces (C++17)

```cpp
// Before C++17
namespace n1 { namespace n2 { namespace n3 {
    struct A {};
}}}

// C++17 and later
namespace n1::n2::n3 {
    struct A {};
}
```

## Namespace Alias

```cpp
namespace n = n1::n2::n3;
n::A obj;
```

## Anonymous Namespace

Everything inside has internal linkage (file-local):

```cpp
namespace {
    int x = 0;  // only visible in this translation unit
}
// Preferred over 'static' for file-local declarations
```

## Inline Namespace

Members appear in parent namespace (useful for versioning):

```cpp
namespace Library {

inline namespace V2 {
    void func() { /* V2 implementation */ }
}

namespace V1 {
    void func() { /* V1 implementation */ }
}

} // namespace Library

Library::func();     // calls V2::func (inline is default)
Library::V1::func(); // explicitly calls V1
Library::V2::func(); // explicitly calls V2
```

## Deprecated Namespace (C++17)

```cpp
namespace [[deprecated]] OldAPI {
    // Using this namespace produces a warning
}
```

## Key Points

- Use namespaces to avoid name collisions
- Nested namespace syntax `a::b::c` requires C++17
- Anonymous namespaces replace `static` for internal linkage
- Inline namespaces enable API versioning
- Can apply attributes to namespaces

## See Also

- [attributes](attributes.md) - [[deprecated]] and other attributes
