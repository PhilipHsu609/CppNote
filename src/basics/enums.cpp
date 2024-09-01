#include <fmt/core.h>
#include <type_traits>

namespace Enums {
// enum is not strongly typed
enum Color { RED, GREEN, BLUE };
enum Fruit { APPLE, BANANA, CHERRY };
void problems() {
    Color c = RED;
    Fruit f = APPLE;

    if (c == f) {
        // This will compile, but it's not what you want
        fmt::println("Color equals Fruit");
    }

    if (c == Fruit::APPLE) {
        // This will compile, but it's not what you want
        fmt::println("RED equals APPLE");
    }

    int x = GREEN + CHERRY;
    fmt::println("RED + APPLE = {} ?!", x);
}

// enum class is strongly typed (allow explicit conversion)
enum class Animal { dog, deer, cat, bird, human };
enum class Mammal { kangaroo, deer, human };
void features() {
    // enum/enum class are automatically enumerated starting from 0
    static_assert(static_cast<int>(Animal::bird) == 3);

    // enum/enum class can be compared
    static_assert(Color::RED < Color::GREEN);
    static_assert(Animal::dog < Animal::deer);

    // enum/enum class
    //     allow setting underlying type
    //     allow setting explicit values
    //     allow aliasing
    //     support attributes
    enum class Foo : uint8_t { A = 1, B = 4, C [[deprecated]] = 255, D = 0, E = 1 };
    static_assert(Foo::A == Foo::E);
    static_assert(std::is_same_v<std::underlying_type_t<Foo>, uint8_t>);

    Foo f = Foo::C; // warning: 'C' is deprecated
}
} // namespace Enums

int main() {
    Enums::problems();
    Enums::features();
    return 0;
}