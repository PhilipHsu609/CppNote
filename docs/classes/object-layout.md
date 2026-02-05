---
title: "Object Layout"
---

# Object Layout

How objects are stored in memory.

## Aggregate

Supports aggregate initialization `{}`:

```cpp
struct Aggregate {
    int a;
    int b[3];
    int c{2};  // default member initializer OK

    Aggregate() = default;  // OK: not user-provided
    void f();               // OK: member functions allowed
private:
    void g();               // OK: private functions allowed
};

Aggregate x{1, {2,3,4}, 5};
static_assert(std::is_aggregate_v<Aggregate>);
```

**NOT aggregate if:**
- User-provided constructor
- Private/protected non-static data members
- Virtual base classes or functions
- Private/protected base classes

## Trivially Copyable

Can be copied with `memcpy`:

```cpp
struct Trivial {
    Trivial() = default;
    Trivial(int) {}  // non-default ctor OK
    void f();
private:
    int x;  // private data OK
};

static_assert(std::is_trivially_copyable_v<Trivial>);

// Safe to memcpy
Trivial a, b;
std::memcpy(&b, &a, sizeof(Trivial));
```

**NOT trivially copyable if:**
- User-provided copy/move constructor or assignment
- Virtual functions

## Standard Layout

Compatible with C structs:

```cpp
struct Standard {
    Standard() {}  // user-provided OK
    int a;
    int b;
    void f();
private:
    static int x;  // private static OK
};

static_assert(std::is_standard_layout_v<Standard>);
```

**NOT standard layout if:**
- Virtual functions
- Multiple access specifiers for non-static data
- Base class with non-static data members
- First member same type as base class

## POD (Plain Old Data)

**Deprecated in C++20.** Was: trivially copyable + standard layout.

```cpp
// Use these instead:
static_assert(std::is_trivially_copyable_v<T>);
static_assert(std::is_standard_layout_v<T>);
```

## Summary Table

| Property | Allows |
|----------|--------|
| Aggregate | `{}` initialization |
| Trivially Copyable | `memcpy` safe |
| Standard Layout | C-compatible layout |

## Key Points

- Aggregate: brace initialization
- Trivially copyable: safe bitwise copy
- Standard layout: predictable memory layout
- Check with type traits at compile time
- POD is deprecated; use narrower concepts

## See Also

- [constructors](constructors.md) - how constructors affect layout
- [virtual](virtual.md) - vtables affect layout
