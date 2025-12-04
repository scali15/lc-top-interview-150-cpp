#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "solution.hpp"
#include "VectorUtils.h"

struct Test {
    vector<int> prices;
    int output;
};

int main() {
    Solution sol;

    vector<Test> tests = 
    {
        {{7,1,5,3,6,4},7},
        {{1,2,3,4,5},4},
        {{7,6,4,3,1},0}
    };

    for (Test& t : tests) {
        cout << "prices = " << VectorUtils::printVec(t.prices) << endl
        << "output = " << t.output << endl;
        int ret = sol.maxProfit(t.prices);
        cout << "got = " << ret << "\n----------\n";
    }

    return 0;
}
