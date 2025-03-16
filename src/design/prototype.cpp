#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

/*
   Prototype design pattern is used when the type of objects to create is determined by a
   prototypical instance, which is cloned to produce new objects. This pattern is used to:
    - avoid subclasses of an object creator in the client application, like the factory
      method pattern does.
    - avoid the inherent cost of creating a new object in the standard way (e.g., using
      the 'new' keyword) when it is prohibitively expensive for a given application.
*/

// Prototype interface
class Prototype {
  public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

// Concrete prototype
class ConcretePrototype1 : public Prototype {
  public:
    ConcretePrototype1(const std::string &name) : name_(name) {}
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype1>(*this);
    }
    void print() const override {
        std::cout << "ConcretePrototype1: " << name_ << std::endl;
    }

  private:
    std::string name_;
};

// Concrete prototype
class ConcretePrototype2 : public Prototype {
  public:
    ConcretePrototype2(const std::string &name) : name_(name) {}
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype2>(*this);
    }
    void print() const override {
        std::cout << "ConcretePrototype2: " << name_ << std::endl;
    }

  private:
    std::string name_;
};

// Prototype factory
class PrototypeFactory {
  public:
    PrototypeFactory() {
        prototypes_["type1"] = std::make_unique<ConcretePrototype1>("Type 1");
        prototypes_["type2"] = std::make_unique<ConcretePrototype2>("Type 2");
    }
    std::unique_ptr<Prototype> createPrototype(const std::string &type) {
        return prototypes_[type]->clone();
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<Prototype>> prototypes_;
};

int main() {
    PrototypeFactory factory;
    auto prototype1 = factory.createPrototype("type1");
    auto prototype2 = factory.createPrototype("type2");

    prototype1->print();
    prototype2->print();

    return 0;
}
