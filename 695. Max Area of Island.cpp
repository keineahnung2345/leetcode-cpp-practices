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

//Approach #2: Depth-First Search (Iterative) [Accepted]
//Runtime: 32 ms, faster than 17.35% of C++ online submissions for Max Area of Island.
//Memory Usage: 16 MB, less than 19.05% of C++ online submissions for Max Area of Island.
//time: O(R*C), space: O(R*C)
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(m, vector<bool>(n, false));
        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};
        
        int ans = 0;
        
        for(int r0 = 0; r0 < m; r0++){
            for(int c0 = 0; c0 < n; c0++){
                if(grid[r0][c0] && !visited[r0][c0]){
                    int area = 0;
                    stack<vector<int>> stk;
                    stk.push({r0, c0});
//MODE1 and MODE2 work the same, just the places of "visited[r0][c0] = true;" are different
#ifdef MODE1
                    visited[r0][c0] = true;
#endif
                    //dfs for a cell, find the area
                    while(!stk.empty()){
                        vector<int> node = stk.top(); stk.pop();
                        int r = node[0], c = node[1];
                        area++;
#ifdef MODE2
                        if(!visited[r][c]){
                            area++;
                            visited[r][c] = true;
                        }
#endif
                        for(int k = 0; k < 4; k++){
                            int nr = r + dr[k];
                            int nc = c + dc[k];
                            if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] && !visited[nr][nc])
                            {
                                stk.push({nr, nc});
#ifdef MODE1
                                visited[nr][nc] = true;
#endif
                            }
                        }
                    }
                    ans = max(ans, area);
                }
            }
        }
        
        return ans;
    }
};
