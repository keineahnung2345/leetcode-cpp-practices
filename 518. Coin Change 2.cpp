//TLE
//20 / 27 test cases passed.
class Solution {
public:
    vector<vector<int>> memo;
    
    int change(int amount, vector<int>& coins, int start) {
        //coin >= 1
        if(start == coins.size()) return amount == 0;
        //impossible
        if(amount < 0) return 0;
        
        if(memo[start][amount] != 0){
            return memo[start][amount];
        }
        
        for(int times = 0; coins[start]*times <= amount; times++){
            int tmp = change(amount-coins[start]*times, coins, start+1);
            // cout << "coin: " << coins[start] << ", times: " << times << ", " << tmp << endl;
            memo[start][amount] += tmp;
            // memo[start][amount] += change(amount-coins[start]*times, coins, start+1);
        }
        
        // cout << "(" << start << ", " << amount << "): " << memo[start][amount] << endl;
        return memo[start][amount];
    }
    
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        if(n == 0) return amount == 0;
        //the range of amount is [0,5000]
        memo = vector<vector<int>>(n, vector<int>(5001));
        change(amount, coins, 0);
        
        return memo[0][amount];
    }
};

//O(N) space DP
//Runtime: 4 ms, faster than 99.34% of C++ online submissions for Coin Change 2.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Coin Change 2.
//time: O(N^2), space: O(N)
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        //amount's range: [0,5000]
        vector<int> dp(5001, 0);
        
        dp[0] = 1;
        
        for(int i = n-1; i >= 0; i--){
            for(int sum = coins[i]; sum <= amount; sum++){
                dp[sum] += dp[sum-coins[i]];
            }
        }
        
        return dp[amount];
    }
};

//unbounded knapsack problem
//https://leetcode.com/problems/coin-change-2/discuss/99212/Knapsack-problem-Java-solution-with-thinking-process-O(nm)-Time-and-O(m)-Space
//O(N^2) space DP
//Runtime: 36 ms, faster than 35.46% of C++ online submissions for Coin Change 2.
//Memory Usage: 26 MB, less than 14.29% of C++ online submissions for Coin Change 2.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int>(5001, 0));
        
        //use 0 coin to make up amount = 0
        dp[0][0] = 1;
        
        //i: use coins[0...i-1]
        for(int i = 1; i <= n; i++){
            /*
            dp[i][0] = 1;
            for(int sum = 1; sum <= amount; sum++){
            */
            for(int sum = 0; sum <= amount; sum++){
                /*
                dp[i-1][sum]: not choose current coin
                dp[i][sum-coins[i-1]]: choose current coin(again)
                */
                dp[i][sum] = dp[i-1][sum] + (sum >= coins[i-1] ? dp[i][sum-coins[i-1]] : 0);
            }
        }
        
        //use coins[0...n-1] to make up amount
        return dp[n][amount];
    }
};
