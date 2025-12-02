#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int> nums, output;
    int k;
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{1,2,3,4,5,6,7}, {5,6,7,1,2,3,4}, 3},
        {{-1,-100,3,99}, {3,99,-1,-100}, 2},
        {{1,2},{2,1},7}
    };

    for (Test& t : tests) {
        cout << "nums = " << VectorUtils::printVec(t.nums) << endl
        << "k = " << t.k << "\nexptected nums = " << VectorUtils::printVec(t.output) << endl;
        sol.rotate(t.nums, t.k);
        cout << "got = " << VectorUtils::printVec(t.nums) << "\n----------\n";
    }

    return 0;
}
