//bfs
//Runtime: 80 ms, faster than 5.44% of C++ online submissions for Surrounded Regions.
//Memory Usage: 19.1 MB, less than 8.24% of C++ online submissions for Surrounded Regions.
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if(m == 0) return;
        int n = board[0].size();
        if(n == 0) return;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs = {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        vector<vector<int>> component;
        vector<int> cur;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                bool surrounded = true;
                component.clear();
                if(board[i][j] == 'O' && !visited[i][j]){
                    queue<vector<int>> q;
                    q.push({i, j});
                    visited[i][j] = true;
                    
                    while(!q.empty()){
                        cur = q.front(); q.pop();
                        if(cur[0] == 0 || cur[0] == m-1 || cur[1] == 0 || cur[1] == n-1){
                            surrounded = false;
                        }
                        component.push_back(cur);
                        
                        for(vector<int>& dir : dirs){
                            int ni = cur[0] + dir[0];
                            int nj = cur[1] + dir[1];
                            if(ni >= 0 && ni < m && nj >= 0 && nj < n && board[ni][nj] == 'O' && !visited[ni][nj]){        
                                visited[ni][nj] = true;
                                q.push({ni, nj});
                            }
                        }
                    }
                }
                
                if(surrounded && !component.empty()){
                    for(vector<int>& cur : component){
                        board[cur[0]][cur[1]] = 'X';
                    }
                }
            }
        }
    }
};

//bfs
//https://leetcode.com/problems/surrounded-regions/discuss/41612/A-really-simple-and-readable-C%2B%2B-solutionuff0conly-cost-12ms
//Runtime: 32 ms, faster than 54.14% of C++ online submissions for Surrounded Regions.
//Memory Usage: 11 MB, less than 44.85% of C++ online submissions for Surrounded Regions.
class Solution {
public:
    int m, n;
    vector<vector<bool>> visited;
    vector<vector<int>> dirs;
    vector<int> cur;
    
    void changeNeighbor(vector<vector<char>>& board, int i, int j, char src, char dst){
        queue<vector<int>> q;
        q.push({i, j});
        visited[i][j] = true;

        while(!q.empty()){
            cur = q.front(); q.pop();
            board[cur[0]][cur[1]] = dst;

            for(vector<int>& dir : dirs){
                int ni = cur[0] + dir[0];
                int nj = cur[1] + dir[1];
                if(ni >= 0 && ni < m && nj >= 0 && nj < n && board[ni][nj] == 'O' && !visited[ni][nj]){
                    visited[ni][nj] = true;
                    q.push({ni, nj});
                }
            }
        }
    };
    
    void solve(vector<vector<char>>& board) {
        m = board.size();
        if(m == 0) return;
        n = board[0].size();
        if(n == 0) return;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        dirs = {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        
        for(int j = 0; j < n; ++j){
            for(int i : {0, m-1}){
                if(board[i][j] == 'O' && !visited[i][j]){
                    changeNeighbor(board, i, j, 'O', '1');
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            for(int j : {0, n-1}){
                if(board[i][j] == 'O' && !visited[i][j]){
                    changeNeighbor(board, i, j, 'O', '1');
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }else if(board[i][j] == '1'){
                    board[i][j] = 'O';
                }
            }
        }
    }
};

//union find
//https://leetcode.com/problems/surrounded-regions/discuss/41617/Solve-it-using-Union-Find
//Runtime: 36 ms, faster than 41.79% of C++ online submissions for Surrounded Regions.
//Memory Usage: 10.4 MB, less than 63.29% of C++ online submissions for Surrounded Regions.
class DSU{
public:
    vector<int> parent;
    
    DSU(int N){
        parent = vector<int>(N);
        iota(parent.begin(), parent.end(), 0);
    };
    
    //wrong implementation
    // int find(int x){
    //     if(parent[x] == x){
    //         return x;
    //     }
    //     return parent[x] = find(parent[x]);
    // };
    
    int find(int x){
        if(parent[x] != x){ //initial state
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y){
        parent[find(x)] = find(y);
    };
    
    bool isConnected(int x, int y){
        return find(x) == find(y);
    }
};

class Solution {
public:
    int m, n;
    
    int node(int i, int j){
        return i*n+j;
    };
    
    void solve(vector<vector<char>>& board) {
        m = board.size();
        if(m == 0) return;
        n = board[0].size();
        if(n == 0) return;
        
        vector<vector<int>> dirs = {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        
        //[0, m*n-1] for each cell, m*n for dummy cell
        DSU dsu(m*n+1);
        int dummyNode = m*n;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(board[i][j] != 'O') continue;
                if(i == 0 || i == m-1 || j == 0 || j == n-1){
                    dsu.unite(node(i, j), dummyNode);
                }else{
                    for(vector<int>& dir : dirs){
                        int ni = i + dir[0];
                        int nj = j + dir[1];
                        if(ni >= 0 && ni < m && nj >= 0 && nj < n && board[ni][nj] == 'O'){
                            dsu.unite(node(ni, nj), node(i, j));
                        }
                    }
                    //another implementation
                    // if(i > 0 && board[i-1][j] == 'O')  dsu.unite(node(i,j), node(i-1,j));
                    // if(i < m-1 && board[i+1][j] == 'O')  dsu.unite(node(i,j), node(i+1,j));
                    // if(j > 0 && board[i][j-1] == 'O')  dsu.unite(node(i,j), node(i, j-1));
                    // if(j < n-1 && board[i][j+1] == 'O')  dsu.unite(node(i,j), node(i, j+1));
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(dsu.isConnected(node(i, j), dummyNode)){
                    board[i][j] = 'O';
                }else{
                    board[i][j] = 'X';
                }
            }
        }
    }
};
