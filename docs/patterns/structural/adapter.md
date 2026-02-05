---
title: "Adapter Pattern"
---

# Adapter Pattern

Convert one interface to another.

## Class Diagram

```
Client → Target (interface)
              ↑
           Adapter → Adaptee
```

## Implementation

```cpp
// Target interface (what client expects)
class Target {
public:
    virtual ~Target() = default;
    virtual std::string request() const {
        return "Target: default behavior";
    }
};

// Adaptee (incompatible interface)
class Adaptee {
public:
    std::string specificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";  // reversed
    }
};

// Adapter makes Adaptee work with Target interface
class Adapter : public Target {
    std::shared_ptr<Adaptee> adaptee_;

public:
    Adapter(std::shared_ptr<Adaptee> adaptee) : adaptee_(adaptee) {}

    std::string request() const override {
        std::string result = adaptee_->specificRequest();
        std::reverse(result.begin(), result.end());
        return "Adapter: (TRANSLATED) " + result;
    }
};
```

## Usage

```cpp
void clientCode(const std::shared_ptr<Target>& target) {
    std::cout << target->request() << "\n";
}

// Client works with Target
auto target = std::make_shared<Target>();
clientCode(target);

// Adaptee has incompatible interface
auto adaptee = std::make_shared<Adaptee>();
// clientCode(adaptee);  // Won't work!

// Adapter makes it work
auto adapter = std::make_shared<Adapter>(adaptee);
clientCode(adapter);  // Works!
```

## Object vs Class Adapter

**Object Adapter** (composition):
```cpp
class Adapter : public Target {
    Adaptee* adaptee_;  // composition
};
```

**Class Adapter** (multiple inheritance):
```cpp
class Adapter : public Target, private Adaptee {
    // inherits from both
};
```

Object adapter is more flexible and preferred.

## Key Points

- Converts interface without modifying original classes
- Enables incompatible classes to work together
- Object adapter uses composition (preferred)
- Class adapter uses multiple inheritance
- Often used with legacy code or third-party libraries

## See Also

- [pimpl](pimpl.md) - implementation hiding
- [solid](../solid.md) - Open/Closed Principle
