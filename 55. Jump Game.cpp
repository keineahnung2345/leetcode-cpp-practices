//TLE

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int N = nums.size();
        vector<bool> dp(N, false);
        
        dp[N-1] = true;
        for(int i = N-1; i >= 0; i--){
            if(nums[i] >= 1){
                //can reach to one of dp[i+j] which is true
                for(int j = 1; j <= nums[i] && i+j < N; j++){
                    if(dp[i+j]){
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        
        for(int i = 0; i < N; i++){
            if(nums[i] >= 1){
                //can reach to one of dp[i+j] which is true
                for(int j = 1; j <= nums[i] && i-j >= 0; j++){
                    if(dp[i-j]){
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[0];
    }
};
