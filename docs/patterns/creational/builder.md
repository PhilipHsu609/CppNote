---
title: "Builder Pattern"
---

# Builder Pattern

Construct complex objects step by step.

## Fluent Builder

```cpp
class Person {
    std::string street, city, company, position;
    int income{0};

public:
    static PersonBuilder create();
    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};

class PersonBuilderBase {
protected:
    Person& person;
public:
    PersonBuilderBase(Person& p) : person(p) {}
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
    operator Person() { return std::move(person); }
};

class PersonAddressBuilder : public PersonBuilderBase {
public:
    PersonAddressBuilder& at(std::string street) {
        person.street = street;
        return *this;
    }
    PersonAddressBuilder& in(std::string city) {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase {
public:
    PersonJobBuilder& at(std::string company) {
        person.company = company;
        return *this;
    }
    PersonJobBuilder& earning(int income) {
        person.income = income;
        return *this;
    }
};
```

## Usage

```cpp
Person p = Person::create()
    .lives()
        .at("123 Main St")
        .in("New York")
    .works()
        .at("Google")
        .earning(150000);
```

## Simple Builder

```cpp
class HtmlBuilder {
    HtmlElement root;
public:
    HtmlBuilder(std::string root_name) {
        root.name = root_name;
    }
    HtmlBuilder& add_child(std::string name, std::string text) {
        root.elements.push_back({name, text});
        return *this;  // fluent interface
    }
    std::string str() const { return root.str(); }
};

auto html = HtmlBuilder("ul")
    .add_child("li", "Item 1")
    .add_child("li", "Item 2")
    .str();
```

## Key Points

- Separates construction from representation
- Fluent interface via `return *this`
- Multiple builders for different aspects
- Can switch between builders mid-construction
- Great for objects with many optional parameters

## See Also

- [factory](factory.md) - simpler creation
- [prototype](prototype.md) - cloning existing objects
