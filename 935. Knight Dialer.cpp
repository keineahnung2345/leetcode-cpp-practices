//Runtime: 328 ms, faster than 27.43% of C++ online submissions for Knight Dialer.
//Memory Usage: 23.2 MB, less than 57.37% of C++ online submissions for Knight Dialer.
class Solution {
public:
    int MOD = 1e9+7;
    vector<vector<int>> edges;
    vector<vector<int>> memo;
    
    int dfs(int cur, int N){
        if(N == 0) return 1;
        if(N == 1) return edges[cur].size();
        if(memo[cur][N] != -1) return memo[cur][N];
        
        memo[cur][N] = 0;

        for(int nei : edges[cur]){
            memo[cur][N] = (memo[cur][N] + dfs(nei, N-1)) % MOD;
        }
        return memo[cur][N];
    }
    
    int knightDialer(int N) {
        int ans = 0;
        edges = vector<vector<int>>(10);

        edges[0] = {4,6};
        edges[1] = {6,8};
        edges[2] = {7,9};
        edges[3] = {4,8};
        edges[4] = {3,9,0};
        edges[5] = {};
        edges[6] = {1,7,0};
        edges[7] = {2,6};
        edges[8] = {1,3};
        edges[9] = {2,4};
        
        memo = vector<vector<int>>(10, vector<int>(N, -1));
        
        for(int i = 0; i <= 9; i++){
            ans = (ans + dfs(i, N-1)) % MOD;
        }
        
        return ans;
    }
};
