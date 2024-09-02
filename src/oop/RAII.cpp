/*
    RAII: Resource Acquisition Is Initialization

    Holding a resource is a class invariant, and is tied to object lifetime.

    Three steps
    1. Encapsulate a resource into a class (constructor)
    2. Ues the resource via a local instance of the class
    3. The resource is automatically released when the object gets out of scope
       (destructor)
*/

#include <fstream>
#include <mutex>
#include <stdexcept>
#include <string>

void writeToFile(const std::string &message) {
    // mutex is to protect access to file (mutex is shared accross threads)
    static std::mutex mutex;

    // lock mutex before accessing file
    std::lock_guard<std::mutex> lock(mutex);

    std::ofstream file("example.txt");
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file");
    }

    file << message << std::endl;

    // file is automatically closed when file goes out of scope
    // mutex will be unlocked second when lock goes out of scope
    // (regardless of exception)
}