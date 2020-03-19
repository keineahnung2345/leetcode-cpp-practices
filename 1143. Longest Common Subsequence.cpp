//Runtime: 20 ms, faster than 27.49% of C++ online submissions for Longest Common Subsequence.
//Memory Usage: 14.2 MB, less than 100.00% of C++ online submissions for Longest Common Subsequence.
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
