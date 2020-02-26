//Runtime: 12 ms, faster than 27.88% of C++ online submissions for Surface Area of 3D Shapes.
//Memory Usage: 9.4 MB, less than 40.00% of C++ online submissions for Surface Area of 3D Shapes.

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ud = 0, lat = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j]) ud += 2;
                
                //remember the max(xxx, 0)!
                if(i == 0) lat += grid[i][j];
                else lat += max(grid[i][j] - grid[i-1][j], 0);
                
                if(i == m - 1) lat += grid[i][j];
                else lat += max(grid[i][j] - grid[i+1][j], 0);
                
                if(j == 0) lat += grid[i][j];
                else lat += max(grid[i][j] - grid[i][j-1], 0);
                
                if(j == n - 1) lat += grid[i][j];
                else lat += max(grid[i][j] - grid[i][j+1], 0);
                
                // cout << grid[i][j] << ", " << lat << endl;
            }
        }
        
        return ud + lat;
    }
};

//official sol
//Runtime: 12 ms, faster than 27.88% of C++ online submissions for Surface Area of 3D Shapes.
//Memory Usage: 9.3 MB, less than 80.00% of C++ online submissions for Surface Area of 3D Shapes.
//time: O(N^2), space: O(1)

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        vector<pair<int, int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        
        int n = grid.size();
        int ans = 0;
        
        for(int r = 0; r < n; r++){
            for(int c = 0; c < n; c++){
                if(grid[r][c]){
                    ans += 2;
                    for(pair<int, int> dir : dirs){
                        //nv : neighboring grid's value
                        int nr = r + dir.first;
                        int nc = c + dir.second;
                        int nv = 0;
                        if(nr >= 0 && nr < n && nc >= 0 && nc < n)
                            nv = grid[nr][nc];
                        ans += max(grid[r][c] - nv, 0);
                    }
                }
            }
        }
        
        return ans;
    }
};

