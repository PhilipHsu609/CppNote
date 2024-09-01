#include <fmt/core.h>

int main() {
    /*
        C++11 introduces implementation-defined attributes.
        Some of the attributes are standardized in C++ and others are compiler-specific.

        Ref:
        - https://www.youtube.com/watch?v=teUA5U6eYQY
        - https://clang.llvm.org/docs/AttributeReference.html
    */
}

// Some standard attributes (till C++17)

// The function never returns.
[[noreturn]] void f() { throw "error"; }

// Indicates that the use of the name or entity decalred with this attribute is allowed,
// but discouraged for some reason.
[[deprecated("use G() instead")]] void g() { fmt::print("g() is deprecated\n"); }

// Encourages the compiler to issue a warning if the return value is discarded,
// useful for functions that return a value that should be used, such as allocated memory
// address, an error code, etc.
//     e.g. use `int x = h();` instead of `h();`
[[nodiscard]] int h() { return 42; }

// maybe unused
[[maybe_unused]] void i() { fmt::print("i() is not used\n"); }

void a_switch() {
    int x = 1;
    switch (x) {
    case 1:
        fmt::print("x is 1\n");
        [[fallthrough]]; // fallthrough to the next case
    case 2:
        fmt::print("x is 2\n");
        break;
    }
}
