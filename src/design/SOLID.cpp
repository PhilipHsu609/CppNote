#include <fmt/core.h>

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

/*
    SOLID Principles
    1. Single Responsibility Principle
    2. Open/Closed Principle
    3. Liskov Substitution Principle
    4. Interface Segregation Principle
    5. Dependency Inversion Principle
*/

namespace Single_Responsibility_Principle {
// Single Responsibility Principle
// A class should have only one reason to change

// Journal class should only be responsible for managing journal entries
struct Journal {
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(const std::string &title) : title(title) {}

    void add_entry(const std::string &entry) {
        static int count = 1;
        entries.push_back(fmt::format("{}: {}", count++, entry));
    }

    // Journal class should not be responsible for saving/loading entries
    // void save(const std::string &filename);
    // void load(const std::string &filename);
};

// Use a separate class to handle saving/loading entries
struct PersistenceManager {
    static void save(const Journal &journal, const std::string &filename) {
        std::ofstream ofs(filename);
        for (const auto &entry : journal.entries) {
            ofs << entry << std::endl;
        }
    }
};

void test() {
    Journal journal("Dear Diary");
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    PersistenceManager pm;
    pm.save(journal, "diary.txt");
}
} // namespace Single_Responsibility_Principle

namespace Open_Closed_Principle {
// Open/Closed Principle
// A class should be open for extension but closed for modification
enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

// Bad design
//  - If we want to filter by size, we need to create a new function
//  - If we want to filter by color and size, we need to create a new function
//  - This violates the Open/Closed Principle
struct ProductFilter {
    std::vector<Product *> by_color(std::vector<Product *> items, Color color) {
        std::vector<Product *> result;
        for (auto &item : items) {
            if (item->color == color) {
                result.push_back(item);
            }
        }
        return result;
    }
};

// Good design

template <typename T>
struct AndSpecification;

template <typename T>
struct Specification {
    virtual bool is_satisfied(T *item) = 0;
    AndSpecification<T> operator&&(Specification<T> &&other) {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T>
struct Filter {
    virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product> {
    std::vector<Product *> filter(std::vector<Product *> items,
                                  Specification<Product> &spec) override {
        std::vector<Product *> result;
        for (auto &item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;
    explicit ColorSpecification(const Color color) : color(color) {}
    bool is_satisfied(Product *item) override { return item->color == color; }
};

struct SizeSpecification : Specification<Product> {
    Size size;
    explicit SizeSpecification(const Size size) : size(size) {}
    bool is_satisfied(Product *item) override { return item->size == size; }
};

template <typename T>
struct AndSpecification : Specification<T> {
    Specification<T> &first;
    Specification<T> &second;
    AndSpecification(Specification<T> &first, Specification<T> &second)
        : first(first), second(second) {}
    bool is_satisfied(T *item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

void test() {
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product house{"House", Color::Blue, Size::Large};

    std::vector<Product *> items{&apple, &tree, &house};

    // Bad design
    ProductFilter pf;
    for (const auto &item : pf.by_color(items, Color::Green)) {
        fmt::print("{} is green\n", item->name);
    }

    // Good design
    BetterFilter bf;
    ColorSpecification green(Color::Green);
    for (const auto &item : bf.filter(items, green)) {
        fmt::print("{} is green\n", item->name);
    }

    auto green_and_large =
        ColorSpecification(Color::Green) && SizeSpecification(Size::Large);
    for (const auto &item : bf.filter(items, green_and_large)) {
        fmt::print("{} is green and large\n", item->name);
    }
}
} // namespace Open_Closed_Principle

namespace Liskov_Substitution_Principle {
// Liskov Substitution Principle
// Objects in a program should be replaceable with instances of their subtypes
// without altering the correctness of the program

// Broken example
//  - Square is a subclass of Rectangle
//  - Square has a set_side method that sets both width and height
//  - This violates the Liskov Substitution Principle
class Rectangle {
  protected:
    int width, height;

  public:
    Rectangle(int width, int height) : width(width), height(height) {}

    virtual int get_width() const { return width; }
    virtual void set_width(int width) { this->width = width; }
    virtual int get_height() const { return height; }
    virtual void set_height(int height) { this->height = height; }

    int area() const { return width * height; }
};

class Square : public Rectangle {
  public:
    Square(int size) : Rectangle(size, size) {}
    void set_width(int width) override { this->width = this->height = width; }
    void set_height(int height) override { this->width = this->height = height; }
};

void process(Rectangle &r) {
    int w = r.get_width();
    r.set_height(10); // For a square, this will set both width and height to 10

    fmt::print("Expected area = {}\n", w * 10);
    fmt::print("Actual area = {}\n", r.area());
}

void test() {
    Rectangle r{3, 4};
    process(r);

    Square s{5};
    process(s);
}
} // namespace Liskov_Substitution_Principle

namespace Interface_Segregation_Principle {
// Interface Segregation Principle
// A client should never be forced to implement an interface that it doesn't use

struct Document {};

// Bad design
struct IMachine {
    // This violates the Interface Segregation Principle
    // Not all machines can print, scan, and fax
    virtual void print(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
};

// Better design
struct IPrinter {
    virtual void print(Document &doc) = 0;
};

struct IScanner {
    virtual void scan(Document &doc) = 0;
};

struct IFax {
    virtual void fax(Document &doc) = 0;
};

struct INewMachine : IPrinter, IScanner {};

struct Printer : IPrinter {
    void print([[maybe_unused]] Document &doc) override {}
};

struct Scanner : IScanner {
    void scan([[maybe_unused]] Document &doc) override {}
};

struct Machine : INewMachine {
    IPrinter &printer;
    IScanner &scanner;
    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}
    void print(Document &doc) override { printer.print(doc); }
    void scan(Document &doc) override { scanner.scan(doc); }
};

void test() {
    Document doc;
    Printer printer;
    Scanner scanner;
    Machine machine(printer, scanner);
    machine.print(doc);
    machine.scan(doc);
}

} // namespace Interface_Segregation_Principle

namespace Dependency_Inversion_Principle {
// Dependency Inversion Principle
// High-level modules should not depend on low-level modules. Both should depend on
// abstractions. Abstractions should not depend on details. Details should depend on
// abstractions.

enum class Relationship { parent, child, sibling };

struct Person {
    std::string name;
};

struct RelationshipBrowser {
    virtual std::vector<Person> find_all_children_of(const std::string &name) = 0;
};

// Low-level module: storage
struct Relationships : RelationshipBrowser {
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person &parent, const Person &child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    std::vector<Person> find_all_children_of(const std::string &name) override {
        std::vector<Person> result;
        for (auto &&[first, rel, second] : relations) {
            if (first.name == name && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

// High-level module: research
struct Research {
    // This violates the Dependency Inversion Principle.
    // Research depends on Relationships, a low-level module.
    // If Relationships changes, Research will also need to change
    //     e.g. if we change the relations to a map.
    // We should depend on abstractions, not concrete implementations.
    Research(Relationships &relationships) {
        for (auto &&[first, rel, second] : relationships.relations) {
            if (first.name == "John" && rel == Relationship::parent) {
                fmt::print("{} has a child named {}\n", first.name, second.name);
            }
        }
    }

    // Better design
    Research(RelationshipBrowser &browser) {
        for (const auto &child : browser.find_all_children_of("John")) {
            fmt::print("John has a child named {}\n", child.name);
        }
    }
};

void test() {
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);
}
} // namespace Dependency_Inversion_Principle

int main() {
    Single_Responsibility_Principle::test();
    Open_Closed_Principle::test();
    Liskov_Substitution_Principle::test();
    Interface_Segregation_Principle::test();
    Dependency_Inversion_Principle::test();
    return 0;
}