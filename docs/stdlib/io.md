---
title: "I/O Streams"
---


Input/output operations.

## Standard Streams

```cpp
#include <iostream>

int x;
std::cin >> x;              // buffered stdin

std::cout << x << '\n';     // buffered stdout
std::cerr << "Error\n";     // unbuffered stderr
std::clog << "Log\n";       // buffered stderr
```

## Formatting

```cpp
#include <iomanip>

// Integer bases
std::cout << std::dec << 10;  // decimal: 10
std::cout << std::hex << 10;  // hex: a
std::cout << std::oct << 10;  // octal: 12

// Boolean
std::cout << std::boolalpha << true;   // "true"
std::cout << std::noboolalpha << true; // "1"

// Floating point
std::cout << std::setprecision(2) << std::fixed << 3.14159;      // 3.14
std::cout << std::setprecision(2) << std::scientific << 3.14159; // 3.14e+00

// Alignment
std::cout << std::left << std::setw(10) << "left";
std::cout << std::right << std::setw(10) << "right";

// Quoted strings
std::cout << std::quoted("hello");  // "hello"
```

## File I/O

```cpp
#include <fstream>

// Reading
std::ifstream in("input.txt");
std::string line;
while (std::getline(in, line)) {
    // process line
}

// Writing
std::ofstream out("output.txt", std::ios::app);
out << "content\n";

// Error handling
if (!in.is_open()) {
    std::cerr << "Error: " << std::strerror(errno) << '\n';
}
if (in.bad()) {
    // I/O error occurred
}
```

## Stream Manipulation

```cpp
char c = in.peek();   // peek next char
char c = in.get();    // get and advance

auto pos = in.tellg();  // get position (g = get)
in.seekg(0);            // seek to beginning

out.tellp();            // put position
out.seekp(0);           // seek for writing

in.ignore(100, '\n');   // skip until delimiter
in.clear();             // clear error flags
```

## Flushing

```cpp
// flush forces output to device (slow)
std::cout << std::flush;
std::cout << '\n' << std::flush; // same as std::endl
```

Prefer `'\n'` over `std::endl` for performance.

## Key Points

- `cerr` is unbuffered (immediate output)
- `endl` flushes, `'\n'` doesn't
- Check `is_open()`, `bad()`, `fail()` for errors
- Use `<iomanip>` for formatting
- File streams auto-close in destructor (RAII)

## See Also

- [filesystem](filesystem.md) - file operations
