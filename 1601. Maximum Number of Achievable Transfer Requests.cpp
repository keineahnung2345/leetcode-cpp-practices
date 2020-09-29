//TLE
//dfs, cycle detection
//10 / 117 test cases passed.
class Solution {
public:
    bool hasCycle(int cur, vector<unordered_map<int, int>>& graph, 
        vector<bool>& visited, vector<bool>& recStack, vector<int>& cycle){
        if(!visited[cur]){
            visited[cur] = true;
            recStack[cur] = true;

            for(const pair<int, int>& p : graph[cur]){
                int nei = p.first;
                if(recStack[nei]){
                    cycle.insert(cycle.begin(), nei);
                    return true;
                }
                if(!visited[nei] && hasCycle(nei, graph, visited, recStack, cycle)){
                    cycle.insert(cycle.begin(), nei);
                    return true;
                }
            }
        }
        
        recStack[cur] = false;
        
        return false;
    };
    
    int maximumRequests(int n, vector<vector<int>>& requests) {
        //src -> (dst, count)
        vector<unordered_map<int, int>> graph(n);
        
        for(const vector<int>& req : requests){
            ++graph[req[0]][req[1]];
        }
        
        // for(int src = 0; src < n; ++src){
        //     cout << src << " : ";
        //     for(const pair<int,int>& p : graph[src]){
        //         cout << "(" << p.first << ", " << p.second << ") ";
        //     }
        //     cout << endl;
        // }
        
        int ans = 0;
        
        
        bool stop = true;
        
        do{
            stop = true;
            // cout << "hello" << endl;
            vector<bool> visited(n, false);
            vector<bool> recStack(n, false);
            for(int p = 0; p < n; ++p){
                vector<int> cycle;
                if(!graph[p].empty() && 
                   !visited[p] && hasCycle(p, graph, visited, recStack, cycle)){
                    ans += cycle.size();

                    //remove cycle from graph
                    // cout << "cycle: ";
                    for(int i = 0; i < cycle.size(); ++i){
                        int start = cycle[i];
                        int end = (i+1 < cycle.size()) ? cycle[i+1] : cycle[0];
                        // cout << start << " -> ";
                        --graph[start][end];
                        if(graph[start][end] == 0){
                            graph[start].erase(end);
                        }
                    }
                    // cout << endl;
                    
                    stop = false;
                }
            }
        }while(!stop);
        
        
        // for(int src = 0; src < n; ++src){
        //     cout << src << " : ";
        //     for(const pair<int,int>& p : graph[src]){
        //         cout << "(" << p.first << ", " << p.second << ") ";
        //     }
        //     cout << endl;
        // }
        
        return ans;
    }
};
