---
title: "fmt"
---


Modern formatting library (basis for C++20 `std::format`).

## Basic Formatting

```cpp
#include <fmt/core.h>

std::string msg = fmt::format("The answer is {}", 42);
std::string msg2 = fmt::format("{1} {0}!", "world", "Hello");

fmt::print("{}, {}\n", msg, msg2);
fmt::print(stderr, "Don't forget to flush the buffer\n");
```

## Custom Formatter

```cpp
#include <fmt/format.h>

struct foo {
    int x = 1;
    int y = 2;
};

template <>
struct fmt::formatter<foo> : fmt::formatter<std::string> {
    auto format(const foo &f, fmt::format_context &ctx) {
        return fmt::formatter<std::string>::format(
            fmt::format("({}, {})", f.x, f.y), ctx);
    }
};

foo f;
fmt::print("foo: {}\n", f);  // foo: (1, 2)
```

## Pointers and Enums

```cpp
int x = 42;
void *p = &x;
fmt::print("Pointer: {:p} {}\n", p, fmt::ptr(p));

enum class Color : uint8_t { RED, GREEN, BLUE };
Color c = Color::RED;
fmt::print("Color: {}\n", fmt::underlying(c));  // Color: 0
```

## Chrono Formatting

```cpp
#include <fmt/chrono.h>

auto now = std::chrono::system_clock::now();
fmt::print("The date is {}\n", fmt::format("{:%Y-%m-%d %H:%M:%S}", now));
```

## Range Formatting

```cpp
#include <fmt/ranges.h>

std::vector<int> v = {1, 2, 3, 4, 5};
fmt::print("{}\n", v);                    // [1, 2, 3, 4, 5]
fmt::print("[{}]\n", fmt::join(v, "/ ")); // [1/ 2/ 3/ 4/ 5]
```

## Color Output

```cpp
#include <fmt/color.h>

fmt::print(fg(fmt::color::crimson) | bg(fmt::color::floral_white) |
               fmt::emphasis::italic,
           "Crimson text on floral white\n");
```

## Headers

| Header | Features |
|--------|----------|
| `fmt/core.h` | `format`, `print` (minimal) |
| `fmt/format.h` | Full formatting, custom formatters |
| `fmt/ranges.h` | Container and range formatting |
| `fmt/chrono.h` | Date/time formatting |
| `fmt/color.h` | Terminal colors and styles |

## Key Points

- Faster than iostreams and printf
- Type-safe formatting
- Basis for C++20 `std::format`
- Extensible via custom formatters
- Header-only or compiled modes

## See Also

- [io](../stdlib/io.md) - standard I/O streams
- [chrono](../stdlib/chrono.md) - time utilities
