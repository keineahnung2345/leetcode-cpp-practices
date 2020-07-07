//Runtime: 304 ms, faster than 13.00% of C++ online submissions for Island Perimeter.
//Memory Usage: 97.6 MB, less than 16.54% of C++ online submissions for Island Perimeter.
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        
        vector<vector<int>> dirs = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}};
        
        int ans = 0;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j]){
                    ans += 4;
                    for(vector<int>& dir : dirs){
                        int ni = i + dir[0];
                        int nj = j + dir[1];
                        if(ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj]){
                           --ans; 
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};
