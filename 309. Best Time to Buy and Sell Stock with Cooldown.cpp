//Runtime: 608 ms, faster than 5.03% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
//Memory Usage: 167.6 MB, less than 7.41% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        if(n == 0) return 0;
        
        //pad 1 transactions, pad 2 days
        vector<vector<int>> dp(n+1, vector(n+2, 0));
        
        for(int i = 1; i <= n; i++){ //transactions
            vector<int> hold(n+2, INT_MIN);
            for(int j = 2; j < n+2; j++){ //days
                dp[i][j] = max(dp[i][j-1], prices[j-2]+hold[j-1]);
                hold[j] = max(hold[j-1], dp[i-1][j-2] - prices[j-2]);
            }
//             cout << "dp" << endl;
//             for(int j = 2; j < n+2; j++){
//                 cout << dp[i][j] << " ";
//             }
//             cout << endl;
            
//             cout << "hold" << endl;
//             for(int j = 2; j < n+2; j++){
//                 cout << hold[j] << " ";
//             }
//             cout << endl;
            
//             cout << "--------" << endl;
        }
        
        return dp[n][n+1];
    }
};
