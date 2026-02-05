---
title: "Virtual Functions"
---


Runtime polymorphism through dynamic dispatch.

## Basic Virtual Functions

```cpp
struct Base {
    virtual void print() const {
        std::cout << "Base\n";
    }
    virtual ~Base() = default;
};

struct Derived : Base {
    void print() const override {
        std::cout << "Derived\n";
    }
};

void call(Base& b) { b.print(); }

Base b;
Derived d;
call(b);  // "Base"
call(d);  // "Derived" (dynamic dispatch)
```

## override and final

```cpp
struct Base {
    virtual void f1(int i = 8) {}
    virtual void f2() {}
};

struct Derived final : Base {  // final: cannot be inherited
    void f1(int i = 7) override final {}  // override + final
    // override: ensures it's actually overriding
    // final: prevents further overriding
};
```

## Default Arguments Warning

```cpp
Base& b = derived;
b.f1();  // Calls Derived::f1 with Base's default (8)!
```

Default arguments come from the **static type**, not dynamic type.

## Virtual Table (vtable)

```cpp
/*
     Object             vtable
   +--------+        +--------+
   |  vptr  | -----> |  print |  -> Base::print or Derived::print
   +--------+        +--------+
   |  data  |        |  f1    |
   +--------+        +--------+
                     |  f2    |
                     +--------+
*/
```

Each class with virtual functions has a vtable. Objects have a hidden `vptr` pointing to their class's vtable.

## Pure Virtual (Abstract Classes)

```cpp
// Interface: only pure virtuals
struct Interface {
    virtual void f() = 0;
    virtual ~Interface() = default;
};

// Abstract: at least one pure virtual
struct Abstract {
    int data;
    virtual void f() = 0;
};

// Cannot instantiate Interface or Abstract
// Interface i;  // ERROR
// Abstract a;   // ERROR
```

## CRTP (Static Polymorphism)

Curiously Recurring Template Pattern - compile-time polymorphism:

```cpp
template <typename T>
struct Base {
    void interface() {
        static_cast<T*>(this)->implementation();
    }
};

struct Derived : Base<Derived> {
    void implementation() { /* ... */ }
};
```

No vtable overhead, but no runtime polymorphism.

## Key Points

- `virtual` enables runtime polymorphism
- Always use `override` when overriding
- Use `final` to prevent further inheritance/overriding
- Default arguments bind at compile time (use static type)
- Virtual destructor required for polymorphic base classes
- CRTP provides compile-time polymorphism

## See Also

- [inheritance](inheritance.md) - class hierarchies
- [object-layout](object-layout.md) - memory layout with vtables
- [raii](raii.md) - combining with RAII
