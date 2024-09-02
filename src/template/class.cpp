#include <string>

namespace Class_template {
/*
    Class template
*/

template <typename T, typename U>
struct A {
    T a;
    U b;
};

// The difference with function template is that class template can have partial
// specialization
//! The partial and full specialized class is a completely new class
//! Has nothing related to the generic class
template <typename T>
struct A<T, int> {
    T c;
    int d;
    float f;
};

template <>
struct A<float, long long> {
    float e;
    long long f;
    double g;
};

// We can implement our own type traits using partial specialization

// type_traits has two classes std::true_type and std::false_type
// which contains a true and false value respectively
#include <type_traits>

// 1. is_same
template <typename T, typename U>
struct is_same : std::false_type {};

// partial specialization
// the specialized one will return true
template <typename T>
struct is_same<T, T> : std::true_type {};

static_assert(is_same<int, int>::value, "int is same as int");
static_assert(!is_same<int, float>::value, "int is not same as float");

// 2. is_const_ptr
template <typename T>
struct is_const_ptr : std::false_type {};

template <typename T>
struct is_const_ptr<const T *> : std::true_type {};

static_assert(is_const_ptr<const int *>::value, "const int* is const ptr");
static_assert(!is_const_ptr<int *>::value, "int* is not const ptr");

} // namespace Class_template

namespace CTAD {
/*
    Class Template Argument Deduction (since C++17)

    e.g. std::pair p(1, 3.14); // no need to specify the type

    The compiler will deduce the type of the template arguments
    but we can also provide the deduction guide
*/
template <typename T>
struct A {
    A(T) {}
};

//* Deduction guide
//  constructor -> class instantiation
A(const char *) -> A<std::string>;

void test() {
    A a("hello");
    static_assert(std::is_same_v<decltype(a), A<std::string>>);
}
} // namespace CTAD