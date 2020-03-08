//Approach #1: Depth-First Search (Recursive) [Accepted]
//Runtime: 32 ms, faster than 17.35% of C++ online submissions for Max Area of Island.
//Memory Usage: 11.4 MB, less than 66.67% of C++ online submissions for Max Area of Island.
//time: O(R*C), space: O(R*C)
class Solution {
public:
    int m, n;
    vector<vector<bool>> visited;
    
    int area(vector<vector<int>>& grid, int r, int c){
        //return 0 for visited cell because we have already calculated the area of the island containing this cell
        if(r < 0 || r >= m || c < 0 || c >= n || visited[r][c] || grid[r][c] == 0) return 0;
        
        visited[r][c] = true;
        
        return 1 + area(grid, r+1, c) + area(grid, r-1, c) + area(grid, r, c+1) + area(grid, r, c-1);
    };
    
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size(), n = grid[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        int ans = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                ans = max(ans, area(grid, i, j));
            }
        }
        
        return ans;
    }
};
