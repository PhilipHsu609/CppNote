---
title: "Singleton Pattern"
---


Ensure a class has only one instance.

## Thread-Safe Singleton (Modern C++)

```cpp
class Singleton {
    static std::unique_ptr<Singleton> instance;
    static std::once_flag init_flag;

    Singleton() = default;  // private constructor

public:
    // Delete copy operations
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::call_once(init_flag, []() {
            instance.reset(new Singleton());
        });
        return instance.get();
    }

    void doSomething() { /* ... */ }
};

// Initialize statics
std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::once_flag Singleton::init_flag;
```

## Meyers Singleton (Simpler)

```cpp
class Singleton {
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        static Singleton instance;  // C++11 guarantees thread-safe
        return instance;
    }
};
```

## Usage

```cpp
Singleton::getInstance().doSomething();

// Or store reference
Singleton& s = Singleton::getInstance();
s.doSomething();
```

## When to Use

Good for:
- Logger
- Configuration manager
- Hardware interface manager

Avoid when:
- Testing is important (hard to mock)
- Multiple instances might be needed later

## Key Points

- Private constructor prevents external instantiation
- Delete copy constructor and assignment
- C++11 static locals are thread-safe (Meyers singleton)
- `std::call_once` for explicit thread-safety
- Consider dependency injection instead

## See Also

- [factory](factory.md) - controlled creation
- [mutex](../../concurrency/mutex.md) - thread synchronization
