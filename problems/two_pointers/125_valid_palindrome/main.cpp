#include <iostream>
#include <string>
#include <vector>

#include "solution.cpp"

using namespace std;

struct Test {
    string s;
    bool expected;
};

int main() {
    Solution sol;
    vector<Test> tests = 
    {
        { "A man, a plan, a canal: Panama", true },
        { "race a car", false },
        { " ", true },
        { "0P", false },
        { "abba", true },
        { "abcba", true },
        { "abc", false }
    };

    for (Test t : tests){
        cout << "input:     \"" << t.s << "\"\n"
         << "expected:  " << (t.expected ? "true" : "false") << "\n"
         << "actual:    " << (sol.isPalindrome(t.s) ? "true" : "false") << "\n"
         << "----------\n";
    }

    return 0;
}
