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
//time: O(N^3), space: O(N^2)
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

//BFS
//https://leetcode.com/problems/course-schedule-iv/discuss/662276/C%2B%2B-or-100-Faster-and-Memory-Optimized
//Runtime: 376 ms, faster than 92.70% of C++ online submissions for Course Schedule IV.
//Memory Usage: 66.2 MB, less than 100.00% of C++ online submissions for Course Schedule IV.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> connected(n, vector<bool>(n, false));
        vector<vector<int>> graph(n);
        
        for(auto pre : prerequisites){
            connected[pre[0]][pre[1]] = true;
            graph[pre[0]].push_back(pre[1]);
        }
        
        for(int i = 0; i < n; i++){
            connected[i][i] = true;
        }
        
        /*
        each time choose a starting point
        and see which nodes it can visit by bfs
        */
        for(int start = 0; start < n; start++){
            queue<int> q;
            vector<bool> visited(n, false);
            q.push(start);
            visited[start] = true;
            while(!q.empty()){
                int cur = q.front(); q.pop();
                
                for(int nei : graph[cur]){
                    if(!visited[nei]){
                        //start can connect to nei through bfs
                        connected[start][nei] = true;
                        visited[nei] = true;
                        q.push(nei);
                    }
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
