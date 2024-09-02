/*
    Template meta programming
*/

namespace Factorial {
// Using meta programming
template <int N>
struct Factorial { // Generic template: recursive step
    static constexpr int value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial<0> { // Full specialization: base case
    static constexpr int value = 1;
};

// Using constexpr
template <typename T>
constexpr int factorial(T n) {
    T tmp = 1;
    for (T i = 2; i <= n; ++i) {
        tmp *= i;
    }
    return tmp;
}

void test() {
    static_assert(Factorial<5>::value == 120);
    static_assert(factorial(5) == 120);
}
} // namespace Factorial

namespace Log2 {
// Using meta programming
template <int N>
struct Log2 {
    static_assert(N > 0);
    static constexpr int value = 1 + Log2<N / 2>::value;
};
template <>
struct Log2<1> {
    static constexpr int value = 0;
};
void test() {
    static_assert(Log2<8>::value == 3);
    static_assert(Log2<1024>::value == 10);
}
} // namespace Log2

namespace Log {
// Using meta programming (WTF?)
template <int A, int B>
struct Max {
    static constexpr int value = A > B ? A : B;
};

template <int N, int BASE>
struct Log {
    static_assert(N > 0);
    static_assert(BASE > 0);

    static constexpr int TMP = Max<1, N / BASE>::value;
    static constexpr int value = 1 + Log<TMP, BASE>::value;
};

template <int BASE>
struct Log<1, BASE> {
    static constexpr int value = 0;
};

void test() {
    static_assert(Log<8, 2>::value == 3);
    static_assert(Log<1024, 2>::value == 10);
    static_assert(Log<1000, 10>::value == 3);
}
} // namespace Log