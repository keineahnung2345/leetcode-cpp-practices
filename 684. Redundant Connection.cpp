//Sol Approach #1: DFS
//Runtime: 28 ms, faster than 11.45% of C++ online submissions for Redundant Connection.
//Memory Usage: 14.6 MB, less than 5.88% of C++ online submissions for Redundant Connection.
//time complexity: O(N^2), space complexity: O(N)
class Solution {
public:
    set<int> seen;
    int MAX_EDGE_VAL = 1000;
    
    bool dfs(vector<vector<int>>& graph, int source, int target){
        //check if source and target can be connected in graph
        if(seen.find(source) == seen.end()){
            seen.insert(source);
            if(source == target) return true;
            for(int nei : graph[source]){
                //if one success, return true
                if(dfs(graph, nei, target)) return true;
            }
        }
        //if all fail, return false
        return false;
    }
    
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<vector<int>> graph(MAX_EDGE_VAL+1);
        
        //check while building graph
        for(vector<int>& edge : edges){
            seen.clear();
            //if edge[0] and edge[1] can be connected through other edges
            if(!graph[edge[0]].empty() &&
              !graph[edge[1]].empty() && 
               dfs(graph, edge[0], edge[1])) {
                //then current edge is redundant
                return edge;
            }
            //insert the non-redundant edge into graph
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        return vector<int>();
    }
};

//Approach #2: Union-Find
//Runtime: 8 ms, faster than 79.50% of C++ online submissions for Redundant Connection.
//Memory Usage: 10.3 MB, less than 47.06% of C++ online submissions for Redundant Connection.
class DSU{
private:
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int size){
        parent = vector<int>(size);
        iota(parent.begin(), parent.end(), 0);
        rank = vector<int>(size);
    };
    
    int find(int x){
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    bool unite(int x, int y){
        int xp = find(x), yp = find(y);
        if(xp == yp){
            //x and y is already connected
            return false;
        }else if(rank[xp] < rank[yp]){
            //union-by-rank
            parent[xp] = yp;
        }else if(rank[xp] > rank[yp]){
            parent[yp] = xp;
        }else{
            parent[yp] = xp;
            rank[xp]++;
        }
        //now x and y is connected
        return true;
    };
};

class Solution {
public:
    int MAX_EDGE_VAL = 1000;
    
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        DSU dsu = DSU(MAX_EDGE_VAL+1);
        for(vector<int>& edge : edges){
            if(!dsu.unite(edge[0], edge[1])){
                return edge;
            }
        }
        return vector<int>();
    }
};

//WA
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // cout << edges.size() << endl;
        for(int i = edges.size()-1; i >= 0; i--){
            int x = edges[i][0], y = edges[i][1];
            bool first = false, second = false;
            for(int j = 0; j < i; j++){
                if(find(edges[j].begin(), edges[j].end(), x) != edges[j].end()){
                    first = true;
                }else if(find(edges[j].begin(), edges[j].end(), y) != edges[j].end()){
                    second = true;
                }
                if(first && second) return edges[i];
            }
            
        }
        return vector<int>();
    }
};
