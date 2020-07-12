//dfs + memorization
//Runtime: 128 ms, faster than 60.00% of C++ online submissions for Stone Game IV.
//Memory Usage: 12.3 MB, less than 100.00% of C++ online submissions for Stone Game IV.
class Solution {
public:
    vector<int> memo;
    
    bool dfs(int n){
        // cout << "n: " << n << endl;
        if(memo[n] != -1){
            return memo[n];
        }
        
        for(int i = 1; i * i <= n; ++i){
            if(!dfs(n - i*i)){
                return memo[n] = true;
            }
        }
        
        return memo[n] = false;
    };
    
    bool winnerSquareGame(int n) {
        memo = vector<int>(n+1, -1);
        
        memo[0] = 0;
        for(int i = 1; i*i <= n; ++i){
            memo[i*i] = 1;
        }
        
        return dfs(n);
    }
};

//bottom-up DP
//https://leetcode.com/problems/stone-game-iv/discuss/730582/JavaC%2B%2BPython-DP
//Runtime: 80 ms, faster than 80.00% of C++ online submissions for Stone Game IV.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Stone Game IV.
class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<int> dp(n+1, false);
        
        for(int i = 1; i <= n; ++i){
            for(int k = 1; k * k <= i; ++k){
                //there is a 'k' s.t. we can make the opponent lose
                if(!dp[i - k*k]){
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
