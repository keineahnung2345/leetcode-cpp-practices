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

//math
//https://leetcode.com/problems/island-perimeter/discuss/95001/clear-and-easy-java-solution
//Runtime: 228 ms, faster than 29.18% of C++ online submissions for Island Perimeter.
//Memory Usage: 96 MB, less than 97.84% of C++ online submissions for Island Perimeter.
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        
        int islands = 0;
        int sharedEdges = 0;
            
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j]){
                    ++islands;
                    /*
                    count shared edges, 
                    note that we only look down and right
                    */
                    if(i+1 < m && grid[i+1][j]) ++sharedEdges;
                    if(j+1 < n && grid[i][j+1]) ++sharedEdges;
                }
            }
        }
        
        return islands*4 - sharedEdges*2;
    }
};
