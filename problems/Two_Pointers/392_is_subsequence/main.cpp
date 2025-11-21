#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "solution.hpp"

struct Test {
    string s, t;
    bool expected;
};

int main() {
    Solution sol;
    vector<Test> tests = 
    {
        {"abc", "ahbgdc", true},
        {"axc", "ahbgdc", false}
    };
    for (const Test& t : tests){
        bool ret = sol.isSubsequence(t.s, t.t);
        cout << "s = " << t.s << endl
        << "t = " << t.t << endl
        << "expected = " << (t.expected ? "true" : "false") << endl
        << "ret = " << (ret ? "true" : "false") << endl
        << "----------\n";

    }
    return 0;
}
