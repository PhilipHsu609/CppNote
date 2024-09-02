#include <fmt/core.h>
#include <fmt/format.h>

#include "lib.hpp"

int main() {
    Color c = Color::RED;

    Foo foo;

    fmt::print("func() = {}\n", func());

    fmt::print("extern_var = {}\n", extern_var);

    fmt::print("specialized add(1, 2) = {}\n", add(1, 2));
    fmt::print("add(1.5, 2.3) = {}\n", add(1.5, 2.3));

    Pair<int, double> pair{1, 2.4};
    TempClass<int> temp{3};

    fmt::print("inline const var = {}\n", inline_var);
    fmt::print("inline constexpr var = {}\n", inline_constexpr_var);

    fmt::print("inline var = {}\n", test);

    test_inline();
    fmt::print("inline var = {}\n", test);

    fmt::print("square(5) = {}\n", square(5));

    fmt::print("non_static_const = {}\n", non_static_const);
    fmt::print("non_static_constexpr = {}\n", non_static_constexpr);

    fmt::print("pi<float> = {}\n", pi<float>);

    return 0;
}