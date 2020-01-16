//Runtime: 28 ms, faster than 79.68% of C++ online submissions for Matrix Block Sum.
//Memory Usage: 11.4 MB, less than 100.00% of C++ online submissions for Matrix Block Sum.

//Hint 3
//Create a cumulative sum matrix where dp[i][j] is the sum of all cells in the rectangle from (0,0) to (i,j), 
//use inclusion-exclusion idea.

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp = mat;
        vector<vector<int>> ans;
        int bottom, right, top, left;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i > 0){
                    dp[i][j] += dp[i-1][j];
                }
                if(j > 0){
                    dp[i][j] += dp[i][j-1];
                }
                if(i > 0 && j > 0){
                    dp[i][j] -= dp[i-1][j-1];
                }
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        
        ans = dp;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                bottom = min(i + K, m - 1);
                right = min(j + K, n - 1);
                top = max(i - K - 1, -1); //-1 means invalid
                left = max(j - K - 1, -1); //-1 means invalid
                ans[i][j] = dp[bottom][right];
                
                if(top != -1){
                    ans[i][j] -= dp[top][right];
                    // cout << i << ", " << j << ":- " << dp[top][right] << endl;
                }
                if(left >= 0){
                    ans[i][j] -= dp[bottom][left];
                    // cout << i << ", " << j << ":- " << dp[bottom][left] << endl;
                }
                if(top >= 0 && left >= 0){
                    ans[i][j] += dp[top][left];
                    // cout << i << ", " << j << ":+ " << dp[top][left] << endl;
                }
            }
        }
        
        return ans;
    }
};
