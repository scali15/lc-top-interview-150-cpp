#!/usr/bin/env python3
import os
import sys
from datetime import date

PROBLEMS_ROOT = "problems"

MAIN_TEMPLATE = """#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    // TODO: define fields for this problem
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        // TODO: define tests
    };

    for (Test& t : tests) {
        // TODO: output tests
    }

    return 0;
}
"""

SOLUTION_TEMPLATE = """#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // TODO: implement solution here
};
"""

README_TEMPLATE = """# {number}. {title}

Paste the problem description here.

"""

STATUS_TEMPLATE = """done: false
created: {date}
completed:
"""

def ensure_dir(path):
    if not os.path.exists(path):
        os.makedirs(path)


def main():
    if len(sys.argv) != 3:
        print("Usage: create_problem.py <Category> <ProblemFolderName>")
        print("Example:")
        print("  ./scripts/create_problem.py Two_Pointers 392_is_subsequence")
        sys.exit(1)

    category = sys.argv[1]
    folder = sys.argv[2]

    category_path = os.path.join(PROBLEMS_ROOT, category)
    problem_path = os.path.join(category_path, folder)

    # Extract problem number + title from folder name
    if "_" in folder:
        number, rest = folder.split("_", 1)
        title = rest.replace("_", " ").title()
    else:
        number = folder
        title = folder.replace("_", " ").title()

    ensure_dir(category_path)
    ensure_dir(problem_path)

    # Paths
    main_cpp = os.path.join(problem_path, "main.cpp")
    sol_cpp = os.path.join(problem_path, "solution.hpp")
    readme_md = os.path.join(problem_path, "README.md")
    status = os.path.join(problem_path, ".status")


    # main.cpp
    if not os.path.exists(main_cpp):
        with open(main_cpp, "w") as f:
            f.write(MAIN_TEMPLATE)
        print(f"Created {main_cpp}")
    else:
        print(f"Exists, skipped: {main_cpp}")

    # solution.cpp
    if not os.path.exists(sol_cpp):
        with open(sol_cpp, "w") as f:
            f.write(SOLUTION_TEMPLATE)
        print(f"Created {sol_cpp}")
    else:
        print(f"Exists, skipped: {sol_cpp}")

    # README.md
    if not os.path.exists(readme_md):
        with open(readme_md, "w") as f:
            f.write(README_TEMPLATE.format(number=number, title=title))
        print(f"Created {readme_md}")
    else:
        print(f"Exists, skipped: {readme_md}")

     # .status file
    if not os.path.exists(status):
        with open(status, "w") as f:
            f.write(STATUS_TEMPLATE.format(date=date.today().isoformat()))
        print(f"Created {status}")
    else:
        print(f"Exists, skipped: {status}")

    print(f"Created problem at: {problem_path}")


if __name__ == "__main__":
    main()
