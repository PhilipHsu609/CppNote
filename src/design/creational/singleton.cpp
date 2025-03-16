#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class Singleton {
  private:
    static std::unique_ptr<Singleton> instance;
    static std::once_flag initInstanceFlag;
    Singleton() = default; // Private constructor

  public:
    Singleton(const Singleton &) = delete;            // Delete copy constructor
    Singleton &operator=(const Singleton &) = delete; // Delete copy assignment

    static Singleton *getInstance() {
        std::call_once(initInstanceFlag, []() { instance.reset(new Singleton()); });
        return instance.get();
    }

    void showMessage() { std::cout << "Singleton instance\n"; }
};

// Initialize static members
std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::once_flag Singleton::initInstanceFlag;

int main() {
    auto accessSingleton = []() {
        Singleton *s = Singleton::getInstance();
        s->showMessage();
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(accessSingleton);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return 0;
}
