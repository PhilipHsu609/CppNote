#pragma once

#include <fmt/core.h>
#include <fmt/format.h>

/*
    If internal linkage variables/functions are defined in a header file, they will be
    defined in each translation unit that includes the header file.

    Unless you want to have multiple copies of the same variable/function in different
    translation units, you should avoid defining internal linkage variables/functions in
    header files.
*/

// enum has external linkage
enum class Color { RED, GREEN, BLUE };

// class has external linkage
class Foo {
  public:
    Foo();
    void foo();
};

// external linkage function declaration
// defined in another translation unit
//  (for other translation units that include this header)
int func();

// external linkage variable declaration
// defined in another translation unit
//  (for other translation units that include this header)
extern int extern_var;

// template function declaration
template <typename T>
T add(T a, T b);

// template struct declaration
template <typename T, typename U>
struct Pair {
    T first{};
    U second{};
    void foo();
};

// template class declaration
template <typename T>
class TempClass {
  public:
    TempClass(T t);

  private:
    T t;
};

// include the implementation file
#include "lib-inl.hpp"