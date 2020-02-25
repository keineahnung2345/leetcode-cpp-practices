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
