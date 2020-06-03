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
        
        //this only extends existing edges, so it gives WA!
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

//Floyd–Warshall(All Pairs Shortest Path)
//https://leetcode.com/problems/course-schedule-iv/discuss/660509/JavaPython-FloydWarshall-Algorithm-Clean-code-O(n3)
//Runtime: 1220 ms, faster than 20.27% of C++ online submissions for Course Schedule IV.
//Memory Usage: 62.1 MB, less than 100.00% of C++ online submissions for Course Schedule IV.
class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> connected(n, vector<bool>(n, false));
        
        for(auto pre : prerequisites){
            connected[pre[0]][pre[1]] = true;
        }
        
        for(int i = 0; i < n; i++){
            connected[i][i] = true;
        }
        
        //each time add a middle point
        for(int k = 0; k < n; k++){
            //check if the middle point make each pair of (i, j) connected
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    connected[i][j] = connected[i][j] || 
                        (connected[i][k] && connected[k][j]);
                }
            }
        }
        
        vector<bool> ans(queries.size());
        
        for(int i = 0; i < queries.size(); i++){
            ans[i] = connected[queries[i][0]][queries[i][1]];
        }
        
        return ans;
    }
};
