---
title: "Operator Overloading"
---

# Operator Overloading

Custom operators for user-defined types.

## Conversion Operators

```cpp
struct A {
    explicit operator int() const { return 1; }  // explicit conversion
    operator double() const { return 2.0; }       // implicit conversion
};

A a;
int x = static_cast<int>(a); // OK: explicit
double y = a;                 // OK: implicit
// int z = a;                 // ERROR: int conversion is explicit
```

## Increment/Decrement

```cpp
struct A {
    int x = 0;

    A& operator++() {      // prefix: ++a
        x++;
        return *this;       // return new value by reference
    }

    A operator++(int) {    // postfix: a++
        A tmp = *this;
        ++*this;            // use prefix
        return tmp;         // return old value by value
    }
};
```

## Copy-Swap Idiom

Exception-safe assignment:

```cpp
struct A {
    int x;

    friend void swap(A& a, A& b) {
        using std::swap;
        swap(a.x, b.x);
    }

    A& operator=(A other) {  // pass by value (copy)
        swap(*this, other);   // swap with copy
        return *this;         // old data destroyed with 'other'
    }
};
```

## Stream Operators

```cpp
struct A {
    int x;

    friend std::ostream& operator<<(std::ostream& os, const A& a) {
        os << a.x;
        return os;
    }
};
```

## Binary Operators

Implement as friend for symmetry:

```cpp
struct B {
    int x;

    // B == B works
    // But without friend: B == A works, A == B doesn't
    friend bool operator==(const B& lhs, const B& rhs) {
        return lhs.x == rhs.x;
    }
};
```

## Key Points

- Use `explicit` for conversion operators that might cause surprises
- Prefix returns reference, postfix returns copy
- Copy-swap idiom provides exception safety
- Binary operators should be friends or free functions
- C++20 adds `<=>` (spaceship) for comparison operators

## See Also

- [copy-move](copy-move.md) - copy and move assignment
- [virtual](virtual.md) - polymorphic operators
