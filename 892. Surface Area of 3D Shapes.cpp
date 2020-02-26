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
