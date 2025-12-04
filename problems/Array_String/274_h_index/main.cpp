#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"


struct Test {
    vector<int> citations;
    int output;
};

void addTestsFolder(vector<Test> *tests);

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{3,0,6,1,5}, 3},
        {{1,3,1},1},
        {{0,0,2},1}
    };

    for (Test& t : tests) {
        cout << "citations = " << VectorUtils::printVec(t.citations) << endl
        << "expected output = " << t.output << endl;
        int ret = sol.hIndex(t.citations);
        cout << "got = " << ret << "\n----------\n";
    }

    return 0;
}


void addTestsFolder(vector<Test> *tests) {
    filesystem::path currPath = filesystem::current_path();
    filesystem::path testPath = currPath.parent_path() / "problems/Array_String/274_h_index/tests";

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
