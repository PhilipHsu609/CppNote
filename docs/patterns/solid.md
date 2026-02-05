---
title: "SOLID Principles"
---

# SOLID Principles

Five design principles for maintainable OOP code.

## S - Single Responsibility Principle

A class should have only one reason to change.

```cpp
// BAD: Journal handles both data and persistence
struct Journal {
    std::vector<std::string> entries;
    void add_entry(const std::string& entry);
    void save(const std::string& filename);  // ❌ Not its job
};

// GOOD: Separate concerns
struct Journal {
    std::vector<std::string> entries;
    void add_entry(const std::string& entry);
};

struct PersistenceManager {
    static void save(const Journal& j, const std::string& filename);
};
```

## O - Open/Closed Principle

Open for extension, closed for modification.

```cpp
// BAD: Adding filters requires modifying ProductFilter
struct ProductFilter {
    std::vector<Product*> by_color(/*...*/);
    std::vector<Product*> by_size(/*...*/);     // ❌ Had to modify
    std::vector<Product*> by_color_and_size(/*...*/); // ❌ Again
};

// GOOD: Extend via new specifications
template <typename T>
struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

struct ColorSpec : Specification<Product> {
    Color color;
    bool is_satisfied(Product* p) override { return p->color == color; }
};

struct SizeSpec : Specification<Product> { /* ... */ };

// Combine specs without modifying existing code
auto green_large = ColorSpec(Green) && SizeSpec(Large);
```

## L - Liskov Substitution Principle

Subtypes must be substitutable for their base types.

```cpp
// BAD: Square violates Rectangle's contract
class Rectangle {
public:
    virtual void set_width(int w) { width = w; }
    virtual void set_height(int h) { height = h; }
    int area() { return width * height; }
};

class Square : public Rectangle {
    void set_width(int w) override { width = height = w; }  // ❌
    void set_height(int h) override { width = height = h; } // ❌
};

void process(Rectangle& r) {
    r.set_width(5);
    r.set_height(10);
    assert(r.area() == 50);  // Fails for Square!
}
```

## I - Interface Segregation Principle

Clients shouldn't depend on interfaces they don't use.

```cpp
// BAD: Printer forced to implement fax
struct IMachine {
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;  // ❌ Not all machines fax
};

// GOOD: Separate interfaces
struct IPrinter { virtual void print() = 0; };
struct IScanner { virtual void scan() = 0; };
struct IFax { virtual void fax() = 0; };

struct MultiFunctionDevice : IPrinter, IScanner { /* ... */ };
struct SimplePrinter : IPrinter { /* ... */ };
```

## D - Dependency Inversion Principle

Depend on abstractions, not concretions.

```cpp
// BAD: High-level depends on low-level implementation
struct Research {
    Research(Relationships& r) {
        for (auto& [p, rel, c] : r.relations) { /* ... */ }  // ❌
    }
};

// GOOD: Depend on abstraction
struct RelationshipBrowser {
    virtual std::vector<Person> find_children(const std::string& name) = 0;
};

struct Research {
    Research(RelationshipBrowser& browser) {
        for (auto& child : browser.find_children("John")) { /* ... */ }
    }
};
```

## Key Points

| Principle | Summary |
|-----------|---------|
| SRP | One class, one responsibility |
| OCP | Extend behavior without modifying existing code |
| LSP | Subclasses must honor base class contracts |
| ISP | Many specific interfaces > one general interface |
| DIP | High-level code shouldn't depend on low-level details |

## See Also

- [factory](creational/factory.md) - DIP in action
- [adapter](structural/adapter.md) - OCP via wrapping
