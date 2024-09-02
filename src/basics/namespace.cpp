#include <fmt/core.h>

/*
    Nested namespace (since C++17)
*/
namespace n1::n2::n3 {
struct A {};
} // namespace n1::n2::n3

/*
    Namespace alias
*/
namespace n = n1::n2::n3;

/*
    Anonymous(unnamed) namespace
    - Everything declared in an anonymous namespace has internal linkage
    - Better than static keyword
    - Members are part of its parent namespace
*/
namespace {
int x = 0;
} // namespace

/*
    Inline namespace
    - Used to versioning
    - Act like the members of inline namespace are part of its parent namespace
*/
namespace F {
inline namespace V2 {
void f() { fmt::println("{} V2", __PRETTY_FUNCTION__); }
} // namespace V2

namespace V1 {
void f() { fmt::println("{} V1", __PRETTY_FUNCTION__); }
} // namespace V1

} // namespace F

/*
    Attributes for namespace (since C++17)
*/

namespace [[deprecated]] OldNamespace {} // namespace OldNamespace

int main() {
    F::f();     // Calls F::V2::f()
    F::V1::f(); // Calls F::V1::f()
    F::V2::f(); // Calls F::V2::f()
    return 0;
}