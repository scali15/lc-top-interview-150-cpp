#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int> nums;
    int output;
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{3,2,3}, 3},
        {{2,2,1,1,1,2,2}, 2}
    };

    for (Test& t : tests) {
        int ret = sol.majorityElement(t.nums);
        cout << "nums = " << VectorUtils::printVec(t.nums) << endl
        << "expected out = " << t.output << endl
        << "got = " << ret << endl << "----------\n";
    }

    return 0;
}
