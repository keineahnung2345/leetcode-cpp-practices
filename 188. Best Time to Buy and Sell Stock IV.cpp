//Runtime error(MLE)
//209 / 211 test cases passed.
//time: O(N*k), space: O(k)
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //0th element for padding
        vector<int> holds(k+1, INT_MIN);
        vector<int> cashs(k+1, 0);
        int ans = 0;
        
        for(int price : prices){
            // cout << "price: " << price << endl;
            for(int i = k; i >= 1; i--){
                /*
                we should update cashs[i] and then holds[i]!
                because when we update cashs[i],
                we need holds[i] in last iteration!
                */
                /*
                hold-cash makes a transaction,
                so holds[i]+price means 
                selling the stock bought in ith transaction
                */
                cashs[i] = max(cashs[i], holds[i]+price);
                holds[i] = max(holds[i], cashs[i-1]-price);
                // cout << i << ", " << holds[i] << ", " << cashs[i] << endl;
                ans = max(ans, cashs[i]);
            }
        }
        
        return ans;
    }
};

//Time Limit Exceeded
//209 / 211 test cases passed.
//time: O(N*k), space: O(min(n,k))
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //0th element for padding
        vector<int> holds(min(n,k)+1, INT_MIN);
        vector<int> cashs(min(n,k)+1, 0);
        int ans = 0;
        
        for(int price : prices){
            // cout << "price: " << price << endl;
            for(int i = min(n,k); i >= 1; i--){
                /*
                we should update cashs[i] and then holds[i]!
                because when we update cashs[i],
                we need holds[i] in last iteration!
                */
                /*
                hold-cash makes a transaction,
                so holds[i]+price means 
                selling the stock bought in ith transaction
                */
                cashs[i] = max(cashs[i], holds[i]+price);
                holds[i] = max(holds[i], cashs[i-1]-price);
                // cout << i << ", " << holds[i] << ", " << cashs[i] << endl;
                ans = max(ans, cashs[i]);
            }
        }
        
        return ans;
    }
};

//add quick solution for larger enough k
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54113/A-Concise-DP-Solution-in-Java
//Runtime: 8 ms, faster than 71.12% of C++ online submissions for Best Time to Buy and Sell Stock IV.
//Memory Usage: 12.1 MB, less than 5.55% of C++ online submissions for Best Time to Buy and Sell Stock IV.
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int ans = 0;
        
        //we can do as many transactions as we want
        if(k >= n/2){
            for(int i = 1; i < n; i++){
                ans += max(0, prices[i]-prices[i-1]);
            }
            return ans;
        }
        
        //0th element for padding
        vector<int> holds(min(n,k)+1, INT_MIN);
        vector<int> cashs(min(n,k)+1, 0);
        
        for(int price : prices){
            // cout << "price: " << price << endl;
            for(int i = min(n,k); i >= 1; i--){
                /*
                we should update cashs[i] and then holds[i]!
                because when we update cashs[i],
                we need holds[i] in last iteration!
                */
                /*
                hold-cash makes a transaction,
                so holds[i]+price means 
                selling the stock bought in ith transaction
                */
                cashs[i] = max(cashs[i], holds[i]+price);
                holds[i] = max(holds[i], cashs[i-1]-price);
                // cout << i << ", " << holds[i] << ", " << cashs[i] << endl;
                ans = max(ans, cashs[i]);
            }
        }
        
        return ans;
    }
};

//DP
//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/discuss/54117/Clean-Java-DP-solution-with-comment
//Runtime: 8 ms, faster than 71.12% of C++ online submissions for Best Time to Buy and Sell Stock IV.
//Memory Usage: 13 MB, less than 5.55% of C++ online submissions for Best Time to Buy and Sell Stock IV.
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int ans = 0;
        
        if(k >= n/2){
            for(int i = 1; i < n; i++){
                ans += max(0, prices[i]-prices[i-1]);
            }
            return ans;
        }
        
        /**
         * dp[i, j] represents the max profit up until prices[j] using at most i transactions. 
         * dp[i, j] = max(dp[i, j-1], prices[j] - prices[jj] + dp[i-1, jj]) { jj in range of [0, j-1] }
         *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj]))
         * dp[0, j] = 0; 0 transactions makes 0 profit
         * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.
         */
        //only pad for k(transactions) dimension, not time dimension
        vector<vector<int>> dp(k+1, vector(n, 0));
        for(int i = 1; i <= k; i++){ //transactions
            // int hold = INT_MIN; //this gives WA!!
            int hold = dp[i-1][0] - prices[0];
            for(int j = 1; j < n; j++){ //days
                //hold: the max money we have if we hold a stock until j-1 day
                dp[i][j] = max(dp[i][j-1], prices[j] + hold);
                hold = max(hold, dp[i-1][j] - prices[j]);
            }
        }
        
        return dp[k][n-1];
    }
};
