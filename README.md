# Modern C++

A comprehensive study note for Modern C++ programming language, covering language features, standard library, design patterns, and best practices.

## Table of Contents

- [C++ Version Features](#c-version-features)
  - [C++11](#c11)
  - [C++14](#c14)
  - [C++17](#c17)
  - [C++20](#c20)
  - [C++23](#c23)
- [Language Fundamentals](#language-fundamentals)
  - [Basics](#basics)
  - [OOP](#oop)
  - [Template (Meta Programming)](#template-meta-programming)
  - [Translation Units](#translation-units)
- [Standard Library](#standard-library)
  - [Containers and Utilities](#containers-and-utilities)
  - [Functional Programming](#functional-programming)
  - [Concurrency](#concurrency)
  - [Utilities](#utilities)
- [Design Patterns](#design-patterns)
  - [SOLID Principles](#solid-principles)
  - [Creational Patterns](#creational-patterns)
  - [Structural Patterns](#structural-patterns)

---

## C++ Version Features

### C++11

- `auto` keyword
- [Constant Expression](./src/basics/const-vol.cpp)
- [Move Semantic](./src/oop/ctor-dtor.cpp)

### C++14

- [Variable Template](./src/template/variable.cpp)
- [Generic Lambda](./src/basics/func.cpp)

### C++17

- Initializing statement
  - `if(int y = x + 1 > 10)`
  - `switch(auto i = f(); x)`
- [if constexpr](./src/basics/const-vol.cpp)
- [Structured Bindings](./src/basics/struct-bitfield-union.cpp)
- [Constexpr Lambda](./src/basics/func.cpp)
- [Feature Testing Macro](./src/basics/preproc.cpp)
- Template
  - `auto` placeholder
- [String View](./src/std/string.cpp)
- [Variant](./src/std/variant.cpp)
- [Optional](./src/std/optional-any.cpp)
- [Any](./src/std/optional-any.cpp)
- [File System](./src/std/fs.cpp)

### C++20

- `auto` as function parameter type
- Initializing statement
  - `for(int i = 0; auto x : container)`
- Consteval, Constinit
  - `std::is_constant_evaluated()`
- Designated Initializer list
  - `struct A {int x, y, z;}; A a{.x=1, .y=2, .z=3};`
- `std::bit_cast` (type punning)
- Spaceship Operator `<=>` (three-way comparision operator)
- `#include <source_location>`
- Template
  - Lambda with `requires`
  - float type parameter
  - class literal type parameter
  - alias template deduction
  - concept (better SFINAE)
  - no deduction rules for aggregates
- Modules
- `std::format`, `std::span`
- Ranges

### C++23

- `if consteval`
- Multidimensional subscript operator
  - `int operator[](int x, int y)`
- `static int operator()`, `static int operator[]`
- `std::print`, `std::println`

---

## Language Fundamentals

### Basics

- [Types](./src/basics/types.cpp)
  - Fundamental types
    - `void`
    - Arithmetic types
    - `nullptr_t`
  - Compound types
    - Reference
    - Function
    - `enum`, `enum class`
    - Pointer, Pointer to member
    - Array, Class, Struct, Union
  - Assignment, Compound and Comma operator
  - `std::size_t`, `std::ptrdiff_t`
  - Type cast
    - `static_cast`, `reinterpret_cast`
- [Floating point](./src/basics/float.cpp)
  - Machine epsilon
- [enum, enum class](./src/basics/enums.cpp)
- [Struct, Bitfield and Union](./src/basics/struct-bitfield-union.cpp)
  - Struct
    - Named struct, unnamed struct
  - Bitfield
  - Union
- [Attributes](./src/basics/attributes.cpp)
  - `deprecated`, `noreturn`, `nodiscard`, `maybe_unused`, `fallthough`
- [Memory and Initialization](./src/basics/memory-init.cpp)
  - Memory
    - Dynamic memory allocation
      - `std::bad_alloc`
      - `std::nothrow`
  - Initialization
    - Zero initialization
    - Default initialization
    - Direct initialization
    - Value initialization
    - List initialization
- [CV-qualifier](./src/basics/const-vol.cpp)
  - Constants
  - Constant expressions
  - Volatile
- [Functions and Lambdas](./src/basics/func.cpp)
  - Functions
    - Function pointers
    - Function overloading
  - Lambdas
- [Preprocessor](./src/basics/preproc.cpp)
  - Macro
  - Conditional compiling
  - Feature testing macro
  - Stringizing macro
  - `#pragma`
  - Token-pasting macro

### OOP

- [Class](./src/oop/class.cpp)
  - Hierarchy
  - Virtual classes
  - Class member overloading with different qualifiers
- [Constructor and destructor](./src/oop/ctor-dtor.cpp)
  - Default , copy, move contrustors
  - Delegate contructors
  - Destructors
  - Member initialization order
  - `explicit`, `static`, `const`, `mutable` keyword
- [RAII](./src/oop/RAII.cpp)
- [Polymorphism](./src/oop/poly.cpp)
  - Virtual methods
  - Virtual table
  - `override`, `final` keywords
  - Static polymorphism
- [Casting and RTTI](./src/oop/cast-RTTI.cpp)
  - RTTI
    - `dynamic_cast`, `typeid`, `type_info`
- [Operator overloading](./src/oop/oo.cpp)
- [Object layout](./src/oop/object-layout.cpp)
  - Aggregate
  - Trivial copyable
  - Standard layout
  - Plain-old data
    - Equivalent to trivial copyable and standard layout
    - Deprecated in C++20

### Template (Meta programming)

- [Function template](./src/template/func.cpp)
  - Template argument deduction
- [Template variables](./src/template/variable.cpp)
- [Compile-time utilities](./src/template/utility.cpp)
  - `static_assert`, `using`, `decltype`, `type_traits`
- [Class template](./src/template/class.cpp)
  - Partial and full specilization
  - CTAD
- [Meta programming](./src/template/meta.cpp)
- [SFINAE](./src/template/SFINAE.cpp)
- [Variadic template](./src/template/variadic.cpp)

### Translation Units

- [Linkage](./src/linkage)
  - Internal and external
- Storage duration
  - Automatic, static, dynamic and thread storage
- One definition rule
- `inline` functions and variables
- [Namespace](./src/basics/namespace.cpp)

## Standard Library

### Containers and Utilities
- [Array](./src/std/array.cpp)
  - Multi-dimensional arrays
- [String](./src/std/string.cpp)
  - String view
  - String conversions
  - `from_chars`, `to_chars`
- [Optional](./src/std/optional-any.cpp)
  - Optional values
  - `std::nullopt`
- [Any](./src/std/optional-any.cpp)
  - Type-safe container for any type
- [Variant](./src/std/variant.cpp)
  - Type-safe union
  - `std::visit`

### Functional Programming
- [Functional](./src/std/functional.cpp)
  - `std::function`
  - `std::bind`
  - `std::invoke`

### Concurrency
- [Thread](./src/std/thread.cpp)
  - Thread creation and management
  - `std::mutex`, `std::shared_mutex`
  - `std::condition_variable`
  - `std::call_once`, `std::once_flag`
  - `std::atomic`
- [Async](./src/std/async.cpp)
  - `std::async`
  - `std::future`, `std::promise`
  - `std::packaged_task`
- [Memory Order](./src/std/memory-order.cpp)
  - Memory ordering for atomics
  - Acquire-release semantics

### Utilities
- [File System](./src/std/fs.cpp)
  - Path operations
  - Directory iteration
  - File operations
- [Time](./src/std/time.cpp)
  - `std::chrono`
  - Time operations
- [Random](./src/std/rand.cpp)
  - Random number generation
  - Distributions
- [Math](./src/std/math.cpp)
  - Mathematical functions
  - Numeric limits
- [I/O](./src/std/io.cpp)
  - Stream operations
  - File I/O
  - Formatting

## Design Patterns

### SOLID Principles
- [SOLID](./src/design/SOLID.cpp)
  - Single Responsibility Principle
  - Open/Closed Principle
  - Liskov Substitution Principle
  - Interface Segregation Principle
  - Dependency Inversion Principle

### Creational Patterns
- [Factory](./src/design/creational/factory.cpp)
  - Factory method
  - Abstract factory
- [Builder](./src/design/creational/builder.cpp)
  - Step-by-step object construction
- [Singleton](./src/design/creational/singleton.cpp)
  - Thread-safe singleton
- [Prototype](./src/design/creational/prototype.cpp)
  - Cloning objects
- [Multiton](./src/design/creational/multiton.cpp)
  - Multiple named instances

### Structural Patterns
- [Adapter](./src/design/structural/adapter.cpp)
  - Interface adaptation
- [Pimpl](./src/design/structural/pimpl.cpp)
  - Pointer to implementation idiom
