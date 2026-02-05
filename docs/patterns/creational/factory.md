---
title: "Factory Pattern"
---

# Factory Pattern

Create objects without exposing creation logic.

## Static Factory Methods

```cpp
class Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}

public:
    // Named constructors
    static Point Cartesian(float x, float y) {
        return {x, y};
    }
    static Point Polar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};

auto p1 = Point::Cartesian(3, 4);
auto p2 = Point::Polar(5, 0.927);
```

## Dedicated Factory Class

```cpp
class Point {
public:
    Point(float x, float y);
};

class PointFactory {
public:
    static Point Cartesian(float x, float y) { return {x, y}; }
    static Point Polar(float r, float theta) {
        return {r * cos(theta), r * sin(theta)};
    }
};

auto p = PointFactory::Polar(5, 0.927);
```

## Inner Factory

```cpp
class Point {
    Point(float x, float y);

public:
    class Factory {
    public:
        static Point Cartesian(float x, float y) { return {x, y}; }
        static Point Polar(float r, float theta);
    };
};

auto p = Point::Factory::Cartesian(3, 4);
```

## Abstract Factory

Create families of related objects:

```cpp
class HotDrink {
public:
    virtual void prepare(int volume) = 0;
};

class HotDrinkFactory {
public:
    virtual std::unique_ptr<HotDrink> make() = 0;
};

class TeaFactory : public HotDrinkFactory {
    std::unique_ptr<HotDrink> make() override {
        return std::make_unique<Tea>();
    }
};

class DrinkFactory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> factories;
public:
    DrinkFactory() {
        factories["tea"] = std::make_unique<TeaFactory>();
        factories["coffee"] = std::make_unique<CoffeeFactory>();
    }
    std::unique_ptr<HotDrink> make(const std::string& name) {
        return factories[name]->make();
    }
};
```

## Key Points

- Factory encapsulates object creation
- Static methods: simple, no extra class
- Abstract factory: families of related objects
- Enables dependency injection
- Hides implementation details

## See Also

- [builder](builder.md) - step-by-step construction
- [prototype](prototype.md) - cloning objects
