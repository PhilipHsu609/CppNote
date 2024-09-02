#include <cerrno>   // errno
#include <cstring>  // strerror
#include <fstream>  // ifstream, ofstream
#include <iomanip>  // hex, boolalpha, setprecision, setw
#include <iostream> // cout, cin, cerr, clog
#include <string>   // string

void io() {
    int x;
    std::cin >> x;
    std::cout << "x = " << x << '\n'; // buffered stdout output

    std::cerr << "Error message\n"; // unbuffered stderr output
    std::clog << "Log message\n";   // buffered stderr output

    // flush and endl force the program to synchronize with the terminal -> slow
    std::cout << std::flush;         // flushes the output buffer
    std::cout << '\n' << std::flush; // equivalend to std::cout << std::endl

    // Integral representation
    std::cout << std::dec << 10 << '\n'; // decimal
    std::cout << std::hex << 10 << '\n'; // hexadecimal
    std::cout << std::oct << 10 << '\n'; // octal

    // true/false
    std::cout << std::boolalpha << true << '\n';    // true
    std::cout << std::noboolalpha << false << '\n'; // 0

    // Floating point representation
    std::cout << std::setprecision(2) << std::fixed << 3.14159 << '\n';      // 3.14
    std::cout << std::setprecision(2) << std::scientific << 3.14159 << '\n'; // 3.14e+00

    // Alignment
    std::cout << std::left << std::setw(10) << "left" << '\n';   // left
    std::cout << std::right << std::setw(10) << "right" << '\n'; // right

    // quoted string
    std::cout << std::quoted("quoted") << '\n'; // "quoted"
}

void file_io() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt", std::ios::app | std::ios::out);
    std::string line;

    // proper way to read a file line by line
    while (std::getline(in, line)) {
        // process
    }

    // with meaningful eerror messages
    if (!in.is_open()) {
        std::cerr << "Error while opening: " << std::strerror(errno) << '\n';
    }
    while (std::getline(in, line)) {
        // process
    }
    if (in.bad()) {
        std::cerr << "Error while reading: " << std::strerror(errno) << '\n';
    }

    // manipulate file pointer
    char c;
    c = in.peek(); // peek the next character
    c = in.get();  // get and advance the file pointer

    int offset;
    offset = out.tellp(); // p for put
    offset = in.tellg();  // g for get

    out.seekp(0); // move to the beginning of the file
    in.seekg(0);  // move to the beginning of the file

    // ignore characters until a delimiter is found
    in.ignore(100, '\n');

    // redirect
    std::cout << in.rdbuf(); // redirect the content of the file to the standard output

    // unset failbits
    in.clear();
}