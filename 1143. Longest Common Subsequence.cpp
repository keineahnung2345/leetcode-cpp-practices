//DP
//Runtime: 20 ms, faster than 27.49% of C++ online submissions for Longest Common Subsequence.
//Memory Usage: 14.2 MB, less than 100.00% of C++ online submissions for Longest Common Subsequence.
//time: O(nm), space: O(nm)
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        int i1 = 0, i2 = 0;
        
        for(int i1 = 0; i1 < m; i1++){
            for(int i2 = 0; i2 < n; i2++){
                //distinguish the case whether text1[i1] == text2[i2] or not so the same char won't be counted twice
                if(text1[i1] == text2[i2]){
                    dp[i1][i2] = ((i1 > 0 && i2 > 0) ? dp[i1-1][i2-1] : 0) + 1;
                }else{
                    dp[i1][i2] = max(((i1 > 0) ? dp[i1-1][i2] : 0), 
                                     ((i2 > 0) ? dp[i1][i2-1] : 0));
                }
                // cout << i1 << " " << i2 << " " << dp[i1][i2] << endl;
            }
        }
        
        return dp[m-1][n-1];
    }
};

//DP, memory optimization
//https://leetcode.com/problems/longest-common-subsequence/discuss/348884/C%2B%2B-with-picture-O(nm)
//Runtime: 12 ms, faster than 87.59% of C++ online submissions for Longest Common Subsequence.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Longest Common Subsequence.
//time: O(nm), space: O(min(m,n))
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(2, vector<int>(n, 0));
        
        int i1 = 0, i2 = 0;
        
        for(int i1 = 0; i1 < m; i1++){
            for(int i2 = 0; i2 < n; i2++){
                //distinguish the case whether text1[i1] == text2[i2] or not so the same char won't be counted twice
                if(text1[i1] == text2[i2]){
                    dp[i1%2][i2] = ((i1 > 0 && i2 > 0) ? dp[(i1-1)%2][i2-1] : 0) + 1;
                }else{
                    dp[i1%2][i2] = max(((i1 > 0) ? dp[(i1-1)%2][i2] : 0), 
                                     ((i2 > 0) ? dp[i1%2][i2-1] : 0));
                }
                // cout << i1 << " " << i2 << " " << dp[i1][i2] << endl;
            }
        }
        
        return dp[(m-1)%2][n-1];
    }
};

//recursion
//https://leetcode.com/articles/delete-operation-for-two-strings/
//TLE
//time: O(2^max(m,n)), space: O(max(m,n))
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2, int m = -1, int n = -1) {
        if(m == -1) m = text1.size();
        if(n == -1) n = text2.size();
        
        if(m == 0 || n == 0){
            return 0;
        }
        
        if(text1[m-1] == text2[n-1]){
            return 1 + longestCommonSubsequence(text1, text2, m-1, n-1);
        }
        
        return max(longestCommonSubsequence(text1, text2, m-1, n), 
                   longestCommonSubsequence(text1, text2, m, n-1)
                  );
    }
};

//recursion + memo
//https://leetcode.com/articles/delete-operation-for-two-strings/
//TLE
//37 / 38 test cases passed.
//time: O(m*n), space: O(m*n)
class Solution {
public:
    vector<vector<int>> memo;
    
    int longestCommonSubsequence(string text1, string text2, int m, int n) {
        if(m == 0 || n == 0){
            return 0;
        }
        
        if(memo[m][n] != -1) return memo[m][n];
        
        if(text1[m-1] == text2[n-1]){
            memo[m][n] = 1 + longestCommonSubsequence(text1, text2, m-1, n-1);
        }else{
            memo[m][n] = max(longestCommonSubsequence(text1, text2, m-1, n),
                             longestCommonSubsequence(text1, text2, m, n-1));
        }
        
        return memo[m][n];
    }
    
    int longestCommonSubsequence(string text1, string text2){
        int m = text1.size(), n = text2.size();
        memo = vector<vector<int>>(m+1, vector(n+1, -1));
        return longestCommonSubsequence(text1, text2, m, n);
    }
};
