/*
    Optional
*/

#include <fmt/core.h> // print
#include <optional>   // optional, nullopt

void test_opt() {
    std::optional<int> opt{3}, none{std::nullopt};

    if (opt.has_value()) {
        fmt::print("opt has value: {}\n", *opt);
    }

    if (!none.has_value()) {
        fmt::print("none has no value\n");
    }

    int x = none.value_or(42); // int x = none.has_value() ? *none : 42;
}

/*
    Any type can holds any type of value and provides type-safety
*/

#include <any>    // any, any_cast
#include <string> // string

void test_any() {
    std::any a = 42;
    a = std::string{"Hello"};

    if (a.type() == typeid(std::string)) {
        fmt::print("a is string: {}\n", std::any_cast<std::string>(a));
    }

    a.reset();
    if (!a.has_value()) {
        fmt::print("a has no value\n");
    }
}