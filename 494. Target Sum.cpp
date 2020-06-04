//recursion + memorization
//139 / 139 test cases passed, but took too long.
class Solution {
public:
    vector<int> memo;
    
    int findTargetSumWays(vector<int>& nums, int S, int start) {
        if(start == nums.size() || S == INT_MAX) return S == 0;
        
        //nums[i] >= 0 for all i
        //sum of nums <= 1000
        //add this determination to avoid overflow
        memo[start] = findTargetSumWays(nums, S <= 1000 ? S+nums[start] : INT_MAX, start+1) + 
            findTargetSumWays(nums, S-nums[start], start+1);
        
        return memo[start];
    }
    
    int findTargetSumWays(vector<int>& nums, int S) {
        memo = vector<int>(nums.size(), 0);
        
        findTargetSumWays(nums, S, 0);
        
        return memo[0];
    }
};
