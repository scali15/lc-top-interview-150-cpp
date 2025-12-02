#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // First instinct attempt, linear time and space. Not sure how to do constant space yet.
    void rotate_v1(vector<int>& nums, int k) {
        int read = 0;
        int write = k;
        vector<int> cp = nums;
        int n = nums.size();

        while (read < n) {
            if (write < n){
                nums[write] = cp[read];
                write++;
                read++;
            }
            else write = write % n;
        }
    }

    // My implementation after looking up a high level (no code) explanation of the reverse-rotate trick.
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};