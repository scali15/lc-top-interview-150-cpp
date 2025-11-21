#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int numRemoved = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == val){
                nums[i] = 51;
                numRemoved++;
            }
        }
        sort(nums.begin(), nums.end(), less<int>());
        return n - numRemoved;  // k
    }
};                                                                                                                                                                                                                                                                        
