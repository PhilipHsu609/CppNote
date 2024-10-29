#include <string>
#include <type_traits>

template <typename T>
T add(T a, T b) {
    return a + b;
}

// explicit template instantiation
//   - may not be used, but the compiler will generate the code
//   - useful for libraries, generate all possible instantiations before the user uses
//     them
//   - allows to separate the declaration (in header file) and definition (in source file)
template <>
std::string add<std::string>(std::string, std::string);

/*
    Template parameter types can be
    1. integral types
    2. enum, enum class
    3. floating-point types (since C++20)
    4. auto (since C++17)
    5. typename

    and some rarely used types
    1. function
    2. ref/ptr to global static function or object
    3. pointer to member type
    4. nullptr_t
*/

template <int T, int U> // template parameter
int add() {
    return T + U; // compile-time computation
}

template <auto T, auto U>
auto sub() {
    return T - U;
}

enum class Dir { LEFT, RIGHT };
template <Dir dir = Dir::RIGHT> // template parameter with default value
void move() {
    if (dir == Dir::LEFT) {
        // move left
    } else {
        // move right
    }
}

template <int a, typename T>
T ceil_div(T b) {
    return (a + b - 1) / b;
}

template <typename = void>
void g() {} // g() is generated if it is called

void f() {
    add(1, 2);     // implicit template instantiation (add<int>)
    add(1.0, 2.0); // implicit template instantiation (add<double>)
    add<3, 3>();   // compile-time computation

    sub<1ll, 2u>(); // sub<long long, unsigned int>

    ceil_div<3>(2);   // 2
    ceil_div<5>(2.0); // 2.5
}

template <typename T>
bool equal(T a, T b) {
    return a == b;
    // it's not safe to compare floating points,
    // so we need to specialize the template
}

// template specialization (can be specialized if all template parameters are provided)
template <>
bool equal<float>(float a, float b) {
    return std::abs(a - b) < 1e-6;
}

namespace ArgumentDeduction {
template <typename T>
T max(T a, T b);

void test1() {
    max(1, 2);     // T is int
    max(1.0, 2.0); // T is double
    // max(1, 2.0);   // error, T cannot be deduced

    const int a = 1, b = 2;
    max(a, b); // T is int

    int i = 1;
    int arr[3] = {1, 2, 3};
    max(&i, arr); // T is int*

    max<double>(1, 2); // T is double
}

// template parameters for return types
template <typename RT, typename T1, typename T2>
RT f1(T1 a, T2 b) {
    return a + b;
}
// deducing return type (since C++14)
template <typename T1, typename T2>
auto f2(T1 a, T2 b) {
    return a + b;
}
// trailing return type (since C++11)
template <typename T1, typename T2>
auto f3(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}
// what if the return type is a reference? We don't want that
// std::decay_t removes reference, const, and volatile qualifiers
template <typename T1, typename T2>
auto f4(T1 a, T2 b) -> typename std::decay_t<decltype(a + b)> {
    return a + b;
}
// return common type
template <typename T1, typename T2>
std::common_type_t<T1, T2> f5(T1 a, T2 b) {
    return a + b;
}
} // namespace ArgumentDeduction