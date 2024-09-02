#include <array>
#include <cstddef>
#include <iostream>

// 2D Matrix
template <typename T, size_t Row, size_t Col>
using Matrix = std::array<std::array<T, Col>, Row>;

// Higher Dimensional Matrix
template <typename T, size_t Dim, size_t... Dims>
struct MultiDimArray {
    using type = std::array<typename MultiDimArray<T, Dims...>::type, Dim>;
};

template <typename T, size_t Dim>
struct MultiDimArray<T, Dim> {
    using type = std::array<T, Dim>;
};

template <typename T, size_t... Dims>
using Array = typename MultiDimArray<T, Dims...>::type;

int main() {
    [[maybe_unused]]
    Matrix<int, 2, 3> matrix = {{{1, 2, 3}, {4, 5, 6}}};

    Array<int, 2, 2, 2> array_3d = {{{{{{1, 2}}, {{3, 4}}}}, {{{{5, 6}}, {{7, 8}}}}}};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                std::cout << array_3d[i][j][k] << " ";
            }
        }
    }

    return 0;
}