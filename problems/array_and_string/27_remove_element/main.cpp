#include <iostream>
#include <vector>

#include "solution.cpp"
#include "VectorUtils.h"

using namespace std;

struct Test {
    vector<int> nums;
    int val;
    vector<int> expected;
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        { {3,2,2,3}, 3, {2,2} },
        { {0,1,2,2,3,0,4,2}, 2, {0,0,1,3,4} }
    };

    for (Test test : tests){
            cout << "nums = " << VectorUtils::printVec(test.nums) << endl;
            cout << "val = " << test.val << endl;
            cout << "expected = " << VectorUtils::printVec(test.expected) << ", len = " << test.expected.size() << endl;

            int len = sol.removeElement(test.nums, test.val);

            cout << "ret = " <<  VectorUtils::printVec(test.nums)  << ", len = " << len << "\n\n";
    }

    return 0;
}
