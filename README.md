# LeetCode Top 150: C++ Solutions

This repository contains my C++ implementations of the LeetCode Top Interview 150 problems.

Each problem lives in its own folder under `problems/` with:

- README.md - problem description
- solution.cpp - C++ implementation
- main.cpp - small test harness

The project uses CMake to automatically detect and build an executable for each problem.

---

## Project Structure
```
libs/ (useful custom functions and other h files used throughout this project)

problems/
├── Array_String/
│   ├── 88_merge_sorted_array/
│   ├── 27_remove_element/
│   └── ...
├── Two_Pointers/
│   ├── 125_valid_palindrome/
│   └── ...
└── ...
CMakeLists.txt
Progress.md
```

CMake automatically creates one executable per problem folder.

---

## Building & Running a Problem (VS Code Recommended)

1. Open this repo in VS Code.
2. Make sure the CMake Tools and C/C++ extensions are installed.
3. In the bottom status bar, select the problem you want as the active CMake target.
4. Use the CMake Tools buttons:
   - Build
   - Run
   - Debug

You can also build or run targets from the CMake sidebar on the left.

---

## Building from Terminal

mkdir -p build
cd build
cmake ..
cmake --build .

Then run any problem binary, for example:

./remove_element

---

## Requirements

- C++20 compiler (Clang or GCC)
- CMake 3.10+
