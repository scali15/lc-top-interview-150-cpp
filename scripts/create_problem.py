#!/usr/bin/env python3
import os
import sys
from datetime import date, datetime
import subprocess

def fetch_leetcode_markdown(slug: str):
    """Call fetch_lc.py and return (markdown, signature)."""

    try:
        result = subprocess.run(
            ["python3", "scripts/fetch_lc.py", slug],
            capture_output=True,
            text=True,
            check=True
        )
        output = result.stdout

        # Split markdown and signature
        if "<SIG_SPLIT>" in output:
            md, sig = output.split("<SIG_SPLIT>", 1)
            return md.strip(), sig.strip()

        # Fallback if signature missing
        return output.strip(), ""

    except Exception as e:
        return f"Failed to fetch problem description: {e}\n", ""



PROBLEMS_ROOT = "problems"

MAIN_TEMPLATE = """#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"


struct Test {{
    // TODO: define fields for this problem
}};

void addTestsFolder(vector<Test> *tests);

int main() {{
    Solution sol;

    vector<Test> tests = 
    {{
        // TODO: define tests
    }};

    for (Test& t : tests) {{
        // TODO: output tests
    }}

    return 0;
}}


void addTestsFolder(vector<Test> *tests) {{
    filesystem::path currPath = filesystem::current_path();
    filesystem::path testPath = currPath.parent_path() / "problems/{CATEGORY}/{PROBLEM}/tests";

    for (const auto& entry : filesystem::directory_iterator(testPath))  {{
        if (entry.is_directory()) {{ throw runtime_error("Error: found unwanted folder in tests folder"); }}
        else if (entry.is_regular_file()) {{
            string testFilePath= entry.path();
            ifstream testFile(testFilePath);

            if (!testFile.is_open()) {{ throw runtime_error("Error opening file: " + testFilePath); }}

            // TODO: format logic according to specific tests

            std::string line;
            std::getline(testFile, line);

            
            testFile.close();
        }}
    }}
}}
"""

SOLUTION_TEMPLATE = """#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


"""

README_TEMPLATE = """# {number}. {title}

Paste the problem description here.

"""

STATUS_TEMPLATE = """done: false
created: {date}, at: {time}
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
    tests_path = os.path.join(problem_path, "tests")

    # Extract problem number + title from folder name
    if "_" in folder:
        number, rest = folder.split("_", 1)
        title = rest.replace("_", " ").title()
    else:
        number = folder
        title = folder.replace("_", " ").title()
    # Fix roman numerals (II, III, IV, VI, VII, VIII, IX, XI, etc.)
    roman_fixes = {
        "Ii": "II",
        "Iii": "III",
        "Iv": "IV",
        "Vi": "VI",
        "Vii": "VII",
        "Viii": "VIII",
        "Ix": "IX",
        "Xi": "XI",
    }
    for k, v in roman_fixes.items():
        title = title.replace(k, v)

    ensure_dir(category_path)
    ensure_dir(problem_path)
    ensure_dir(tests_path)

    # derive LC slug from folder
    slug = folder.split("_", 1)[1].replace("_", "-")

    # Paths
    main_cpp = os.path.join(problem_path, "main.cpp")
    sol_cpp = os.path.join(problem_path, "solution.hpp")
    readme_md = os.path.join(problem_path, "README.md")
    status = os.path.join(problem_path, ".status")


    description, signature = fetch_leetcode_markdown(slug)

    # main.cpp
    if not os.path.exists(main_cpp):
        with open(main_cpp, "w") as f:
            f.write(MAIN_TEMPLATE.format(CATEGORY=category, PROBLEM=folder))
        print(f"Created {main_cpp}")
    else:
        print(f"Exists, skipped: {main_cpp}")

    # solution.cpp
    if not os.path.exists(sol_cpp):
        with open(sol_cpp, "w") as f:
            f.write(SOLUTION_TEMPLATE)
            if signature:
                f.write(signature + "\n")
            else:
                f.write("// TODO: implement solution here\n")
        print(f"Created {sol_cpp}")
    else:
        print(f"Exists, skipped: {sol_cpp}")

    # README.md
    if not os.path.exists(readme_md):
        with open(readme_md, "w") as f:
            f.write(f"# {number}. {title}\n\n")
            f.write(description)

        print(f"Created {readme_md}")

    else:
        print(f"Exists, skipped: {readme_md}")

    # .status file
    if not os.path.exists(status):
        with open(status, "w") as f:
            f.write(STATUS_TEMPLATE.format(
                date=date.today().isoformat(),
                time=datetime.now().strftime('%I:%M:%S %p')
            ))
        print(f"Created {status}")
    else:
        print(f"Exists, skipped: {status}")


if __name__ == "__main__":
    main()
