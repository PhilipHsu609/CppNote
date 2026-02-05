---
title: "RAII"
---


Resource Acquisition Is Initialization.

## The Pattern

1. Acquire resource in constructor
2. Use resource through object
3. Release resource in destructor (automatic)

```cpp
void writeToFile(const std::string& message) {
    static std::mutex mutex;

    // RAII: lock acquired in constructor
    std::lock_guard<std::mutex> lock(mutex);

    // RAII: file opened in constructor
    std::ofstream file("example.txt");
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file");
    }

    file << message << std::endl;

    // Automatic cleanup when scope exits:
    // 1. file destructor closes file
    // 2. lock destructor releases mutex
    // Even if exception is thrown!
}
```

## Why RAII?

Without RAII (error-prone):
```cpp
void dangerous() {
    int* p = new int[100];
    // ... code that might throw ...
    delete[] p;  // might never run!
}
```

With RAII (safe):
```cpp
void safe() {
    std::unique_ptr<int[]> p(new int[100]);
    // ... code that might throw ...
    // p automatically deleted
}
```

## RAII Wrappers in Standard Library

| Resource | RAII Wrapper |
|----------|--------------|
| Dynamic memory | `unique_ptr`, `shared_ptr` |
| Mutex | `lock_guard`, `unique_lock` |
| File | `fstream` |
| Thread | `jthread` (C++20) |

## Custom RAII

```cpp
class FileHandle {
    FILE* file;
public:
    FileHandle(const char* name) : file(fopen(name, "r")) {
        if (!file) throw std::runtime_error("open failed");
    }
    ~FileHandle() {
        if (file) fclose(file);
    }
    // Delete copy (or implement properly)
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};
```

## Key Points

- Tie resource lifetime to object lifetime
- Destructor guarantees cleanup (even with exceptions)
- Prefer RAII wrappers over manual resource management
- Follow Rule of 5 for custom RAII types
- Core principle of modern C++

## See Also

- [allocation](../memory/allocation.md) - memory management
- [constructors](constructors.md) - acquisition
- [destructors](destructors.md) - release
