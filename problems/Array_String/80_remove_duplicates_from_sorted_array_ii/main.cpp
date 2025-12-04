#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int> nums;
    int expected_k;
    vector<int> expected_nums;
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{1,1,1,2,2,3},5,{1,1,2,2,3,10001}},
        {{0,0,1,1,1,1,2,3,3},7,{0,0,1,1,2,3,3,10001,10001}}
    };
    

    for (Test& t : tests) {
        cout << "nums = " << VectorUtils::printVec(t.nums) << endl;
        int k = sol.removeDuplicates(t.nums);
        cout << "expected = " << VectorUtils::printVec(t.expected_nums) << ", k = " << t.expected_k << endl;
        cout << "got = " << VectorUtils::printVec(t.nums) << ", k = " << k << "\n--------\n";

    }

    return 0;
}
