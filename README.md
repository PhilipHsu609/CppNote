# Modern C++

## C++11

- `auto` keyword
- [Constant Expression](./src/basics/const.cpp)
- [Move Semantic](./src/oop/ctor-dtor.cpp)

## C++14

- [Variable Template](./src/template/variable.cpp)
- [Generic Lambda](./src/basics/func.cpp)

## C++17

- Initializing statement
  - `if(int y = x + 1 > 10)`
  - `switch(auto i = f(); x)`
- [if constexpr](./src/basics/const-vol.cpp)
- [Structured Bindings](./src/basics/struct-bitfield-union.cpp)
- [Constexpr Lambda](./src/basics/func.cpp)
- [Feature Testing Macro](./src/basics/preproc.cpp)
- [String View](./src/std/string.cpp)
- [Variant](./src/std/variant.cpp)
- [Optional](./src/std/optional-any.cpp)
- [Any](./src/std/optional-any.cpp)
- [File System](./src/std/fs.cpp)

## C++20

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
- `std::format`
- `std::span`
- Ranges

## C++23

- `if consteval`
- `std::print`, `std::println`

## Basics

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

## OOP

- [Class](./src/oop/class.cpp)
  - Hierarchy
  - Virtual classes
  - Class member overloading with different qualifiers
