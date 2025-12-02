#include <iostream>
#include <vector>
#include <string>

#include "solution.hpp"
#include "VectorUtils.h"

using namespace std;

struct Test {
    vector<int> nums;
    int expected_k;
    vector<int> expected_nums;
    
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{1,1,2}, 2, {1,2,101}},
        {{0,0,1,1,1,2,2,3,3,4},5,{0,1,2,3,4,101,101,101,101,101}}
    };

    for (Test& test : tests) {
        int k = sol.removeDuplicates(test.nums);
        cout << "expected nums = " << VectorUtils::printVec(test.expected_nums) << ", " << "expected k = " << test.expected_k
        << "\nreturned nums = " << VectorUtils::printVec(test.nums) << ", returned k = " << k << "\n---------\n";
    }

    return 0;
}
