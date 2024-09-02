#pragma once

// inline const/constexpr has external linkage (since C++17)
//   - same as extern const/constexpr
inline const int inline_var = 32;
inline constexpr int inline_constexpr_var = 43;

// inline variable definition
inline int test = 1;

// inline function has external linkage
inline void test_inline() { test = 777; }

// constexpr function
//   - implicitly inline function
constexpr int square(int x) { return x * x; }

// non-inline constants
//   - implicitly internal linkage
//   - no need static keyword
const int non_static_const = 1;
constexpr int non_static_constexpr = 2;

// template variable has external linkage
template <typename T>
constexpr T pi = T(3.1415926535897932385L);

// template function definition
template <typename T>
T add(T a, T b) {
    return a + b;
}

// template struct member definition
template <typename T, typename U>
void Pair<T, U>::foo() {
    fmt::print("Pair::foo()\n");
}

// template class definition
template <typename T>
TempClass<T>::TempClass(T t) : t(t) {
    fmt::print("TempClass::TempClass()\n");
}
