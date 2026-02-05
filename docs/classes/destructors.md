---
title: "Destructors"
---


Object cleanup when lifetime ends.

## Basic Destructor

```cpp
class Resource {
    int* data;
public:
    Resource() : data(new int[100]) {}
    ~Resource() {
        delete[] data; // cleanup
    }
};
```

## Virtual Destructor

**Required** when deleting derived objects through base pointer:

```cpp
struct Base {
    virtual ~Base() { /* cleanup Base */ }
};

struct Derived : Base {
    ~Derived() { /* cleanup Derived */ }
};

Base* ptr = new Derived;
delete ptr; // Calls ~Derived() then ~Base()
```

Without `virtual`, only `~Base()` runs (undefined behavior).

## Destruction Order

```cpp
struct A { ~A() { std::cout << "A"; } };
struct B : A { ~B() { std::cout << "B"; } };
struct C : B { ~C() { std::cout << "C"; } };

C c;
// Output when c goes out of scope: "CBA"
// Destruction is reverse of construction
```

## When Destructors Run

- Local variables: when scope exits
- Heap objects: when `delete` is called
- Class members: after containing class destructor body
- Global/static: at program termination

## Key Points

- Always make destructor `virtual` if class has virtual functions
- Destructor should never throw exceptions
- Runs in reverse order of construction
- Called automatically when object goes out of scope

## See Also

- [constructors](constructors.md) - object creation
- [raii](raii.md) - resource management pattern
