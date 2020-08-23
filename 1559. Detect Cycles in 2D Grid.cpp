//dfs, detect cycle in undirected graph
//https://www.geeksforgeeks.org/detect-cycle-undirected-graph/
//Runtime: 1872 ms, faster than 20.00% of C++ online submissions for Detect Cycles in 2D Grid.
//Memory Usage: 245.8 MB, less than 20.00% of C++ online submissions for Detect Cycles in 2D Grid.
class Solution {
public:
    int m, n;
    unordered_map<char, unordered_map<int, unordered_set<int>>> graphs;
    unordered_map<char, unordered_set<int>> nodes;
    
    int getgid(int i, int j){
        if(i < 0 || i >= m || j < 0 || j >= n) return -1;
        return i*n + j;
    }
    
    bool isCyclicUtil(int v, unordered_map<int, unordered_set<int>>& graph, unordered_set<int>& visited, int parent){ 
        visited.insert(v);

        // cout << "visit " << v/n << ", " << v%n << endl;

        for(const int& nei : graph[v]){
            // cout << "look at " << nei/n << ", " << nei%n << endl;
            if(visited.find(nei) == visited.end()){
                if(isCyclicUtil(nei, graph, visited, v)){
                    // cout << nei/n << ", " << nei%n << " not visited and iscyclic" << endl;
                    return true;
                }
            }else if(nei != parent){
                /*
                consider the graph:
                0<->1, 0<->2 and 2<->1
                we go to 0, mark it as visited, 
                then go to 1, and mark it as visited,
                then go to 2 from 1, then 2's parent is 1.
                note that 2 has another nei, which is 0,
                and 0 is not 2's parent,
                so there is a cycle.
                (2 and its neighbor 0 has common ancestor,
                so 2 and 0 are already connected indirectly,
                and 2 and 0 are also the neighbor to each other,
                so there are 2 paths from 2 to 0,
                so we can say there is a cycle)
                */
                // cout << nei/n << ", " << nei%n << " in rec stack" << endl;
                return true;
            }
        }
        
        return false; 
    } 
    
    bool containsCycle(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        vector<vector<int>> dirs = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };
        
        //build graph
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int gid = getgid(i, j);
                char c = grid[i][j];
                
                for(vector<int>& dir : dirs){
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    int ngid = getgid(ni, nj);
                    if(ngid == -1) continue;
                    if(c == grid[ni][nj]){
                        // cout << "c: " << c << ", " << i << ", " << j << "<->" << ni << ", " << nj << endl;
                        graphs[c][gid].insert(ngid);
                        graphs[c][ngid].insert(gid);
                        nodes[c].insert(gid);
                        nodes[c].insert(ngid);
                    }
                }
            }
        }
        
        //check graphs corresponding to different chars
        for(auto it = graphs.begin(); it != graphs.end(); ++it){
            char c = it->first;
            unordered_map<int, unordered_set<int>>& graph = it->second;
            
            // cout << "look at " << c << ", nodes: " << nodes[c].size() << ", edges: " << graph.size() << endl;
            
            if(nodes[c].size() < 4) continue;
             
            unordered_set<int> visited;
            unordered_set<int> recStack;
            
            for(const int& node : nodes[c]){
                // cout << "node: " << node/n << ", " << node%n << endl;
                if(visited.find(node) != visited.end()) continue;
                if(isCyclicUtil(node, graph, visited, -1)){
                    return true; 
                }
            }
        }
        
        return false;
    }
};

//dfs, detect cycle in undirected graph, cleaner
//https://leetcode.com/problems/detect-cycles-in-2d-grid/discuss/805677/DFS-or-Simple-Explanation
//Runtime: 832 ms, faster than 20.00% of C++ online submissions for Detect Cycles in 2D Grid.
//Memory Usage: 98.4 MB, less than 20.00% of C++ online submissions for Detect Cycles in 2D Grid.
class Solution {
public:
    int m, n;
    vector<vector<bool>> visited;
    vector<vector<int>> dirs;
    
    bool dfs(int r, int c, int pr, int pc, vector<vector<char>>& grid){
        visited[r][c] = true;
        
        for(vector<int>& dir : dirs){
            int nr = r + dir[0];
            int nc = c + dir[1];
            //neighbor must be valid
            if(nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;
            //neighbor's color must be the same as cur's
            if(grid[r][c] != grid[nr][nc])
                continue;
            if(!visited[nr][nc]){
                if(dfs(nr, nc, r, c, grid)){
                    return true;
                }
            }else if(!(nr == pr && nc == pc)){
                //neighbor is not parent
                return true;
            }
        }
        
        return false;
    };
    
    bool containsCycle(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        dirs = {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(!visited[i][j]){
                    if(dfs(i, j, -1, -1, grid)){
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
};

//Union find
//https://www.geeksforgeeks.org/union-find/
//Runtime: 596 ms, faster than 60.00% of C++ online submissions for Detect Cycles in 2D Grid.
//Memory Usage: 45.6 MB, less than 20.00% of C++ online submissions for Detect Cycles in 2D Grid.
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    int unite(int x, int y){
        //merge the larger into the smaller
        if(x > y){
            swap(x, y);
        }
        
        //they are already in the same union
        if(parent[find(y)] == find(x)){
            return -1;
        }
        
        //merge y into x
        parent[find(y)] = find(x);
        /*
        this line is not:
        parent[y] = find(x);
        If so, it will give WA, 73 / 74 test cases passed.
        */
        return 0;
    }
};

class Solution {
public:
    int m, n;
    
    int getgid(int r, int c){
        return r*n + c;
    };
    
    bool containsCycle(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        DSU dsu(m*n);
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(i-1 >= 0 && grid[i][j] == grid[i-1][j]){
                    if(dsu.unite(getgid(i-1, j), getgid(i,j)))
                        return true;
                }
                if(j-1 >= 0 && grid[i][j] == grid[i][j-1]){
                    if(dsu.unite(getgid(i, j-1), getgid(i,j)))
                        return true;
                }
            }
        }
        
        return false;
    }
};
