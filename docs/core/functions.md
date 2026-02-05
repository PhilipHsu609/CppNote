---
title: "Functions"
---

# Functions

Function declarations, overloading, and function pointers.

## Function Signature

A function signature includes:
- Number of arguments
- Argument types
- Order of arguments

```cpp
void f(int);
void f(double) = delete; // explicitly delete overload
```

## Deleted Functions

```cpp
void g(int*);
void g(std::nullptr_t) = delete; // prevent nullptr overload
```

## Function Pointers

```cpp
// fp takes two ints and returns int
void use(int (*fp)(int, int));

// Complex declaration (read inside-out):
// fp is a pointer to function taking int,
// returning pointer to array of 10 pointers to int
void complex(int* (*(*fp)(int))[10]);
```

## Functors

A functor is a class with `operator()`:

```cpp
struct Functor {
    void operator()() { /* ... */ }
};

Functor f;
f(); // callable like a function
```

Since C++11, lambdas often replace functors.

## Key Points

- Overloading: same name, different signatures
- Use `= delete` to explicitly forbid overloads
- Read complex pointer declarations inside-out
- Functors are objects that behave like functions

## See Also

- [lambdas](lambdas.md) - lambda expressions
- [functional](../stdlib/functional.md) - std::function
