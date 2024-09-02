#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cstdint>
#include <vector>

struct foo {
    int x = 1;
    int y = 2;
};

enum class Color : uint8_t { RED, GREEN, BLUE };

template <>
struct fmt::formatter<foo> : fmt::formatter<std::string> {
    auto format(const foo &f, fmt::format_context &ctx) {
        // include<fmt/format.h>
        return fmt::formatter<std::string>::format(fmt::format("({}, {})", f.x, f.y),
                                                   ctx);
    }
};

int main() {
    std::string msg = fmt::format("The answer is {}", 42);
    std::string msg2 = fmt::format("{1} {0}!", "world", "Hello");
    fmt::print("{}, {}\n", msg, msg2);
    fmt::print(stderr, "Don't forget to flush the buffer\n");

    foo f;
    fmt::print("foo: {}\n", f);

    int x = 42;
    void *p = &x;
    fmt::print("Pointer: {:p} {}\n", p, fmt::ptr(p));

    Color c = Color::RED;
    fmt::print("Color: {}\n", fmt::underlying(c));

    // fmt/chrono.h
    auto now = std::chrono::system_clock::now();
    fmt::print("The date is {}\n", fmt::format("{:%Y-%m-%d %H:%M:%S}", now));

    // fmt/ranges.h
    std::vector<int> v = {1, 2, 3, 4, 5};
    fmt::print("{}\n", v);
    fmt::print("[{}]\n", fmt::join(v, "/ "));

    // fmt/color.h
    fmt::print(fg(fmt::color::crimson) | bg(fmt::color::floral_white) |
                   fmt::emphasis::italic,
               "Crimson text on floral white\n");
}