/*
    Template variables
*/
#include <array>       // std::array
#include <cstddef>     // size_t
#include <cstring>     // std::memcpy
#include <memory>      // std::uninitialized_fill_n
#include <type_traits> // std::is_arithmetic_v

// can be pi<float>, pi<double>, pi<long double>
template <typename T>
constexpr T pi = T(3.1415926535897932385L);

template <int N>
std::array<int, N> arr{};

template <typename T>
T circular_area(T r) {
    return pi<T> * r * r;
}

template <typename T>
void init(T *p, size_t N) {
    // is_arithmetic_v is a template variable
    if constexpr (std::is_arithmetic_v<T>) {
        std::memcpy(p, 0, sizeof(T) * N);
    } else {
        std::uninitialized_fill_n(p, N, T{});
    }
}

int main() {
    arr<10>[0] = 1;

    for (int i = 0; i < 10; i++) {
        arr<10>[i] = i;
    }

    arr<13>[1] = 2;
}