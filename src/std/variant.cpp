/*
    Variant: a type-safe union (since C++17)
*/

#include <variant>

void basic() {
    std::variant<int, float, bool> v(3.3f);

    // std::get<type>
    int x = std::get<int>(v);
    float f = std::get<float>(v);

    // std::get<index>
    x = std::get<0>(v);
    f = std::get<1>(v);

    // index() returns the position of the type in the variant
    int index = v.index(); // last time we accessed the float, so index is 1

    std::get<bool>(v) = true;
    index = v.index(); // now index is 2
}

void visit() {
    std::variant<int, float, bool> v(3.3f);

    // std::visit(visitor, variant)
    // - apply a callable visitor to the variant
    std::visit(
        [](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                // arg is int
            } else if constexpr (std::is_same_v<T, float>) {
                // arg is float
            } else if constexpr (std::is_same_v<T, bool>) {
                // arg is bool
            }
        },
        v);
}