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

//recursion + memorization
//Runtime: 20 ms, faster than 75.18% of C++ online submissions for Target Sum.
//Memory Usage: 38.2 MB, less than 23.08% of C++ online submissions for Target Sum.
//time: O(sum*N), space: O(sum*N)
class Solution {
public:
    vector<vector<int>> memo;
    
    int findTargetSumWays(vector<int>& nums, int S, int start) {
        /*
        change the condition to S > 1000, so that 
        memo[start][S+1000] is always valid
        */
        if(start == nums.size() || S > 1000) return S == 0;
        
        if(memo[start][S+1000] != INT_MAX) return memo[start][S+1000];
        
        // cout << S << endl;
        //nums[i] >= 0 for all i
        //sum of nums <= 1000
        //add this determination to avoid overflow
        memo[start][S+1000] = findTargetSumWays(nums, S <= 1000 ? S+nums[start] : INT_MAX, start+1) + 
            findTargetSumWays(nums, S-nums[start], start+1);
        
        return memo[start][S+1000];
    }
    
    int findTargetSumWays(vector<int>& nums, int S) {
        /*
        sum of nums <= 1000,
        so the possible range after adding + or - is [-1000, 1000],
        we map [-1000,1000] to [0,2000] as the index of memo
        */
        memo = vector<vector<int>>(nums.size(), vector(2001, INT_MAX));
        findTargetSumWays(nums, S, 0);
        //if S > 1000, it's impossible for us to make up S by nums
        return S <= 1000 ? memo[0][S+1000] : 0;
    }
};
