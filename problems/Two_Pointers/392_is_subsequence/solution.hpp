#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_ptr, t_ptr, s_len, t_len;
        s_ptr = 0; t_ptr = 0; 
        s_len = s.size(); t_len = t.size();

        while (s_ptr < s_len && t_ptr < t_len){
            if (s[s_ptr] == t[t_ptr]) {
                s_ptr++;
            }
            t_ptr++;
        }

        return s_ptr == s_len;
    }
};
