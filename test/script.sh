set -x
clang++ -std=c++17 -DDESIGN=1 test.cpp && ./a.out
clang++ -std=c++17 -DDESIGN=2 test.cpp && ./a.out
clang++ -std=c++17 -DDESIGN=3 test.cpp && ./a.out