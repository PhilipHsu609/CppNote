/*
    File system
    - Based on POSIX
    - Work on Windows, Linux, MacOS, etc.
*/

#include <cstdint>    // uintmax_t
#include <filesystem> // fs
#include <fmt/core.h> // print

namespace fs = std::filesystem;

void test() {
    fs::path cur{fs::current_path()};

    fmt::print("Current path: {}\n", cur.string());
    fmt::print("Root path: {}\n", cur.root_path().string());
    fmt::print("Parent path: {}\n", cur.parent_path().string());
    fmt::print("Filename: {}\n", cur.filename().string());
    fmt::print("Extension: {}\n", cur.extension().string());

    if (fs::exists(cur)) {
        fmt::print("Exists\n");
    }

    if (fs::is_directory(cur)) {
        fmt::print("Is directory\n");
    }

    if (fs::is_regular_file(cur)) {
        fmt::print("Is regular file\n");
    }

    if (fs::is_symlink(cur)) {
        fmt::print("Is symlink\n");
    }

    std::uintmax_t size = fs::file_size(cur);

    // Iterator
    for (auto &p : fs::directory_iterator(cur)) {
        fmt::print("{}", p.path().string());
    }

    // Recursive iterator
    for (auto &p : fs::recursive_directory_iterator(cur)) {
        fmt::print("{}", p.path().string());
    }

    // Modify
    fs::create_directory("dir");
    fs::copy("file", "file2");
    fs::copy_file("file", "file2");
    fs::remove("file");
    fs::remove_all("dir");
}