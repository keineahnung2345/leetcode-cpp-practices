//Backtracking
//TLE
//10 / 61 test cases passed.
class Solution {
public:
    int m, n;
    
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    void backtrack(int& minSum, int curSum, int curI, int curJ, vector<vector<int>>& grid, vector<vector<bool>>& visited){
        if(curI == m-1 && curJ == n-1){
            minSum = min(minSum, curSum);
        }else{
            for(vector<int>& dir : dirs){
                int nextI = curI + dir[0];
                int nextJ = curJ + dir[1];
                if(nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n && !visited[nextI][nextJ]){
                    cout << nextI << " " << nextJ << " | ";
                    visited[nextI][nextJ] = true;
                    backtrack(minSum, curSum+grid[nextI][nextJ], nextI, nextJ, grid, visited);
                    visited[nextI][nextJ] = false;
                }
            }
        }
    };
    
    int minPathSum(vector<vector<int>>& grid) {
        this->m = grid.size();
        if(this->m == 0) return 0;
        this->n = grid[0].size();
        
        int minSum = INT_MAX;
        int curI = 0, curJ = 0;
        int curSum = grid[curI][curJ];
        vector<vector<bool>> visited(m, vector(n, false));
        
        backtrack(minSum, curSum, curI, curJ, grid, visited);
        
        return minSum;
    }
};

//DP
//Note: You can only move either down or right at any point in time.
//Runtime: 12 ms, faster than 23.69% of C++ online submissions for Minimum Path Sum.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Minimum Path Sum.
class Solution {
public:
    int m, n;
    
    vector<vector<int>> dirs = {
        {-1, 0},
        {0, -1}
    };
    
    int minPathSum(vector<vector<int>>& grid) {
        this->m = grid.size();
        if(this->m == 0) return 0;
        this->n = grid[0].size();
        
        vector<vector<int>> dp = grid;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int prevMin = INT_MAX;
                for(vector<int>& dir : dirs){
                    int prevI = i + dir[0];
                    int prevJ = j + dir[1];
                    if(prevI >= 0 && prevJ >= 0){
                        prevMin = min(prevMin, dp[prevI][prevJ]);
                    }
                }
                dp[i][j] += (prevMin == INT_MAX) ? 0 : prevMin;
            }
        }
        
        return dp[m-1][n-1];
    }
};
