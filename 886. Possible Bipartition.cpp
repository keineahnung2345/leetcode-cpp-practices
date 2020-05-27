//graph
//Approach 1: Depth-First Search
//time: O(N+E), space: O(N+E)
//Runtime: 488 ms, faster than 29.22% of C++ online submissions for Possible Bipartition.
//Memory Usage: 66.5 MB, less than 14.29% of C++ online submissions for Possible Bipartition.
class Solution {
public:
    vector<vector<int>> graph;
    map<int, int> color;
    
    bool dfs(int node, int c){
        if(color.find(node) != color.end()){
            //a conflict occurs if the color assigned is different from the color we want to assign
            return color[node] == c;
        }
        
        color[node] = c;
        
        for(int nei : graph[node]){
            if(!dfs(nei, 1-c)){
                return false;
            }
        }
        
        return true;
    }
    
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        //padding before
        graph = vector<vector<int>>(N+1);
        
        for(vector<int>& edge : dislikes){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        for(int node = 1; node <= N; ++node){
            //skip visited node
            if(color.find(node) == color.end() && 
              !dfs(node, 0) //try to assign the node to group 0 and see if it success
              ){
                return false;
            }
        }
        
        return true;
    }
};
