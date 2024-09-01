# Modern C++

## C++11

- `auto` keyword
- [Constant Expression](./src/basics/const.cpp)
- [Move Semantic](./src/oop/ctor-dtor.cpp)

## C++14

- [Variable Template](./src/template/variable.cpp)

## C++17

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
- Consteval, Constinit
- Designated Initializers
- Spaceship Operator `<=>` (three-way comparision operator)
- Template
  - float type parameter
  - class literal type parameter
  - alias template deduction
  - concept (better SFINAE)
  - no deduction rules for aggregates
- `std::format`
- `std::span`
- Ranges

## C++23

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
- [Floating point](./src/basics/float.cpp)
  - Machine epsilon
- [enum, enum class](./src/basics/enums.cpp)
