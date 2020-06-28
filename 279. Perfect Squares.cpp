//TLE
//545 / 588 test cases passed.
class Solution {
public:
    int numSquares(int n) {
        //padding ahead
        vector<int> dp(n+1, 0);
        
        for(int i = 1; i*i <= n; ++i){
            dp[i*i] = 1;
        }
        
        for(int i = 1; i <= n; ++i){
            if(dp[i] == 0){
                //cout << "i: " << i << endl;
                int count = INT_MAX;
                for(int j = 1; j <= i/2; ++j){
                    //cout << j << " and " << i-j << " : " << dp[j] << " and " << dp[i-j] << endl;
                    count = min(count, dp[j] + dp[i-j]);
                }
                dp[i] = count;
                //cout << "i: " << i << ", dp[i]: " << dp[i] << endl;
            }
        }
        
        return dp[n];
    }
};
