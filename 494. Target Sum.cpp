//recursion
//Runtime: 1452 ms, faster than 10.35% of C++ online submissions for Target Sum.
//Memory Usage: 9.2 MB, less than 38.46% of C++ online submissions for Target Sum.
//time: O(2^N), space: O(N)
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S, int start) {
        if(start == nums.size() || S == INT_MAX) return S == 0;
        
        //nums[i] >= 0 for all i
        //sum of nums <= 1000
        //add this determination to avoid overflow
        return findTargetSumWays(nums, S <= 1000 ? S+nums[start] : INT_MAX, start+1) + 
            findTargetSumWays(nums, S-nums[start], start+1);
    }
    
    int findTargetSumWays(vector<int>& nums, int S) {
        return findTargetSumWays(nums, S, 0);
    }
};
