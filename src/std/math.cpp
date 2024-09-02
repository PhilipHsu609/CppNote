#include <cmath>       // exp2, log2
#include <limits>      // numeric_limits
#include <type_traits> // enable_if_t, is_floating_point_v

void math() {
    auto x = std::exp2(3); // 2^3 = 8
    auto y = std::log2(8); // log2(8) = 3
}

template <typename T>
T get_max() {
    return std::numeric_limits<T>::max();
}

template <typename T>
T get_min() {
    return std::numeric_limits<T>::min();
}

template <typename T, std::enable_if_t<std::is_floating_point_v<T>> = 0>
T get_lowest() {
    // e.g. -infinity
    return std::numeric_limits<T>::lowest();
}

template <typename T, std::enable_if_t<std::is_floating_point_v<T>> = 0>
T get_epsilon() {
    // the machine epsilon
    return std::numeric_limits<T>::epsilon();
}
