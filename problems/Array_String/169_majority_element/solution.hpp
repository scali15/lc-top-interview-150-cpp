#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int majorityElement_verOne(vector<int>& nums) {
        int n = nums.size();

        sort(nums.begin(), nums.end(), less<int>());

        int i = 1;
        int count = 1;
        int bestcount = 0;
        int bestnum = nums[0];

        while (i < n){
            if (nums[i] != nums[i-1]) {
                count = 1;
            }
            else{
                count++;
                if(count > bestcount){
                    bestcount = count;
                    bestnum = nums[i];
                }

            }
            i++;
        }

        return bestnum;
    }
    
    // Boyer-Moore Majority Vote Algorithm
    int majorityElement(vector<int>& nums) {
        int count = 1;
        int candidate = nums[0];

        for (int i = 1; i < nums.size(); i++){
            if (nums[i] == candidate) {
                count++;
            }
            else {
                count --;
            }
            if (count == 0){
                candidate = nums[i];
                count = 1;
            }
        }

        return candidate;
    }
};