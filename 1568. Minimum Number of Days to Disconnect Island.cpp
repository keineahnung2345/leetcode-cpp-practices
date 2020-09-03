//https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/discuss/819303/Python-you-need-at-most-2-days
//Runtime: 476 ms, faster than 18.56% of C++ online submissions for Minimum Number of Days to Disconnect Island.
//Memory Usage: 31.9 MB, less than 16.52% of C++ online submissions for Minimum Number of Days to Disconnect Island.
//time: O(m^2*n^2)
class Solution {
public:
    int m, n;
    vector<vector<int>> dirs;
    vector<vector<bool>> visited;
    
    int getConns(vector<vector<int>>& grid){
        int conns = 0;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(!grid[i][j] || visited[i][j]) continue;
                
                ++conns;
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;
                
                while(!q.empty()){
                    pair<int, int> p = q.front(); q.pop();
                    
                    for(vector<int>& dir : dirs){
                        int ni = p.first + dir[0];
                        int nj = p.second + dir[1];
                        if(ni < 0 || ni >= m || nj < 0 || nj >= n || 
                           !grid[ni][nj] || visited[ni][nj]) 
                            continue;
                        visited[ni][nj] = true;
                        q.push({ni,nj});
                    }
                }
            }
        }
        
        return conns;
    }
    
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int conns = getConns(grid);
        // cout << "conns: " << conns << endl;
        if(conns == 0 || conns >= 2) return 0;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(!grid[i][j]) continue;
                grid[i][j] = 0;
                conns = getConns(grid);
                // cout << "conns: " << conns << endl;
                /*
                [[0,0,0],[0,1,0],[0,0,0]]
                is also needed to be disconnected,
                i.e. to destroy the island
                */
                if(conns == 0 || conns >= 2)
                    return 1;
                grid[i][j] = 1;
            }
        }
        
        return 2;
    }
};
