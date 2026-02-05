---
title: "Copy and Move"
---


Value semantics and efficient transfers.

## Special Member Functions

```cpp
class A {
public:
    A();                       // default constructor
    A(const A& a);             // copy constructor
    A(A&& a);                  // move constructor
    A& operator=(const A& a);  // copy assignment
    A& operator=(A&& a);       // move assignment
    ~A();                      // destructor
};
```

## Copy Semantics

Deep copy - new independent object:

```cpp
struct Widget {
    int* data;

    Widget(const Widget& other)
        : data(new int(*other.data)) {} // deep copy

    Widget& operator=(const Widget& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
};
```

## Move Semantics (C++11)

Transfer ownership - source left in valid but unspecified state:

```cpp
struct Widget {
    int* data;

    Widget(Widget&& other) noexcept
        : data(other.data) {
        other.data = nullptr;  // leave source empty
    }

    Widget& operator=(Widget&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

## When Each Is Called

```cpp
Widget w1;
Widget w2 = w1;           // copy constructor
Widget w3 = std::move(w1); // move constructor

w2 = w3;                  // copy assignment
w2 = std::move(w3);       // move assignment
w2 = Widget{};            // move assignment (temporary)
```

## Rule of Zero/Three/Five

**Rule of Zero:** Don't define any special members if you don't need to.

**Rule of Three (pre-C++11):** If you define destructor, copy constructor, or copy assignment, define all three.

**Rule of Five (C++11+):** Add move constructor and move assignment to the three.

```cpp
// Rule of Zero - preferred
struct Modern {
    std::vector<int> data;  // handles everything
};

// Rule of Five - when needed
struct Legacy {
    int* raw;
    Legacy();
    ~Legacy();
    Legacy(const Legacy&);
    Legacy(Legacy&&) noexcept;
    Legacy& operator=(const Legacy&);
    Legacy& operator=(Legacy&&) noexcept;
};
```

## Copy Elision (RVO)

Compiler can skip copy/move:

```cpp
Widget create() {
    return Widget{};  // may construct directly at call site
}

Widget w = create();  // no copy/move (RVO)
```

C++17 guarantees RVO in many cases.

## Key Points

- Copy creates independent duplicate
- Move transfers ownership (faster)
- Use `std::move` to enable move
- Mark move operations `noexcept`
- Follow Rule of Zero when possible
- Compiler may elide copies (RVO)

## See Also

- [constructors](constructors.md) - constructor details
- [raii](raii.md) - resource management
