---
title: "Prototype Pattern"
---


Create new objects by cloning existing ones.

## Basic Prototype

```cpp
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

class ConcretePrototype : public Prototype {
    std::string name_;
public:
    ConcretePrototype(const std::string& name) : name_(name) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this);
    }

    void print() const override {
        std::cout << "ConcretePrototype: " << name_ << "\n";
    }
};
```

## Prototype Factory

```cpp
class PrototypeFactory {
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes_;

public:
    PrototypeFactory() {
        prototypes_["type1"] = std::make_unique<ConcretePrototype1>("Default1");
        prototypes_["type2"] = std::make_unique<ConcretePrototype2>("Default2");
    }

    std::unique_ptr<Prototype> create(const std::string& type) {
        return prototypes_[type]->clone();
    }
};
```

## Usage

```cpp
PrototypeFactory factory;

auto obj1 = factory.create("type1");
auto obj2 = factory.create("type1");  // independent clone

obj1->print();
obj2->print();
```

## When to Use

- Creating objects is expensive (database, network)
- Objects have many shared properties
- Need to avoid subclasses of factories
- Runtime configuration of which classes to instantiate

## Key Points

- Clone method creates deep copy
- Prototype registry stores clonable templates
- Avoids cost of standard construction
- Each clone is independent
- Implement proper copy semantics

## See Also

- [factory](factory.md) - alternative creation pattern
- [builder](builder.md) - step-by-step construction
