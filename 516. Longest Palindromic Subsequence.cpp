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

//DP, add shortcut, O(1) space
//Runtime: 80 ms, faster than 81.12% of C++ online submissions for Longest Palindromic Subsequence.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Longest Palindromic Subsequence.
//from leetcode 100% solution
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        
        if(n == 1) return 1;
        if(n == 2) return (s[0] == s[1]) ? 2 : 1;
        
        int l = 0, r = n-1;
        while(l <= r && s[l] == s[r]){
            l++; r--;
        }
        if(l > r) return n;
        
        vector<int> dp(n, 0);
        int dp_ip1_js1, dp_ip1_j;
            
        for(int i = n-1; i >= 0; i--){
            /*
            dp_ip1_js1: dp[i+1][j-1],
            it is only used when i+1 < j,
            i.e. there will be at least one char 
            between s[i] and s[j], 
            so dp[i+1][j-1] is at least 1
            */
            dp_ip1_js1 = 1; //reset here!!(reset for each row)
            
            for(int j = i; j < n; j++){
                if(i == j){
                    dp[j] = 1;
                }else if(i+1 == j){
                    dp[j] = (s[i] == s[j]) ? 2 : 1;
                }else if(i+1 < j){
                    dp_ip1_j = dp[j]; //dp[i+1][j]
                    dp[j] = max({dp_ip1_js1 + ((s[i] == s[j]) ? 2 : 0),
                                   dp[j], //dp[i+1][j]
                                   dp[j-1] //dp[i][j-1]
                                 });
                    dp_ip1_js1 = dp_ip1_j;
                }
                
                // cout << "(" << i << ", " << j << "): " << dp[j] << endl;
            }
        }
        
        // cout << "==============" << endl;
        
        return dp[n-1];
    }
};
