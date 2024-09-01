namespace Constants {
void constants() {
    // Const variables are evaluated at compile-time
    const int x = 5;
    const char s[] = "Hello";

    // Pointers
    int y = 10;
    const int *p1 = &y;       // Pointer to const int
    int *const p2 = &y;       // Const pointer to int
    const int *const p3 = &y; // Const pointer to const int

    //! Common error
    using ptr_t = int *;
    const ptr_t p4 = &y; // Const pointer to int (int *const)
    *p4 = 5;             // Allowed!
}
} // namespace Constants

namespace Volatile {
void vol() {
    // Volatile qualifier tells the compiler to **avoid aggressive memory optimizations**
    // involving a pointer or an object
    //    - Use it when the value of a variable can be changed by external sources
    //    - Use it when the variable is accessed by multiple threads

    // Example 1 - Reading from memory
    // Without volatile, the compiler may optimize the loop by removing the read operation
    //   - First read the value of *ptr and store it in a register
    //   - Then, for each iteration, the condition will compare the value in the register
    //     with 0, which is always true
    int *ptr1 = (int *)0x1234; // Assume this is a memory-mapped register with zero value
    // We are waiting the register to become non-zero
    while (*ptr1 == 0) {
    }
    // But with volatile, the compiler will always read the value of *ptr from the memory
    //   - For each loop, the value of *ptr is read from the memory
    volatile int *ptr2 = (volatile int *)0x1234;
    while (*ptr2 == 0) {
    }

    // Example 2 - Out of bound memory access
    // Without volatile, the compiler may optimize the code by removing the out-of-bound
    // access
    int arr[5];
    arr[5] = 10; // Undefined behavior, this code will be removed if we turn on the
                 // optimization (-O1)
    // But with volatile, the compiler will always generate the code to access the
    // out-of-bound memory
    volatile int arr2[5];
    arr2[5] = 10; // This code will not be removed and cause segmentation fault
}
} // namespace Volatile

namespace Constant_expressions {
// Constexpr functions
constexpr int square(int x) {
    // guarantee compile-time evaluation as long as ALL it's arguments are evaluated at
    // compile-time
    return x * x;

    // There are some limitations:
    //   1. No runtime features
    //   2. No goto, asm, assert
    //   3. Cannot be virtual member function (until C++20)
    //   4. No static variables
    //   5. No undefined behaviors

    // Always evaluate at runtime if:
    //   1. Contain non constexpr functions
    //   2. Contain reference to runtime global variables
}

struct S {
    int x{7};
    constexpr S(int x) : x(x) {
        // evaluated at compile-time if every base class, non-variant, non-static member
        // is initialized
    }
    constexpr int f() const { return x; }
    static constexpr int g() { return 42; }
};

// Constexpr specifier delcares an expression that CAN be evaluated at compile-time
void constexpr_variables() {
    constexpr int x = 5;
    constexpr int y = x * 2; // Evaluated at compile-time

    constexpr int z = square(8);

    constexpr S s(10);
    constexpr int a = s.f();

    // S s2(4);
    // constexpr int b = s2.f(); //! Not allowed because s2.f() is evaluated at runtime
}

int if_constexpr() {
    if constexpr (sizeof(int) == 4) {
        return 1;
    } else if constexpr (sizeof(int) == 8) {
        return 2;
    } else {
        return 3;
    }
}
} // namespace Constant_expressions