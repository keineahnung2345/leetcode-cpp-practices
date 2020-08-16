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

//DP
//Hint 1: Use dynamic programming. dp[i] is max jumps you can do starting from index i. Answer is max(dp[i]).
//Hint 2: dp[i] = 1 + max (dp[j]) where j is all indices you can reach from i.
//Runtime: 80 ms, faster than 53.12% of C++ online submissions for Jump Game V.
//Memory Usage: 15.6 MB, less than 31.53% of C++ online submissions for Jump Game V.
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        vector<pair<int, int>> parr(n);
        
        for(int i = 0; i < n; ++i){
            parr[i] = {i, arr[i]};
        }
        
        sort(parr.begin(), parr.end(), 
            [](const pair<int, int>& p, const pair<int, int>& q){
                return (p.second == q.second) ? p.first < q.first : p.second < q.second;
            });
        
        vector<int> dp(n, INT_MIN);
        int ans = 0;
        
        for(pair<int, int>& p : parr){
            dp[p.first] = 1;
            for(int k = p.first-1; k >= max(p.first-d, 0) && arr[k] < arr[p.first]; --k){
                dp[p.first] = max(dp[p.first], dp[k]+1);
            }
            for(int k = p.first+1; k <= min(p.first+d, n-1) && arr[k] < arr[p.first]; ++k){
                dp[p.first] = max(dp[p.first], dp[k]+1);
            }
            ans = max(ans, dp[p.first]);
            // cout << p.first << ", " << dp[p.first] << ", " << ans << endl;
        }
        
        return ans;
    }
};
