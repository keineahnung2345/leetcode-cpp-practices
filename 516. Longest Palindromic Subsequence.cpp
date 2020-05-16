//DP
//https://github.com/keineahnung2345/leetcode-cpp-practices/blob/master/5.%20Longest%20Palindromic%20Substring.cpp
//Runtime: 264 ms, faster than 5.98% of C++ online submissions for Longest Palindromic Subsequence.
//Memory Usage: 67.2 MB, less than 100.00% of C++ online submissions for Longest Palindromic Subsequence.
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector(n, 0));
        
        for(int i = n-1; i >= 0; i--){
            for(int j = i; j < n; j++){
                if(i == j){
                    dp[i][j] = 1;
                }else if(i+1 == j){
                    dp[i][j] = (s[i] == s[j]) ? 2 : 1;
                }else if(i+1 < j){
                    dp[i][j] = max({dp[i+1][j-1] + ((s[i] == s[j]) ? 2 : 0),
                                   dp[i+1][j],
                                   dp[i][j-1]});
                }
                
                // cout << "(" << i << ", " << j << "): " << dp[i][j] << endl;
            }
        }
        
        // cout << "==============" << endl;
        
        return dp[0][n-1];
    }
};
