#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace Basic_Factory {
class Point {
    Point(float x, float y) : x(x), y(y) {}
    [[maybe_unused]] float x, y;

  public:
    // Expose the factory methods inside the product class
    static Point NewCartesian(float x, float y) { return {x, y}; }
    static Point NewPolar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};

void test() {
    [[maybe_unused]] Point p = Point::NewCartesian(1, 2);
    [[maybe_unused]] Point p2 = Point::NewPolar(1, 2);
}
} // namespace Basic_Factory

namespace Basic_Factory_2 {
class Point {
    [[maybe_unused]] float x, y;

  public:
    // We have to make the constructor public to let the factory class create
    // the object.
    // Or we can make the factory class a friend of the product class. But this violates
    // the Open-Closed Principle.
    Point(float x, float y) : x(x), y(y) {}
};

// A dedicated factory class
class PointFactory {
  public:
    static Point NewCartesian(float x, float y) { return {x, y}; }
    static Point NewPolar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};

void test() {
    [[maybe_unused]] Point p = PointFactory::NewCartesian(1, 2);
    [[maybe_unused]] Point p2 = PointFactory::NewPolar(1, 2);
}
} // namespace Basic_Factory_2

namespace Inner_Factory {
class Point {
    [[maybe_unused]] float x, y;

    Point(float x, float y) : x(x), y(y) {}

  public:
    // Expose the factory methods inside the product class.
    // Or we can make the factory a private class inside the product class, and expose
    // a static method to create the factory object.
    class Factory {
      public:
        static Point NewCartesian(float x, float y) { return {x, y}; }
        static Point NewPolar(float r, float theta) {
            return {r * cos(theta), r * sin(theta)};
        }
    };
};

void test() {
    [[maybe_unused]] Point p = Point::Factory::NewCartesian(1, 2);
    [[maybe_unused]] Point p2 = Point::Factory::NewPolar(1, 2);
}
} // namespace Inner_Factory

namespace Abstract_Factory {
class HotDrink {
  public:
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

class Tea : public HotDrink {
  public:
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour " << volume
                  << "ml, add some lemon\n";
    }
};

class Coffee : public HotDrink {
  public:
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour " << volume
                  << "ml, add cream and sugar\n";
    }
};

class HotDrinkFactory {
  public:
    virtual ~HotDrinkFactory() = default;
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

class TeaFactory : public HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override { return std::make_unique<Tea>(); }
};

class CoffeeFactory : public HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override { return std::make_unique<Coffee>(); }
};

class DrinkFactory {
    std::unordered_map<std::string, std::unique_ptr<HotDrinkFactory>> factories;

  public:
    DrinkFactory() {
        factories["coffee"] = std::make_unique<CoffeeFactory>();
        factories["tea"] = std::make_unique<TeaFactory>();
    }
    std::unique_ptr<HotDrink> make_drink(const std::string &name) {
        auto drink = factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

class DrinkFactory2 {
    std::unordered_map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

  public:
    DrinkFactory2() {
        factories["coffee"] = [] {
            auto coffee = std::make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
        factories["tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
    }
    std::unique_ptr<HotDrink> make_drink(const std::string &name) {
        return factories[name]();
    }
};

void test() {
    DrinkFactory df;
    auto drink = df.make_drink("tea");
}
} // namespace Abstract_Factory