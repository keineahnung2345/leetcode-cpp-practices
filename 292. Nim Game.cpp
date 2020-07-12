//DP
//TLE
//50 / 60 test cases passed.
class Solution {
public:
    bool canWinNim(int n) {
        if(n <= 3) return true;
        
        vector<bool> dp(n+1, false);
        
        dp[1] = dp[2] = dp[3] = true;
        
        for(int i = 4; i <= n; ++i){
            dp[i] = (!dp[i-1] || !dp[i-2] || !dp[i-3]);
        }
        
        return dp[n];
    }
};

//math
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Nim Game.
//Memory Usage: 6.1 MB, less than 13.57% of C++ online submissions for Nim Game.
class Solution {
public:
    bool canWinNim(int n) {
        return n%4;
    }
};
