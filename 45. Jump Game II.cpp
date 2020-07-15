//TLE
//91 / 92 test cases passed.
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp(n, INT_MAX);
        
        dp[0] = 0;
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(n-1, i+nums[i]); ++j){
                //we can jump from i to j
                dp[j] = min(dp[j], dp[i]+1);
            }
        }
        
        return dp[n-1];
    }
};
