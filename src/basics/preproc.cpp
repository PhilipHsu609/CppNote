#include <fmt/core.h>

#define VAL 10
#undef VAL

#if defined(VAL)
#elif !defined(VAL)
#else
#endif

// Feature test macros
#if __has_include(<optional>)
#include <optional>
#endif

// Stringizing operator #
#define STR(s) #s // s will be enclosed in double quotes

void f() { fmt::println("{}:{} {} {}", __FILE__, __LINE__, __FUNCTION__, __func__); }

template <typename T>
float g(T p) {
    fmt::println("{}", __PRETTY_FUNCTION__);
    return 0.0f;
}

void conditional_compile() {
#ifdef __cplusplus
    fmt::println("C++");
#endif

// C++ version
#if __cplusplus == 199711L
    fmt::println("C++98");
#elif __cplusplus == 201103L
    fmt::println("C++11");
#elif __cplusplus == 201402L
    fmt::println("C++14");
#elif __cplusplus == 201703L
    fmt::println("C++17");
#elif __cplusplus == 202002L
    fmt::println("C++20");
#endif

// Compiler
#ifdef __GNUG__
    fmt::println("GNU C++");
#endif

#ifdef __clang__
    fmt::println("Clang");
#endif

#ifdef _MSC_VER
    fmt::println("MSVC");
#endif

// OS / environment
#ifdef __linux__
    fmt::println("Linux");
#endif

#ifdef _WIN32
    fmt::println("Windows");
#endif

#ifdef _WIN64
    fmt::println("Windows 64-bit");
#endif

#ifdef __MINGW32__
    fmt::println("MinGW 32-bit");
#endif

#ifdef __APPLE__
    fmt::println("Apple");
#endif

#ifdef __unix__
    fmt::println("Unix");
#endif
}

// compiler dependent
#pragma message("This is a message")

#define FUNC_GEN(type) \
    void to_##type() { fmt::println("to_" #type); }

FUNC_GEN(int)
FUNC_GEN(float)

int main() {
    // Source location macros
    // __LINE__
    // __FILE__
    // __FUNCTION__
    // __PRETTY_FUNCTION__
    // __func__

    to_int();
    to_float();

    f();
    g(10);
    conditional_compile();
}

// #error "This is an error" // compiler will stop here