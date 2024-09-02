#include "lib.hpp"

/*
    =============== Internal linkage ===============
*/
namespace {
/*
    Everything in anonymous namespace are internal linkage
*/
void im_internal() {}
} // namespace

// static function has internal linkage
//   (better to place it in an anonymous namespace)
static int bar() {
    int x = 1;
    return x;
}

// static variable has internal linkage
//   (better to place it in an anonymous namespace)
static int svar = 0;

/*
    =============== External linkage ===============
*/
// external linkage variable definition
int extern_var = 77;

// external linkage function definition
int func() { return 66; }

// template specialization has external linkage
// (just like a standard function)
template <>
int add<int>(int a, int b) {
    return a + b + 777;
}

// class definition
Foo::Foo() {}
void Foo::foo() {}