#include <cstddef>
#include <cstdlib>

namespace Functions {
// Function signature defines
//     - input types for a function
//     - input and output type for a template function
// Function signature includes
//     - number of arguments
//     - argument types
//     - order of arguments
// Function overload allows functions with the same name but different signatures
void f(int) {}
void f(double) = delete; // delete overloading for a specific type

void g(int *) {}
void g(std::nullptr_t) = delete;
} // namespace Functions

namespace Function_pointers {
// fp is a function pointer that takes two int as arguments and returns an int
void g(int (*fp)(int, int)) {}
// WTF is fp?
// fp is a pointer to a function            (*fp)
//    - that takes an int as argument       (*fp)(int)
//    - and returns a pointer               *(*fp)(int)
//    - to an array of 10                   (*(*fp)(int))[10]
//    - pointers to int                     int*(*(*fp)(int))[10]
void f(int *(*(*fp)(int))[10]) {}
} // namespace Function_pointers

namespace Functors {
// A function object or functor is a callable object that can be treated as a parameter.
//     - Since C++11, lambdas can replace functors in many cases.
struct Functor {
    void operator()() {}
};
} // namespace Functors

namespace Lambda_expressions {
// auto x = [capture value](parameters) { body }
void lambda() {
    // Since C++14, lambda can be generic
    auto g = [](auto x, auto y) { return x + y; };

    // Since C++14, lambda parameters can have default values
    auto h = [](int x = 0) { return x; };

    // Since C++17, lambda can have constexpr
    auto factorial = [](int n) constexpr {
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    };
    constexpr int result = factorial(10);

    // mutable lambda expression
    int x = 0;
    auto f = [x]() mutable {
        // lambda capture is by-const-value
        // mutable specifier allows to modify the parameters captured by value
        x = 1;
        return x;
    };
}
} // namespace Lambda_expressions
