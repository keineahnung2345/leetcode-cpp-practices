/**
In a given grid, each cell can have one of three values:

the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.

 

Example 1:



Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
grid[i][j] is only 0, 1, or 2.
**/

//Runtime: 12 ms, faster than 86.00% of C++ online submissions for Rotting Oranges.
//Memory Usage: 10 MB, less than 99.48% of C++ online submissions for Rotting Oranges.
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<vector<int>> q;
        int minute = 0;
        int levelCount = 0;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
            
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j] == 2){
                    q.push(vector<int> {i,j});
                    levelCount++;
                    visited[i][j] = true;
                }
            }
        }
        
        while(!q.empty()){
            vector<int> cur = q.front();
            int curi = cur[0], curj = cur[1];
            q.pop();
            
            grid[curi][curj] = 2;
            
            // cout << curi << " " << curj << endl;
            
            if(curi > 0 && grid[curi-1][curj] == 1 && !visited[curi-1][curj]){
                q.push(vector<int> {curi-1, curj});
                visited[curi-1][curj] = true;
            }
            
            if(curi < grid.size()-1 && grid[curi+1][curj] == 1 && !visited[curi+1][curj]){
                q.push(vector<int> {curi+1, curj});
                visited[curi+1][curj] = true;
            }
            
            if(curj > 0 && grid[curi][curj-1] == 1 && !visited[curi][curj-1]){
                q.push(vector<int> {curi, curj-1});
                visited[curi][curj-1] = true;
            }
            
            if(curj < grid[0].size()-1 && grid[curi][curj+1] == 1 && !visited[curi][curj+1]){
                q.push(vector<int> {curi, curj+1});
                visited[curi][curj+1] = true;
            }
            
            levelCount--;
            if(levelCount == 0 && q.size() > 0){
                levelCount = q.size();
                minute++;
            }
        }
        
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                if(grid[i][j] == 1) return -1;
            }
        }
        
        // cout << endl;
        
        return minute;
    }
};

/**
Approach 1: Breadth-First Search
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the number of cells in the grid.

Space Complexity: O(N)O(N). 
**/

/**
class Solution {
public:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, -1, 0, 1};
    
    int orangesRotting(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        
        queue<vector<int>> q;
        map<vector<int>, int> depth;
        for(int r = 0; r < R; r++){
            for(int c = 0; c < C; c++){
                if(grid[r][c] == 2){
                    q.push(vector<int> {r,c});
                    depth[vector<int> {r,c}] = 0;
                }
            }
        }
        
        int ans = 0;
        while(!q.empty()){
            vector<int> rc = q.front();
            q.pop();
            int r = rc[0], c = rc[1];
            for(int k = 0; k < 4; k++){
                int nr = r + dr[k];
                int nc = c + dc[k];
                if(nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] == 1){
                    //visit(modify grid) and then push into queue
                    grid[nr][nc] = 2;
                    q.push(vector<int> {nr, nc});
                    ans = depth[vector<int> {nr,nc}] =  depth[vector<int> {r,c}] + 1;
                }
            }
        }
        
        for(vector<int> row : grid){
            for(int e : row){
                if(e == 1) return -1;
            }
        }
        
        return ans;
    }
};**/
