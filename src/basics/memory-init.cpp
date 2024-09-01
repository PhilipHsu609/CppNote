#include <fmt/core.h>
#include <fmt/ranges.h>

namespace Memory {
void static_memory() {
    int a = 42;
    int b[5] = {1, 2, 3, 4, 5};
    char s[] = "Hello";
    char *p = "World"; //! p is a local pointer pointing to a string literal stored
                       //! in the read-only data section.
}
void dynamic_memory() {
    int *a = new int;
    int *b = new int(13);

    // 1D array
    int *c = new int[5];
    // 2D array (since C++11), the second dimension must be a constant.
    auto *d = new int[3][2];

    // non-allocating placement (allocated in a pre-allocated buffer (stack or heap))
    char *buf[sizeof(std::string)];
    std::string *s = new (buf) std::string("Hello");

    //! Objects with non-trivial destructors must MANAULLY call the destructor.
    s->~basic_string();

    // Non-thrown exceptions
    int *p1 = new int[100];                // throws std::bad_alloc if allocation fails
    int *p2 = new (std::nothrow) int[100]; // returns nullptr if allocation fails

    delete a;
    delete b;
    delete[] c;
    delete[] d;
    delete[] p1;
    delete[] p2;
}
} // namespace Memory

namespace Initialization {
void zero_init() {
    // Variables with **static** or thread-local **storage duration** declared with no
    // initializer will perform zero initialization before other initializations.
    int w;              // zero-initialized (assume this is a global variable)
    static int x;       // zero-initialized
    extern int z;       // zero-initialized
    thread_local int y; // zero-initialized
}
void default_init() {
    // Default-initialized
    //  - For all POD types, the default value is undefined.
    //  - For non-POD types, the empty argument constructor is called.

    int i;               // indeterminate value
    int *a = new int;    // indeterminate value
    int *b = new int[5]; // each element is default-initialized, indeterminate value
    std::string *s = new std::string;    // empty string
    std::string *t = new std::string[5]; // each element is an empty string

    struct S {
        int n;
        S() {}
    };
    // st call the default constructor
    //    - Members that are not in a constructor initializer list are
    //        default-initialized.
    //    - n is default-initialized (indeterminate value)
    S st;

    // Variables with **static** or thread-local **storage duration** declared with no
    // initializer will perform default initialization.

    // Assume this is a global variable.
    // it will first perform zero initialization (indeterminate value),
    // then default initialization (empty string).
    std::string u;

    delete a;
    delete s;
    delete[] b;
    delete[] t;
}
void direct_init() {
    // Direct-initialized
    int *a = new int(42);
    int b{23};
    int c(15);
    // int d();  this is a function declaration, not a variable declaration

    std::string s("Hello");
    std::string t(5, 'a');

    delete a;
}
void value_init() {
    // Value-initialized when an empty initializer.

    int i{};               // zero-initialized
    int j = int();         // zero-initialized
    int *a = new int();    // zero-initialized
    int *b = new int[5](); // each element is zero-initialized

    struct S1 {
        int mem1;
        std::string mem2;
        virtual void foo() {} // make sure S1 is not an aggregate
    }; // implicit default constructor

    struct S2 {
        int mem1;
        std::string mem2;
        S2(const S2 &) {} // user-defined copy constructor
    }; // no default constructor

    struct S3 {
        int mem1;
        std::string mem2;
        S3() {} // user-provided default constructor
    };

    /*
        S1 has an implicit default constructor -> zero-initialized -> default-initalized.
            mem1 is zero-initialized
            mem2 is default-initialized (empty string)
    */
    S1 s1{};

    // S2 s2{}; // error: no default constructor

    /*
        S3 has a user provided default constructor -> default-initialized.
            mem1 is default-initialized (indeterminate value)
            mem2 is default-initialized (empty string)
    */
    S3 s3{};

    delete a;
    delete[] b;
}
void list_init() {
    // List-initialized (since C++11)
    //     - Direct-list-initialization (w/o =)
    //           - both explicit/implicit constructors are considered
    //     - Copy-list-initialization (w/ =)
    //           - only explicit constructors are considered

    // TODO: I don't understand.
}
} // namespace Initialization
