//TLE
//183 / 184 test cases passed.
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector(n, 1));
        int ans = INT_MIN;
        
        for(int i = n-1; i >= 0; i--){
            for(int j = i; j < n; j++){
                //[i...j]
                // cout << i << ", " << j << endl;
                if(j == i){
                    //interval of length 1
                    dp[i][j] = nums[i];
                }else{
                    dp[i][j] = nums[i] * dp[i+1][j];
                }
                ans = max(ans, dp[i][j]);
            }
        }
        
        return ans;
    }
};
