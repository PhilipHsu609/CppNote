#include <iostream>
#include <map>
#include <memory>
#include <string>

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

void testMultiton() {
    auto instance1 = Multiton<int>::getInstance("key1");
    auto instance2 = Multiton<double>::getInstance("key2");
    auto instance3 = Multiton<int>::getInstance("key1");
    auto instance4 = Multiton<double>::getInstance("key2");

    if (instance1 == instance3) {
        std::cout << "Test passed: instance1 and instance3 are the same." << std::endl;
    } else {
        std::cout << "Test failed: instance1 and instance3 are different." << std::endl;
    }

    if (instance2 == instance4) {
        std::cout << "Test passed: instance2 and instance4 are the same." << std::endl;
    } else {
        std::cout << "Test failed: instance2 and instance4 are different." << std::endl;
    }
}

int main() {
    testMultiton();
    return 0;
}
