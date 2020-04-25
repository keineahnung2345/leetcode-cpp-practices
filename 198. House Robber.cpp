//recursion
//TLE
/**
class Solution {
public:
    int robStart(vector<int>& nums, int s){
        if(s >= nums.size()) return 0;
        return nums[s] + max(robStart(nums, s+2), robStart(nums, s+3));
    }
    int rob(vector<int>& nums) {
        return max(robStart(nums, 0), robStart(nums, 1));
    }
};
**/

//DP, consider 2nd and 3rd next houses
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for House Robber.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for House Robber.

class Solution {
public:
    vector<int> money;
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        else if(nums.size() == 1) return nums[0];
        
        int N = nums.size();
        money = nums;
        //so that we can access money[N]
        money.push_back(0);
        for(int i = N-3; i >= 0; i--){
            money[i] += max(money[i+2], money[i+3]);
        }
        return max(money[0], money[1]);
    }
};

//DP, consider next 2 houses
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for House Robber.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for House Robber.
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        
        vector<int> dp(n);
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for(int i = 2; i < n; i++){
            //if we rob the ith house, we can add dp[i-2] because there is no alear
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        
        return dp[n-1];
    }
};
