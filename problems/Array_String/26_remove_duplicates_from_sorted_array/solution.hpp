#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return n;

        int k = n;
        int done = 0;

        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[done]) {
                nums[++done] = nums[i];
            }
            else k--;
        }
        return k;
    }
        
};
