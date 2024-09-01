#include <fmt/core.h>

namespace Structs {
// A named structure
struct Foo {
    int a;
    int b;
};

// A unnamed structure
struct {
    int c;
    int d;
} Bar;

/*
    * C++ does not allow anonymous structures, but C does (C11).
    struct {
        int e;
        int f;
    };
*/
Foo get_foo() { return {1, 2}; }
void structure_binding() {
    Foo foo{1, 2};
    auto [a, b] = foo;
    auto [c, d] = get_foo();

    int arr[2] = {1, 2};
    auto &[x, y] = arr;
}
} // namespace Structs

namespace Bitfields {
// A bitfield is a variable of a structure with a predefined bit width.
// * The byte-alignment of the structure with bitfields is implementation-defined.
struct Foo {
    unsigned int b1 : 10; // 10 bits [0, 1023]
    unsigned int b2 : 10; // 10 bits [0, 1023]
    unsigned int b3 : 8;  // 8 bits  [0, 255]
};                        // sizeof(Foo) == 4 bytes

struct Bar {
    unsigned int b1 : 10; // 10 bits
    unsigned int : 0;     // start a new byte
    unsigned int b2 : 10; // 10 bits
    unsigned int : 6;     // skip 6 bits
    unsigned int b3 : 10; // 10 bits
};                        // sizeof(Bar) == 8 bytes

struct Baz {
    unsigned char b1 : 3;
    unsigned char : 2;
    unsigned char b2 : 6;
    unsigned char b3 : 2;
}; // sizeof(Baz) == 2 bytes

void size() {
    fmt::println("size of Foo: {}", sizeof(Bitfields::Foo));
    fmt::println("size of Bar: {}", sizeof(Bitfields::Bar));
    fmt::println("size of Foo: {}", sizeof(Bitfields::Baz));
}
} // namespace Bitfields

namespace Unions {
union A {
    int a;
    float b;
};
// * C++17 introduces a type-safe union called std::variant
//     #include <variant>
//     std::variant<int, float> v;
} // namespace Unions

int main() { Bitfields::size(); }