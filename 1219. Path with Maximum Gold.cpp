//https://leetcode.com/problems/path-with-maximum-gold/discuss/398184/C%2B%2B-Short-DFS
//Runtime: 52 ms, faster than 63.62% of C++ online submissions for Path with Maximum Gold.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Path with Maximum Gold.

class Solution {
public:
    vector<vector<int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    int dfs(vector<vector<int>>& grid, int i, int j){
        int ans = 0;
        int org = grid[i][j];
        grid[i][j] = 0; //mark as visited
        
        for(auto& direction : directions){
            int x = direction[0], y = direction[1];
            //Note: if (grid[i+x][j+y] != 0), skip it
            if(i + x >= 0 && j + y >= 0 && i + x < grid.size() && j + y < grid[0].size() && grid[i+x][j+y] != 0){
                ans = max(ans, grid[i+x][j+y] + dfs(grid, i + x, j + y));
            }
        }
        
        grid[i][j] = org;
        return ans;
    }
    
    int getMaximumGold(vector<vector<int>>& grid) {
        int ans = 0;
        
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j]){
                    ans = max(ans, grid[i][j] + dfs(grid, i, j));
                }
            }
        }
        
        return ans;
    }
};
