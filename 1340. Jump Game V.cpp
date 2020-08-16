//DFS
//TLE
//51 / 127 test cases passed.
class Solution {
public:
    unordered_map<int, unordered_set<int>> graph;
    
    void dfs(int cur, vector<bool>& visited, int jumps, int& max_jumps){
        max_jumps = max(max_jumps, jumps);
        for(const int& nei : graph[cur]){
            if(!visited[nei]){
                // cout << cur << ": " << jumps << "->" << nei << endl;
                visited[nei] = true;
                dfs(nei, visited, jumps+1, max_jumps);
                visited[nei] = false;
            }
        }
    };
    
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(i+d, n-1) && arr[i] > arr[j]; ++j){
                graph[i].insert(j);
            }
            for(int j = i-1; j >= max(i-d, 0) && arr[i] > arr[j]; --j){
                graph[i].insert(j);
            }
        }
        
        int max_jumps = 0;
        
        for(int start = 0; start < n; ++start){
            vector<bool> visited(n, false);
            visited[start] = true;
            int jumps = 0;
            dfs(start, visited, 1, jumps);
            max_jumps = max(max_jumps, jumps);
        }
        
        return max_jumps;
    }
};
