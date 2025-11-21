#include <iostream>
#include <vector>

#include "solution.hpp"
#include "VectorUtils.h"

using namespace std;

struct Test{
    vector<int> nums1;
    int m;
    vector<int> nums2;
    int n;
    vector<int> expected;
};

int main() {
    Solution sol;
    vector<Test> tests = 
    {
        { {1,2,3,0,0,0}, 3, {2,5,6}, 3, {1,2,2,3,5,6} },
        { {1}, 1, {}, 0, {1} },
        { {0}, 0, {1}, 1, {1} }
    };

    for (Test test : tests){
            cout << "nums1 = " << VectorUtils::printVec(test.nums1) << endl;
            cout << "nums2 = " << VectorUtils::printVec(test.nums2) << endl;
            cout << "m = " << test.m << ", n = " << test.n << endl;

            cout << "expected = " << VectorUtils::printVec(test.expected) << endl;
            sol.merge(test.nums1, test.m, test.nums2, test.n);

            cout << "ret = " <<  VectorUtils::printVec(test.nums1) << endl << endl;
    }

    return 0;
}
