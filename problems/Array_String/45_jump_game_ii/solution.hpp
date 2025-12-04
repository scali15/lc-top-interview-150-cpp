#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    // approach: have a fronteir var representing reachable, update it with current jump
    // scan each index up to frontier and once its reached, use the jump that leads the furthest
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) { return 0; }
        else if (n==2) { return 1; }    // guarunteed able to reach end of nums

        int frontier = nums[0];
        int bestJump = frontier;
        int i = 1;
        int jumps = 1;


        while(frontier < n-1 && i < n){
            if (i < frontier+1) {
                bestJump= max(bestJump, i + nums[i]);
                i++;
            }
            else {  // 'jump' to current frontier to have next set of idxs in range
                frontier = bestJump;
                jumps++;
            }
        }
        return jumps;
    }
    // eyyyyy looks like I hit the optimal solution on my own this time, and pretty fast to boot
    // complexity analysis: O(n) time, O(1) space
};
