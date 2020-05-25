//TLE
//64 / 121 test cases passed.
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K+1, vector(N+1, INT_MAX));
        
        for(int k = 1; k <= K; k++){
            for(int n = 0; n <= N; n++){
                if(k == 1){
                    dp[k][n] = n;
                    continue;
                }
                
                if(n == 0){
                    dp[k][n] = 0;
                    continue;
                }
                
                for(int i = 1; i <= n; i++){
                    dp[k][n] = min(dp[k][n], 
                       /*egg breaks at ith floor, 
                       remain k-1 eggs, 
                       and i-1 floors to try
                       */
                       max(dp[k-1][i-1],
                       /*
                       egg does not break, 
                       remain k eggs, 
                       and n-i floors to try
                       */
                           dp[k][n-i]
                       //drop once
                       )+1);
                    // cout << "i: " << i << ", choose: " << "dp[" << k-1 << "][" << i-1 << "]: " << dp[k-1][i-1] << ", and dp[" << k << "][" << n-i << "]: " << dp[k][n-i] << endl;
                }
                // cout << "(" << k << ", " << n << "): " << dp[k][n] << endl;
            }
        }
                                   
        return dp[K][N];
    }
};
