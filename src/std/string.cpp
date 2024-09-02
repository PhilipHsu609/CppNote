#include <charconv>    // from_chars
#include <cstddef>     // size_t
#include <string>      // string, string_literals, to_string
#include <string_view> // string_view

using namespace std::string_literals;

void cvt() {
    std::string num = "FF"s;

    int x;
    std::size_t num_char_processed;
    x = std::stoi(num, &num_char_processed, 16);

    // since C++17
    // - faster, no allocation, no exceptions
    std::from_chars(num.data(), num.data() + num.size(), x, 16);

    int y = 255;
    num = std::to_string(y);
}

void view() {
    // string_view
    // - since C++17
    // - reference to a read-only string

    std::string str = "Hello, World!";
    std::string_view view = str;
}