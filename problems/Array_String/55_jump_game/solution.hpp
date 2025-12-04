#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    // topics :array, dynamic programming, greedy

    /**
     * approach: track distance from the end
     * not sure what to do
     * hmmmm
     * brute force - depth first search problem space
     */
        bool canJumpv1(vector<int>& nums) {
            if (nums.size() == 1) { return true; }

            int n = nums.size();
            stack<int> st = {};
            
            st.push(0);

            while (!st.empty()) {
                int curr = st.top();
                if (curr >= n) {
                    st.pop();
                    continue;
                }
                else if (curr == n-1) return true; 
                int possible_jumps = nums[curr];
                st.pop(); 
                for (int i = 1; i <= possible_jumps; i++){ st.push(curr+i); }
            }

            return false;
        }
        // annnnnd that works but it exceeded the time limit on LC...
        // makes sense, this is worst case O(n^2) at least but probably worse
        // also jump lengths up to 10000, so memory footprint with stack is huge.

        // okay with a little help from ai the complexity of this is about O(k^n) where k is the average jump length,
        // so yeah much worse

    // TODO: make this faster
    // idea: prune visited indexes and dont pus invalid indexes

    // sidequest: implement building test cases from text files for this project to test those massive LC cases

    bool canJumpv2(vector<int>& nums) {
        if (nums.size() == 1) { return true; }

            int n = nums.size();
            stack<int> st = {};
            vector<bool> visited(n, false);
            
            st.push(0);

            while (!st.empty()) {
                int curr = st.top();
                if (curr == n-1) return true; 
                int possible_jumps = nums[curr];
                st.pop(); 
                visited[curr] = true;
                
                for (int i = 1; i <= possible_jumps; i++){ 
                    int next = curr+i;
                    if (next >= n) break;

                    if (!visited[next]) st.push(next); 
                }
            }

            return false;
    }
    // first working solution!
    // lets see, time complexity now is more like O(maxJump * n), space is O(maxJump)
    // and since n <= 10^4 and jump <= 10^5, maxjump is 10x, a scalaer, 
    // and so this is simplified to O(n^2) and O(n) respsectively
    // anyway, it only beats 15% though and 7% in memory, so now as usual 
    // I'll try to implement the optimal solution from a high level description 


    // From chagGPT:
    // "As you walk left → right, keep track of the farthest index you can reach so far, and use that to determine whether the next index is even worth evaluating."
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int furthest = 0;

        for (int i = 0; i < n && i <= furthest; i++){
            furthest = max(furthest, i + nums[i]);
            if (furthest >= n-1) { return true; }
        }
        return false;
    }

    // yikes that was way too simple. At least I learned a bunch about filesystem.
    // Complexity here is linear time and constant space, which is optimal

};
