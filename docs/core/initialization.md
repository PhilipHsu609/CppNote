---
title: "Initialization"
---


How variables get their initial values.

## Zero Initialization

Static/thread-local storage with no initializer:

```cpp
int w;              // zero (if global/static)
static int x;       // zero
extern int z;       // zero
thread_local int y; // zero
```

## Default Initialization

No initializer provided:

```cpp
int i;                     // indeterminate value (if local)
int* a = new int;          // indeterminate
int* b = new int[5];       // each element indeterminate
std::string s;             // empty string (constructor called)
```

For non-POD types, the default constructor runs.

## Direct Initialization

Explicit value in parentheses or braces:

```cpp
int* a = new int(42);
int b{23};
int c(15);
// int d(); // This declares a function!

std::string s("Hello");
std::string t(5, 'a'); // "aaaaa"
```

## Value Initialization

Empty initializer `{}` or `()`:

```cpp
int i{};               // 0
int j = int();         // 0
int* a = new int();    // 0
int* b = new int[5](); // all zeros
```

### Value Initialization of Structs

```cpp
struct S1 {
    int mem1;
    std::string mem2;
    virtual void foo() {} // makes S1 non-aggregate
};

struct S3 {
    int mem1;
    std::string mem2;
    S3() {} // user-provided default constructor
};

S1 s1{}; // mem1 = 0, mem2 = "" (zero + default init)
S3 s3{}; // mem1 = indeterminate, mem2 = "" (only default init)
```

- Implicit constructor → zero-init then default-init
- User-provided constructor → only default-init

## List Initialization (C++11)

Using braces `{}`:

```cpp
int x{5};
std::vector<int> v{1, 2, 3};

// Direct-list-initialization (no =)
std::string s{"hello"};

// Copy-list-initialization (with =)
std::string t = {"hello"};
```

## Key Points

- Global/static variables are zero-initialized
- Local POD variables are uninitialized (garbage)
- `{}` value-initializes (zeros for POD)
- `()` after `new` value-initializes
- User-provided constructors skip zero-initialization

## See Also

- [constructors](../classes/constructors.md) - class initialization
- [allocation](../memory/allocation.md) - dynamic allocation
