//WA
//67 / 68 test cases passed.
/*
5
[[3,4],[2,3],[1,2],[0,1]]
[[0,4],[4,0],[1,3],[3,0]]
*/

class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        //bfs
        map<int, set<int>> graph;
        
        for(vector<int>& pre : prerequisites){
            graph[pre[0]].insert(pre[1]);
            for(auto it = graph.begin(); it != graph.end(); it++){
                if(it->second.find(pre[0]) != it->second.end()){
                    it->second.insert(pre[1]);
                }
            }
        }
        
        vector<bool> ans(queries.size(), false);
        
        for(int i = 0; i < queries.size(); i++){
            if(graph.find(queries[i][0]) == graph.end()){
                ans[i] = false;
            }else{
                ans[i] = (graph[queries[i][0]].find(queries[i][1]) != graph[queries[i][0]].end());
            }
        }
        
        return ans;
    }
};
