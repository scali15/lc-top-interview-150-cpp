#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <filesystem>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int> nums;
    bool output;
};

void addTestsFolder(vector<Test> *tests) {
    filesystem::path currPath = filesystem::current_path();
    filesystem::path testPath = currPath.parent_path() / "problems/Array_String/55_jump_game/tests";

    for (const auto& entry : filesystem::directory_iterator(testPath))  {
        if (entry.is_directory()) { throw runtime_error("Error: found unwanted folder in tests folder\n"); }
        else if (entry.is_regular_file()) {
            string testFilePath= entry.path();
            ifstream testFile(testFilePath);

            if (!testFile.is_open()) { throw runtime_error("Error opening file: " + testFilePath); }

            std::string line;
            std::getline(testFile, line);
            vector<int> nums = VectorUtils::parseList(line);

            bool output;
            testFile >> std::ws; // eat all new lines and other whitespace
            testFile >> output;

            tests->push_back({nums, output});
            
            testFile.close();
        }
    }
}

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{2,3,1,1,4},true},
        {{3,2,1,0,4},false}
    };

    addTestsFolder(&tests);

    for (Test& t : tests) {
        cout << "nums = " << VectorUtils::printVec(t.nums) << endl
        << "expected result = " << (t.output ? "true" : "false" ) << endl;
        string ret = (sol.canJump(t.nums) ? "true" : "false");
        cout << "got = " << ret << "\n----------\n"; 
    }

    return 0;
}
