/*
    SFINAE (Substitution Failure Is Not An Error): When substituting the decuded type for
    the template praameter fails, the specialization is discarded from the overload set
    instead of causing a compilation error.

    Simply speaking, try to substitute the type and if it fails, discard it and move on to
    the next one until no more left, and then throw an error.
*/
#include <type_traits>

// Usage 1:
template <typename T>
T ceil_div(T value, T div); // template function declaration

/*
    We have a template function that takes an integral type T.
    But we want to specialize the function for signed and unsigned T. How?
        1. ceil_div<unsigned short>, ceil_div<short>, ceil_div<unsigned int>,
            ceil_div<int>, ... etc.
        2. Using type traits to adopt SFINAE.
            - std::enable_if allows for creating a substitution failure in order to enable
                or discard the specialization.
*/

// std::enable_if_t as a hidden template parameter

// specialization for signed T
template <typename T, std::enable_if_t<std::is_signed_v<T>> = 0>
T ceil_div(T value, T div) {
    return (value > 0 && div > 0) ? (value + div - 1) / div : value / div;
}

// specialization for unsigned T
template <typename T, std::enable_if_t<!std::is_signed_v<T>> = 0>
T ceil_div(T value, T div) {
    return (value + div - 1) / div;
}

// std::enable_if_t as a return type
template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> ceil_div(T value, T div) {
    return (value > 0 && div > 0) ? (value + div - 1) / div : value / div;
}

// Usage 2:

/*
    Check if a type has a member x.

    std::void_t is a metafunction that always yields void, used for detecting valid types.

    std::void_t<condition>
    - If condition is true, std::void_t<condition> is void, then the specialization is
        selected.
    - Otherwise, it will trigger SFINAE and the specialization is discarded. So the
        primary template is selected.
*/

template <typename T, typename = void>
struct Has_x : std::false_type {};

template <typename T>
struct Has_x<T, std::void_t<decltype(std::declval<T>().x)>> : std::true_type {};

// a useful alias to simplify the usage
template <typename T>
inline constexpr bool Has_x_v = Has_x<T>::value;