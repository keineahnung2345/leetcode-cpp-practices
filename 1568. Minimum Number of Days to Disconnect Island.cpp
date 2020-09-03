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

//Tarjan’s algorithm for finding articulation points
//https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/discuss/819643/Java-Tarjan-4ms-with-explain
//https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
//Runtime: 24 ms, faster than 97.01% of C++ online submissions for Minimum Number of Days to Disconnect Island.
//Memory Usage: 11.5 MB, less than 72.15% of C++ online submissions for Minimum Number of Days to Disconnect Island.
class Solution {
public:
    int m, n;
    vector<vector<int>> dirs;
    vector<vector<int>> graph;
    
    int getConns(vector<vector<int>>& grid){
        int conns = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
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
    
    bool APUtil(int u, int& time, vector<bool>& visited, vector<int>& disc, 
                vector<int>& low, vector<int>& parent){
        int child_count = 0;
        visited[u] = true;
        ++time;
        disc[u] = low[u] = time;
        // cout << "visit: " << u/n << ", " << u%n << " at " << time << endl;
        for(int& v : graph[u]){
            if(!visited[v]){
                ++child_count;
                parent[v] = u;
                bool res = APUtil(v, time, visited, disc, low, parent);
                if(res) return true;
                /*
                if the subtree rooted at v has 
                a back edge connected to somewhere higher than u,
                then low[u] will be updated
                */
                low[u] = min(low[u], low[v]);
                
                if(parent[u] == -1 && child_count > 1)
                    return true;
                
                /*
                u: not root nor leaf,
                and one of its children's subtree doesn't have backedge
                */
                if(parent[u] != -1 && low[v] >= disc[u])
                    return true;
            }else if(v != parent[u]){
                //?
                low[u] = min(low[u], disc[v]);
            }
        }
        
        return false;
    }
    
    bool AP(){
        vector<bool> visited(m*n, false);
        vector<int> disc(m*n, 0);
        vector<int> low(m*n, 0);
        vector<int> parent(m*n, -1);
        
        int time = 0;
        for(int i = 0; i < m*n; ++i){
            if(graph[i].empty() || visited[i]) continue;
            // cout << "root: " << i/n << ", " << i%n << " has " << graph[i].size() << " children" << endl;
            bool res = APUtil(i, time, visited, disc, low, parent);
            if(res) return true;
        }
        
        for(int i = 0; i < m*n; ++i){
            if(graph[i].empty()) continue;
            // cout << i/n << ", " << i%n << " , disc: " << disc[i] << ", low: " << low[i] << ", parent: " << parent[i]/n << ", " << parent[i]%n << endl;
        }
        
        return false;
    };
    
    int getid(int i, int j){
        //*n, not *m !!
        return i*n + j;
    };
    
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int conns = getConns(grid);
        // cout << "conns: " << conns << endl;
        if(conns == 0 || conns >= 2) return 0;
        
        int sum = 0;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                sum += grid[i][j];
            }
        }
        
        if(sum <= 2) return sum;
        
        graph = vector<vector<int>>(m*n);
        // cout << "m: " << m << ", n: " << n << endl;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(!grid[i][j]) continue;
                int cid = getid(i, j);
                // cout << "(" << i << ", " << j << "): ";
                for(vector<int>& dir : dirs){
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    if(ni < 0 || ni >= m || nj < 0 || nj >= n || !grid[ni][nj])
                        continue;
                    int nid = getid(ni, nj);
                    graph[cid].push_back(nid);
                    // cout << "(" << ni << ", " << nj << "), ";
                    // graph[nid].push_back(cid); //duplicate
                }
                // cout << endl;
            }
        }
        
        //can find articulation point, so only need one cut
        if(AP()) return 1;
        return 2;
    }
};
