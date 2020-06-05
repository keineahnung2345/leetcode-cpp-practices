//bounded backpack problem with 2-dimensional constraint
//Runtime: 380 ms, faster than 32.03% of C++ online submissions for Ones and Zeroes.
//Memory Usage: 101.9 MB, less than 14.72% of C++ online submissions for Ones and Zeroes.
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<vector<int>>> dp(strs.size(), vector<vector<int>>(m+1, vector(n+1, 0)));
        
        for(int i = 0; i < strs.size(); i++){
            //the cost of char '0'
            int cm = count(strs[i].begin(), strs[i].end(), '0');
            //the cost of char '1'
            int cn = count(strs[i].begin(), strs[i].end(), '1');
            for(int j = 0; j <= m; j++){
                for(int k = 0; k <= n; k++){
                    if(i == 0){
                        dp[i][j][k] = (j >= cm && k >= cn);
                    }else{
                        dp[i][j][k] = max(dp[i-1][j][k], (i > 0 && j >= cm && k >= cn) ? 1 + dp[i-1][j-cm][k-cn] : 0);
                    }
                    // cout << i << ", " << j << ", " << k << " : " << dp[i][j][k] << endl;
                }
            }
        }
        
        return dp[strs.size()-1][m][n];
    }
};
