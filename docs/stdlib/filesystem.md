---
title: "std::filesystem"
since: "C++17"
---


Cross-platform file and directory operations.

## Path Operations

```cpp
#include <filesystem>
namespace fs = std::filesystem;

fs::path p = fs::current_path();

p.string();        // full path as string
p.root_path();     // root (e.g., "/" or "C:\")
p.parent_path();   // directory containing this
p.filename();      // just the filename
p.extension();     // file extension
p.stem();          // filename without extension
```

## File Properties

```cpp
fs::path p = "file.txt";

fs::exists(p);           // does it exist?
fs::is_regular_file(p);  // regular file?
fs::is_directory(p);     // directory?
fs::is_symlink(p);       // symbolic link?

auto size = fs::file_size(p);  // size in bytes
auto time = fs::last_write_time(p);
```

## Directory Iteration

```cpp
// Non-recursive
for (const auto& entry : fs::directory_iterator(dir)) {
    entry.path();
    entry.is_regular_file();
}

// Recursive (subdirectories too)
for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    entry.path();
}
```

## Modification Operations

```cpp
fs::create_directory("newdir");
fs::create_directories("a/b/c");  // creates parents

fs::copy("src", "dst");
fs::copy_file("src.txt", "dst.txt");

fs::rename("old", "new");

fs::remove("file");       // single file/empty dir
fs::remove_all("dir");    // recursive delete
```

## Path Manipulation

```cpp
fs::path p = "/home/user";
p /= "docs";          // append with separator
p /= "file.txt";      // "/home/user/docs/file.txt"

fs::path p2 = p.parent_path() / "other.txt";
```

## Key Points

- Cross-platform (Windows, Linux, macOS)
- Based on POSIX semantics
- Operations can throw `filesystem_error`
- Use `error_code` overloads to avoid exceptions
- C++20 adds more features

## See Also

- [io](io.md) - file I/O streams
