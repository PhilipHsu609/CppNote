---
title: "std::string"
---


Dynamic character sequence.

## Conversions

```cpp
#include <string>
#include <charconv>

using namespace std::string_literals;

// String to integer
std::string num = "FF"s;
std::size_t pos;
int x = std::stoi(num, &pos, 16); // hex, pos = chars processed

// C++17: faster, no allocation, no exceptions
int y;
std::from_chars(num.data(), num.data() + num.size(), y, 16);

// Integer to string
int val = 255;
std::string s = std::to_string(val);
```

## String Literals

```cpp
using namespace std::string_literals;

auto s1 = "hello"s;        // std::string
auto s2 = "hello";         // const char*
auto s3 = "hello"sv;       // std::string_view (C++17)
```

## string_view (C++17)

Non-owning reference to string data:

```cpp
#include <string_view>

std::string str = "Hello, World!";
std::string_view view = str;  // no copy

void process(std::string_view sv);  // efficient parameter
process("literal");                  // no allocation
process(str);                        // no copy
```

## Key Points

- `std::string` owns its data
- `std::string_view` is a non-owning view
- Use `from_chars`/`to_chars` for fast conversions
- String literals with `s` suffix create `std::string`
- Pass `string_view` to functions for efficiency

## See Also

- [io](../io.md) - string I/O
