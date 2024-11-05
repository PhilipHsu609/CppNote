/*
    Variadic template captures a parameter pack of arguments, which hold an arbitrary
    number of values or types.

    - parameter pack: `... TArgs`
    - pack expansion: `TArgs... args`
*/
#include <cstddef>
#include <iostream>
#include <type_traits>

namespace Basic {
template <typename... TArgs> // variadic typename ->  TArgs is a template parameter pack
void f(TArgs... args) {      // args is a function parameter pack
    auto numOfArgs = sizeof...(args);
}

template <typename T>
T add(T a, T b) {
    return a + b;
}

template <typename T, typename... TArgs> // variadic typename
T add(T a, TArgs... args) {              // typename expansion
    return a + add(args...);             // argument expansion
    // recursively call add(T a, TArgs...) and the first argument is removed
    // until we reach the base case
}

// We can apply function to each variadic argument
template <typename T>
T square(T x) {
    return x * x;
}
template <typename... TArgs>
auto add_square(TArgs... args) {
    return add(square(args)...); // each argument is squared
}

template <typename... TArgs>
void g(TArgs... args) {
    // type expansion and argument expansion
    f<std::make_unsigned_t<TArgs>...>(args...);
}

void test() {
    f(1, 2ll, 3u, 'a');
    // expanded to f(TArgs...) [TArgs=<int, long long, unsigned int, char>]

    // lambda with variadic arguments (since C++14)
    auto foo = [](auto... args) { size_t size = sizeof...(args); };
}
} // namespace Basic

namespace Folding {
/*
    Folding expression (since C++17)

    Perform a fold of a parameter pack over a unary/binary operator.

    - unary right fold
        (args op...) => (args1 op (...op (argsN-1 op argsN)))
    - unary left fold
        (... op args) => (((args1 op args2) op ... ) op argsN)
    - binary right fold
        (args op ... op init) => (args1 op (...op (argsN op init)))
    - binary left fold
        (init op ... op args) => (((init op args1) op ... ) op argsN)

    left/right fold is determined by the position of the parameter pack
*/
template <typename... TArgs>
auto add1(TArgs... args) {
    return (args + ...);
}
template <typename... TArgs>
auto add2(TArgs... args) {
    return (0 + ... + args);
}

// comma operator
// see basic/types.cpp, comma operator has left-to-right associativity
template <typename... TArgs>
auto comma1(TArgs... args) {
    // unary right fold: (E1, (E2, (E3, (..., EN)))) => EN
    return (args, ...);
}
template <typename... TArgs>
auto comma2(TArgs... args) {
    // unary left fold: ((((E1, E2), E3), ...), EN) => EN
    return (..., args);
}

// stream operator
template <typename... TArgs>
void output(TArgs... args) {
    // binary left fold
    // (((stc::cout << E1) << E2) << ... ) << EN
    (std::cout << ... << args) << '\n';
}
} // namespace Folding