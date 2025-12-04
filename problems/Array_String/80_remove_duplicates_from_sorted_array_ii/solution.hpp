class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return n;

        int k = n;
        int done = 1;

        for (int i = 2; i < n; i++) {
            if (nums[i] != nums[done] || nums[i] != nums[done-1]) { nums[++done] = nums[i]; }
            else { k--; }
        }
        return k;
    }
};
