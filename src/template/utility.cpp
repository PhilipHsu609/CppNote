/*
    Compile-time utilities:
    1. static_assert
    2. using
    3. decltype
    4. type_traits
*/
#include <type_traits>

namespace Static_assert {
static_assert(sizeof(int) == 4, "error message");
static_assert(sizeof(int) == 4); // No error message since C++17
} // namespace Static_assert

namespace Using {
// using is an inhanced version of typedef
using func = void (*)(int, int);

// using can also be used to define partial/full specialization aliases of a template
template <typename T, int size>
struct Vector {};

template <int size>
using Bitset = Vector<bool, size>; // partial specialization
using Int4 = Vector<int, 4>;       // full specialization
} // namespace Using

namespace Decltype {
// decltype captures the type of an entity or an expression
void f(int, int);

static_assert(std::is_same_v<decltype(f), void(int, int)>);
static_assert(std::is_same_v<decltype(f(1, 2)), void>);

using f_type = decltype(f); // f_type is a function type
f_type *f_ptr = f;          // f_ptr is a pointer to a function

// double parentheses will get the reference type
int x = 1;
static_assert(std::is_same_v<decltype((x)), int &>);
} // namespace Decltype

namespace Type_traits {
/*
    type_traits define a compile time interface to query or modify the properties of types

    Type properties:
    - is_<type>
    - is_<ref/ptr/const/volatile>
    - is_<class/abstract/polymorphic>
    - is_<same/base_of/convertible>
    - and more...

    Type manipulation:
    - make_<signed/unsigned>
    - add_<const/pointer/lvalue_reference>
    - remove_<const/pointer/reference>
    - and more...
*/

// 1. type check in template (instead of specialization)
template <typename T>
void g(T t) {
    if constexpr (std::is_integral_v<T>) {
        // do something
    } else if constexpr (std::is_floating_point_v<T>) {
        // do something
    } else {
        // do something
    }
}
template <typename T>
T add(T a, T b) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    return a + b;
}

// 2. type manipulation
template <typename T>
void f(T ptr) {
    using R = std::remove_pointer_t<T>;
    R x = *ptr;
}
} // namespace Type_traits