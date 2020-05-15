//TLE
//94 / 109 test cases passed.
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        
        vector<vector<int>> dp(n, vector(n, INT_MIN));
        int ans = INT_MIN;
        
        //i: start
        for(int i = n-1; i >= 0; i--){
            //j: end
            //the upper bound(exclusive) changes from n to i+n -> circular
            for(int j = i; j < i+n; j++){
                //length 1 subarray
                if(i == j){
                    dp[i][j%n] = A[i];
                }else{
                    dp[i][j%n] = max({dp[i][j%n], 
                                    (dp[(i+1)%n][j%n] == INT_MIN) ? INT_MIN : A[i]+dp[(i+1)%n][j%n], 
                                    (dp[i][(j-1+n)%n] == INT_MIN) ? INT_MIN : dp[i][(j-1+n)%n]+A[j%n]
                                    });
                }
                
                // if(dp[i][j%n] > ans){
                //     cout << "[" << i << ", " << j << "]: " << dp[i][j%n] << endl;
                // }
                ans = max(ans, dp[i][j%n]);
            }
        }
        
        return ans;
    }
};
