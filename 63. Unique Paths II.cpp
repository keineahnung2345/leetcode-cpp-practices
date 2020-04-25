//Runtime: 4 ms, faster than 75.49% of C++ online submissions for Unique Paths II.
//Memory Usage: 9.2 MB, less than 86.67% of C++ online submissions for Unique Paths II.

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<long> > grids(m+1, vector<long>(n+1));
        //padding to the top and left
        for(int i = 0; i < m+1; i++){
            grids[i][0] = 0;
        }
        for(int j = 0; j < n+1; j++){
            grids[0][j] = 0;
        }
        
        for(int diag = 0; diag <= (m-1) + (n-1); diag++){
            for(int i = max(0, diag-(n-1)), j = diag - i; i <= m-1 && j >= 0; i++, j--){
                if(obstacleGrid[i][j] == 1){
                    grids[i+1][j+1] = 0;
                }else if(i == 0 && j == 0){
                    //it should be "if(i == 0 && j == 0)" rather than "if(i == 0 || j == 0)" here!
                    //we can only ensure that grids[0][0] is reachable, but grids[0][x] or grids[x][0]
                    grids[i+1][j+1] = 1;
                }else{
                    grids[i+1][j+1] = grids[i-1+1][j+1] + grids[i+1][j-1+1];
                }
                // cout << i << " " << j << " " << obstacleGrid[i][j] << " " << grids[i+1][j+1] << endl;
            }
        }
        // cout << endl << endl;
        
        // for(int i = 0; i < m+1; Vi++){
        //     for(int j = 0; j < n+1; j++){
        //         cout << grids[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        return grids[m-1+1][n-1+1];
    }
};

//DP, shorter
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        
        vector<vector<long long int>> dp(m+1, vector(n+1, 0LL));
        
        dp[1][1] = 1;
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(i == 1 && j == 1) continue;
                dp[i][j] = (obstacleGrid[i-1][j-1] == 1) ? 0 : (dp[i-1][j] + dp[i][j-1]);
                // cout << dp[i][j] << " ";
            }
            // cout << endl;
        }
        
        return dp[m][n];
    }
};

//DP, O(N) space
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        
        vector<long long int> row(n+1, 0LL);
        
        row[1] = 1;
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(i == 1 && j == 1) continue;
                row[j] = (obstacleGrid[i-1][j-1] == 1) ? 0 : (row[j] + row[j-1]);
            }
        }
        
        return row[n];
    }
};
