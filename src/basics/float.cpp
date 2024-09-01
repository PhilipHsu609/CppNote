#include <fmt/core.h>

int main() {
    // Interval machine epsilon (not relative machine epsilon)
    // - the difference between 1 and the next larger floating point number
    // - interval machine epsilon = 2 * relative machine epsilon
    // - interval machine epsilon = ulp of 1.0
    // - approx 1.19e-7 for float
    fmt::println("Machine epsilon for float: {:.23f}",
                 std::numeric_limits<float>::epsilon());

    fmt::println("Lowest value for float: {:.3f}", std::numeric_limits<float>::lowest());

    // - approx 2.22e-16 for double
    fmt::println("Machine epsilon for double: {:.53f}",
                 std::numeric_limits<double>::epsilon());

    fmt::println("Lowest value for double: {:.3f}",
                 std::numeric_limits<double>::lowest());
}