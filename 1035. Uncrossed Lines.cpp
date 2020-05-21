//LCS, DP, O(N^2) space
//Runtime: 40 ms, faster than 14.05% of C++ online submissions for Uncrossed Lines.
//Memory Usage: 13.2 MB, less than 9.09% of C++ online submissions for Uncrossed Lines.
//time: O(N^2), space: O(N^2)
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

//LCS, DP, O(N) space
//Runtime: 12 ms, faster than 78.56% of C++ online submissions for Uncrossed Lines.
//Memory Usage: 9.8 MB, less than 77.27% of C++ online submissions for Uncrossed Lines.
//time: O(N^2), space: O(N)
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        
        vector<int> dp(n+1, 0);
        
        for(int i = 1; i <= m; i++){
            int dp_is1_js1 = dp[0]; //will be used when j = 1
            // cout << dp[0] << " "; //0
            for(int j = 1; j <= n; j++){
                int dp_is1_j = dp[j];
                if(A[i-1] == B[j-1]){
                    dp[j] = dp_is1_js1 + 1;
                }else{
                    dp[j] = max(dp[j-1], dp[j]);
                }
                dp_is1_js1 = dp_is1_j;
            }
        }
        
        return dp[n];
    }
};
