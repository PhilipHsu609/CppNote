---
title: "Multiton Pattern"
---

# Multiton Pattern

Named instances with controlled creation (variation of Singleton).

## Implementation

```cpp
template <typename T>
class Multiton {
  public:
    static std::shared_ptr<Multiton<T>> getInstance(const std::string &key) {
        if (instances.find(key) == instances.end()) {
            instances[key] = std::shared_ptr<Multiton<T>>(new Multiton<T>(key));
        }
        return instances[key];
    }

    void display() const { std::cout << "Instance with key: " << key << std::endl; }

  private:
    Multiton(const std::string &key) : key(key) {}
    std::string key;
    static std::map<std::string, std::shared_ptr<Multiton<T>>> instances;
};

template <typename T>
std::map<std::string, std::shared_ptr<Multiton<T>>> Multiton<T>::instances;
```

## Usage

```cpp
auto instance1 = Multiton<int>::getInstance("key1");
auto instance2 = Multiton<double>::getInstance("key2");
auto instance3 = Multiton<int>::getInstance("key1");
auto instance4 = Multiton<double>::getInstance("key2");

// instance1 == instance3 (same key, same type)
// instance2 == instance4 (same key, same type)
```

## Key Points

- Like Singleton but with named instances
- Each unique key returns the same instance
- Different types maintain separate instance maps
- Private constructor prevents direct instantiation

## See Also

- [singleton](singleton.md) - single instance pattern
- [factory](factory.md) - object creation
