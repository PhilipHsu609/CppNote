---
title: "Memory Allocation"
---


Dynamic memory management with new/delete.

## Stack vs Heap

```cpp
void stack_allocation() {
    int a = 42;             // stack
    int b[5] = {1,2,3,4,5}; // stack
    char s[] = "Hello";     // stack (array copied)
    const char* p = "World"; // p on stack, string in read-only section
}
```

## Basic Dynamic Allocation

```cpp
int* a = new int;        // uninitialized
int* b = new int(13);    // initialized to 13
int* c = new int{13};    // same, uniform initialization

delete a;
delete b;
delete c;
```

## Array Allocation

```cpp
int* arr1 = new int[5];           // 1D array
auto* arr2 = new int[3][2];       // 2D array (C++11)
// Note: second dimension must be constant

delete[] arr1;
delete[] arr2;
```

## Placement new

Construct in pre-allocated memory:

```cpp
alignas(std::string) char buffer[sizeof(std::string)];
std::string* s = new (buffer) std::string("Hello");

// Must manually call destructor!
s->~basic_string();
// Don't delete - memory wasn't from new
```

## Nothrow Allocation

```cpp
int* p1 = new int[100];                // throws std::bad_alloc on failure
int* p2 = new (std::nothrow) int[100]; // returns nullptr on failure

if (p2 == nullptr) {
    // handle allocation failure
}
```

## Key Points

- `new` allocates and constructs, `delete` destructs and deallocates
- Use `delete[]` for arrays allocated with `new[]`
- Placement new requires manual destructor call
- Prefer smart pointers over raw new/delete

## See Also

- [raii](../classes/raii.md) - automatic resource management
