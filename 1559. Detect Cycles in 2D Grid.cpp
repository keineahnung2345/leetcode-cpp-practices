//detect cycle in undirected graph
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
