//DP
//@xiaowuc1's answer
//Runtime: 280 ms, faster than 20.00% of C++ online submissions for Cherry Pickup II.
//Memory Usage: 14.6 MB, less than 100.00% of C++ online submissions for Cherry Pickup II.
//time: O(m*N^2), space: O(m*n^2)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        
        /*
        for example in the case:
        [[0,8,7,10,9,10,0,9,6],
         [8,7,10,8,7,4,9,6,10],
         [8,1,1,5,1,5,5,1,2],
         [9,4,10,8,8,1,9,5,0],
         [4,3,6,10,9,2,4,8,10],
         [7,3,2,8,3,3,5,9,8],
         [1,2,6,5,6,2,0,10,0]]
         
        dp[1][0][0] should be set to a invalid value, not 8,
        because the two robots can't both appear at (1, 0)
        to avoid this, we initialize dp to INT_MIN, not 0!
        */
        
        
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        
        dp[0][0][n-1] = grid[0][0] + grid[0][n-1];
        
        for(int i = 1; i < m; i++){
            for(int a = 0; a < n; a++){
                for(int b = 0; b < n; b++){
                    for(int l = a-1; l <= a+1; l++){
                        for(int r = b-1; r <= b+1; r++){
                            if(l < 0 || l >= n || r < 0 || r >= n) continue;
                            dp[i][a][b] = max(dp[i][a][b], ((a != b) ? grid[i][a] + grid[i][b] : grid[i][a]) + dp[i-1][l][r]);
                        }
                    }
                    
                    cout << i << ", " << a << ", " << b << ", " << dp[i][a][b] << endl;
                }
            }
        }
        
        int ans = 0;
        for(int a = 0; a < n; a++){
            for(int b = 0; b < n; b++){
                ans = max(ans, dp[m-1][a][b]);
            }
        }
        
        return ans;
    }
};

//DP, O(n^2) space
//@xiaowuc1's answer
//Runtime: 228 ms, faster than 20.00% of C++ online submissions for Cherry Pickup II.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Cherry Pickup II.
//time: O(m*N^2), space: O(n^2)
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        
        dp[0][0][n-1] = grid[0][0] + grid[0][n-1];
        
        for(int i = 1; i < m; i++){
            for(int a = 0; a < n; a++){
                for(int b = 0; b < n; b++){
                    for(int l = a-1; l <= a+1; l++){
                        for(int r = b-1; r <= b+1; r++){
                            if(l < 0 || l >= n || r < 0 || r >= n) continue;
                            dp[i%2][a][b] = max(dp[i%2][a][b], ((a != b) ? grid[i][a] + grid[i][b] : grid[i][a]) + dp[(i-1)%2][l][r]);
                        }
                    }
                    
                    // cout << i << ", " << a << ", " << b << ", " << dp[i%2][a][b] << endl;
                }
            }
        }
        
        int ans = 0;
        for(int a = 0; a < n; a++){
            for(int b = 0; b < n; b++){
                ans = max(ans, dp[(m-1)%2][a][b]);
            }
        }
        
        return ans;
    }
};
