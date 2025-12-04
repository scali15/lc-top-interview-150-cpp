#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int>nums;
    int output;
};

void addTestsFolder(vector<Test> *tests);

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{2,3,1,1,4},2},
        {{2,3,0,1,4},2}
    };

    addTestsFolder(&tests);

    for (Test& t : tests) {
        cout << "nums = " << VectorUtils::printVec(t.nums) << endl
        << "expected output = " << t.output << endl;
        int ret = sol.jump(t.nums);
        cout << "got = " << ret << "\n----------\n";
    }

    return 0;
}



void addTestsFolder(vector<Test> *tests) {
    filesystem::path currPath = filesystem::current_path();
    filesystem::path testPath = currPath.parent_path() / "problems/Array_String/45_jump_game_ii/tests";

    for (const auto& entry : filesystem::directory_iterator(testPath))  {
        if (entry.is_directory()) { throw runtime_error("Error: found unwanted folder in tests folder"); }
        else if (entry.is_regular_file()) {
            string testFilePath= entry.path();
            ifstream testFile(testFilePath);

            if (!testFile.is_open()) { throw runtime_error("Error opening file: " + testFilePath); }

            std::string list;
            std::getline(testFile, list);
            testFile >> std::ws;    // consume whitespace

            int numJumps;
            testFile >> numJumps;

            vector<int> nums = VectorUtils::parseList(list);
            tests->push_back({nums,numJumps});
            
            
            testFile.close();
        }
    }
}