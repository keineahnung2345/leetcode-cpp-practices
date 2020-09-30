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

//enumerate all combination of requests
//https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/discuss/866456/Python-Check-All-Combinations
//Runtime: 1468 ms, faster than 10.64% of C++ online submissions for Maximum Number of Achievable Transfer Requests.
//Memory Usage: 357.3 MB, less than 5.03% of C++ online submissions for Maximum Number of Achievable Transfer Requests.
//time: O((N+R)*(2^R)), space: O(N)
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int nr = requests.size();
        int ans = 0;
        
        //enumerate all combination of requests
        for(int comb = 0; comb < (1 << nr); ++comb){
            vector<int> out(n), in(n);
            
            for(int i = 0; i < nr; ++i){
                // cout << comb << " " << i << endl;
                if(comb & (1 << i)){
                    //requests[i] is chosen
                    ++out[requests[i][0]];
                    ++in[requests[i][1]];
                }
            }
            
            if(in == out){
                ans = max(ans, accumulate(out.begin(), out.end(), 0));
            }
        }
        
        return ans;
    }
};

//backtracking
//https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/discuss/866387/Java-Backtracking-Straightforward-No-Bit-Masking
//Runtime: 212 ms, faster than 71.74% of C++ online submissions for Maximum Number of Achievable Transfer Requests.
//Memory Usage: 9.1 MB, less than 81.09% of C++ online submissions for Maximum Number of Achievable Transfer Requests.
class Solution {
public:
    void backtrack(vector<vector<int>>& requests, int start, 
                   vector<int>& in, vector<int>& out, int& ans){
        if(start == requests.size()){
            if(in == out){
                ans = max(ans, accumulate(in.begin(), in.end(), 0));
            }
        }else{
            // don't need the for loop here!
            // for each request, we only have two choices: choose or not choose
            // for(int i = start; i < requests.size(); ++i){
            // }
            //not choose requests[i]
            backtrack(requests, start+1, in, out, ans);

            //choose requests[i]
            ++out[requests[start][0]];
            ++in[requests[start][1]];
            backtrack(requests, start+1, in, out, ans);
            --out[requests[start][0]];
            --in[requests[start][1]];
        }
    }
    
    int maximumRequests(int n, vector<vector<int>>& requests) {
        vector<int> in(n), out(n);
        int ans = 0;
        
        backtrack(requests, 0, in, out, ans);
        
        return ans;
    }
};
