#include <cstddef>
#include <fmt/core.h>

#include <cstdint>
#include <type_traits>

namespace Fundemental_types {
void fundamental_types() {
    // Arithmetic types: bool, char, int, float, double
    static_assert(std::is_arithmetic_v<bool> && std::is_arithmetic_v<char> &&
                      std::is_arithmetic_v<int> && std::is_arithmetic_v<float> &&
                      std::is_arithmetic_v<double> && std::is_arithmetic_v<std::size_t>,
                  "Arithmetic types are fundamental types");

    // void, std::nullptr_t
    static_assert(std::is_fundamental_v<void> && std::is_fundamental_v<std::nullptr_t>,
                  "They are also fundamental types");
}
} // namespace Fundemental_types

namespace Compound_types {
void compound_types() {
    enum class Color { Red, Green, Blue };
    struct Point {
        int x;
        int y;
    };
    union types {
        int i;
        float f;
    };
    void foo();

    // Compound types:
    // pointers, references, enumerators, arrays, structures, unions, classes, functions
    static_assert(std::is_compound_v<int *> && std::is_compound_v<int &> &&
                      std::is_compound_v<int[10]> && std::is_compound_v<Color> &&
                      std::is_compound_v<Point> && std::is_compound_v<types> &&
                      std::is_compound_v<decltype(foo)>,
                  "Those are compound types");
}
} // namespace Compound_types

namespace Nullptr_type {
void foo([[maybe_unused]] int *ptr) { fmt::print("foo(int* ptr)\n"); }
void foo([[maybe_unused]] std::nullptr_t ptr) { fmt::print("foo(std::nullptr_t ptr)\n"); }
void nullptr_type() {
    // nullptr, the pointer literal, is an object of type std::nullptr_t
    static_assert(sizeof(nullptr) == sizeof(void *), "nullptr is a pointer literal");

    // nullptr can be used to disambiguate overloaded functions
    // e.g. f(0) or f(NULL) is ambiguous
    int *p{};
    foo(p);
    foo(nullptr);
}
} // namespace Nullptr_type

namespace Conversion_rules {
void promotions() {
    /*
        Promotion rules, from top to bottom (pick the first match):
    */

    // 1. Floating point promotion
    static_assert(std::is_same_v<decltype(1.0f + 1), float>, "float + int = float");

    // 2. Implicit integral promotion
    static_assert(std::is_same_v<decltype('a' + 'b'), int>,
                  "small int + small int = int");
    std::uint8_t a = 255, b = 255;
    fmt::println("a + b = {}", a + b); // 510 (integral promotion, no overflow)

    // 3. Size promotion
    static_assert(std::is_same_v<decltype(1 + 1ll), long long>,
                  "small int + large int = large int");
    static_assert(std::is_same_v<decltype('a' + true), int>);

    // 4. Signedness promotion (between same size)
    static_assert(std::is_same_v<decltype(1u + 1), unsigned int>,
                  "unsigned + signed = unsigned");
}
} // namespace Conversion_rules

namespace Type_cast {
void old_style() {
    int a = 5;
    float f = (float)a;
}
void new_style() {
    int a = 5;
    // Static cast perfrom compile-time type check
    float f = static_cast<float>(a);

    // Const cast can add or remove constness or volatility
    const int b = 10;
    int *p = const_cast<int *>(&b); // Remove constness
    *p = 20;                        // Undefined behavior

    // Reinterpret cast (bit-level conversion)
    //    - reinterpret_cast<T*>(v) == (T*)v
    //    - reinterpret_cast<T&>(v) == *((T*)&v)
    int c = reinterpret_cast<int &>(f); // cast float to int in bit-level
    int *q = reinterpret_cast<int *>(&f);
    // int v = static_cast<std::size_t>(q);
    //     error: static_cast cannot cast pointer to integer
    int v = reinterpret_cast<std::size_t>(q); // cast pointer to integer

    // Array reshape
    int arr[3][4] = {};
    int(&arr2)[2][6] = reinterpret_cast<int(&)[2][6]>(arr);

    // Cast 3x4 int array to 1x2 array of pointers point to 1x6 int array
    // (6 * sizeof(int*) = 48 bytes = 3 * 4 * sizeof(int))
    int(*arr3)[6] = reinterpret_cast<int(*)[6]>(arr);
}
} // namespace Type_cast

namespace Misc {
void integer() {
    static_assert(std::is_same_v<std::size_t, unsigned long>);
    static_assert(std::is_signed_v<std::ptrdiff_t>);
}
void assignemnt() {
    // Assignment, Compound have **right-to-left** associativity
    int b;
    int a = b = 1; // b=1, then a=1
}
void comma() {
    int b;
    // Comma operator has **left-to-right** associativity
    int x = (1, 2, 3);  // x=3
    int y = (b = 2, 4); // b=2, y=4
}
} // namespace Misc