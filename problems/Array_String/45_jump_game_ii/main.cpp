#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

void addTestsFolder(vector<Test> *tests) {
    filesystem::path currPath = filesystem::current_path();
    filesystem::path testPath = currPath.parent_path() / "problems/Array_String/45_jump_game_ii/tests";

    for (const auto& entry : filesystem::directory_iterator(testPath))  {
        if (entry.is_directory()) { throw runtime_error("Error: found unwanted folder in tests folder"); }
        else if (entry.is_regular_file()) {
            string testFilePath= entry.path();
            ifstream testFile(testFilePath);

            if (!testFile.is_open()) { throw runtime_error("Error opening file: " + testFilePath); }

            // TODO: format logic according to specific tests

            std::string line;
            std::getline(testFile, line);

            
            testFile.close();
        }
    }
}

struct Test {
    vector<int>nums;
    int output;
};


int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{2,3,1,1,4},2},
        {{2,3,0,1,4},2}
    };

    // add if using tests folder (for huge test cases)
    // addTestsFolder(&tests);

    for (Test& t : tests) {
        // TODO: output tests
    }

    return 0;
}
