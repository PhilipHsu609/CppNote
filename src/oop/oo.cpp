/*
    Operator Overloading
*/
#include <fmt/core.h>
#include <iostream>

struct A {
    int x = 0;
    explicit operator int() const { return 1; }
    operator double() const { return 2.0; }

    A &operator++() { // prefix (++A) returns the new copy of A by reference
        x++;
        return *this;
    }
    A operator++(int) { // postfix (A++) returns the old copy of A by value
        A tmp = *this;
        ++*this; // call prefix operator
        return tmp;
    }

    // Copy-Swap Idiom
    friend void swap(A &a, A &b) {
        using std::swap;
        swap(a.x, b.x);
    }
    A &operator=(A a) { // copy assignment operator
        swap(*this, a);
        return *this;
    }

    // stream assignment operator
    friend std::ostream &operator<<(std::ostream &os, const A &a) {
        os << a.x;
        return os;
    }
};

struct B : A {
    // Binary operator should be implemented as friend methods, otherwise
    // B == A will work but A == B will not work
    friend bool operator==(const B &lhs, const B &rhs) { return lhs.x == rhs.x; }
};

auto f() { return A{}; }

int main() {
    int x = static_cast<int>(f()); // explicit prevent implicit conversion
    double y = f();

    fmt::print("x: {}\n", x);
    fmt::print("y: {}\n", y);
}