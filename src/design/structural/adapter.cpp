#include <iostream>
#include <memory>
#include <string>

// Target interface
class Target {
  public:
    virtual ~Target() = default;
    virtual std::string request() const {
        return "Target: The default target's behavior.";
    }
};

// Adaptee class with a different interface
class Adaptee {
  public:
    std::string specificRequest() const { return ".eetpadA eht fo roivaheb laicepS"; }
};

// Adapter class makes the Adaptee's interface compatible with the Target's interface
class Adapter : public Target {
  private:
    std::shared_ptr<Adaptee> adaptee;

  public:
    Adapter(std::shared_ptr<Adaptee> adaptee) : adaptee(adaptee) {}
    std::string request() const override {
        std::string toReverse = this->adaptee->specificRequest();
        std::reverse(toReverse.begin(), toReverse.end());
        return "Adapter: (TRANSLATED) " + toReverse;
    }
};

void clientCode(const std::shared_ptr<Target> &target) {
    std::cout << target->request() << std::endl;
}

int main() {
    std::cout << "Client: I can work just fine with the Target objects:\n";
    std::shared_ptr<Target> target = std::make_shared<Target>();
    clientCode(target);
    std::cout << "\n";

    std::shared_ptr<Adaptee> adaptee = std::make_shared<Adaptee>();
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't "
                 "understand it:\n";
    std::cout << "Adaptee: " << adaptee->specificRequest() << "\n\n";

    std::cout << "Client: But I can work with it via the Adapter:\n";
    std::shared_ptr<Adapter> adapter = std::make_shared<Adapter>(adaptee);
    clientCode(adapter);

    return 0;
}
