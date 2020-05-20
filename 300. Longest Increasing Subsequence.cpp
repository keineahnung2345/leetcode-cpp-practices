//DP
//Runtime: 80 ms, faster than 27.26% of C++ online submissions for Longest Increasing Subsequence.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Longest Increasing Subsequence.
//time: O(N^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 1);
        int ans = 1;
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            // cout << dp[i] << " ";
            ans = max(ans, dp[i]);
        }
        // cout << endl;
        
        return ans;
    }
};
