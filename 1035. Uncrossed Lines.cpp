//LCS
//Runtime: 40 ms, faster than 14.05% of C++ online submissions for Uncrossed Lines.
//Memory Usage: 13.2 MB, less than 9.09% of C++ online submissions for Uncrossed Lines.
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        
        vector<vector<int>> dp(m+1, vector(n+1, 0));
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(A[i-1] == B[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        
        return dp[m][n];
    }
};
