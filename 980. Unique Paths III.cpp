//Runtime: 12 ms, faster than 29.53% of C++ online submissions for Unique Paths III.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Unique Paths III.
class Solution {
public:
    vector<pair<int, int>> dirs;
    int startI, startJ, endI, endJ;
    
    void backtrack(vector<vector<bool>>& visited, vector<vector<int>>& grid, int& pathCount, int curI, int curJ){
        int m = visited.size(), n = visited[0].size();
        
        bool allVisited = true;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                allVisited &= visited[i][j];
                if(!allVisited) break;
            }
            if(!allVisited) break;
        }
        
        if(curI == endI && curJ == endJ && allVisited){
            pathCount++;
        }
        
        for(int i = 0; i < dirs.size(); i++){
            int nextI = curI + dirs[i].first;
            int nextJ = curJ + dirs[i].second;
            if(nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n && !visited[nextI][nextJ] && grid[nextI][nextJ] != -1){
                //valid position
                visited[nextI][nextJ] = true;
                backtrack(visited, grid, pathCount, nextI, nextJ);
                visited[nextI][nextJ] = false;
            }
        }
    }
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        int pathCount = 0;
        
        for(int i = 0; i < m; i++){
            //start
            auto it = find(grid[i].begin(), grid[i].end(), 1);
            if(it != grid[i].end()){
                startI = i; startJ = it - grid[i].begin();
            }
            
            //end
            it = find(grid[i].begin(), grid[i].end(), 2);
            if(it != grid[i].end()){
                endI = i; endJ = it - grid[i].begin();
            }
            
            //obstacle
            it = find(grid[i].begin(), grid[i].end(), -1);
            if(it != grid[i].end()){
                //mark obstacle as visited
                visited[i][it - grid[i].begin()] = true;
            }
        }
        
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        // cout << "goal: " << endI << " " << endJ << endl;
        
        visited[startI][startJ] = true;
        backtrack(visited, grid, pathCount, startI, startJ);
        
        return pathCount;
    }
};
