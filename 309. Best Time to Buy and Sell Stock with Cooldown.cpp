//inspired by 188. Best Time to Buy and Sell Stock IV.cpp
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

//Finite state machine
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75928/Share-my-DP-solution-(By-State-Machine-Thinking)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
//Memory Usage: 11.5 MB, less than 7.41% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n == 0) return 0;
        vector<int> s0(n, 0); //after "sell+rest"(s2) or "s0", do "rest" or "buy"
        vector<int> s1(n, 0); //after "buy"(s0) or "s1", do "rest" or "sell"
        vector<int> s2(n, 0); //after "sell"(s1), do "rest"
        
        s0[0] = 0;
        s1[0] = -prices[0];
        s2[0] = 0;
        
        for(int i = 1; i < n; i++){
            s0[i] = max(s0[i-1], s2[i-1]);
            s1[i] = max(s1[i-1], s0[i-1]-prices[i]);
            s2[i] = s1[i-1]+prices[i];
        }
        
        return max(s0[n-1], s2[n-1]);
    }
};

//1-D DP
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75927/Share-my-thinking-process
//Runtime: 4 ms, faster than 60.34% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
//Memory Usage: 11.5 MB, less than 7.41% of C++ online submissions for Best Time to Buy and Sell Stock with Cooldown.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n == 0) return 0;
        //padding
        vector<int> buy(n+1, 0);
        vector<int> sell(n+1, 0);
        prices.insert(prices.begin(), 0);
        
        buy[1] = -prices[1];
        
        for(int i = 2; i <= n; i++){
            buy[i] = max(buy[i-1], sell[i-2]-prices[i]);
            sell[i] = max(sell[i-1], buy[i-1]+prices[i]);
        }
        
        return sell[n];
    }
};

