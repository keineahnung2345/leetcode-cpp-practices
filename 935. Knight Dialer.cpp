//recursion + memorization
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

//bottom-up DP
//Runtime: 344 ms, faster than 26.23% of C++ online submissions for Knight Dialer.
//Memory Usage: 21.7 MB, less than 58.60% of C++ online submissions for Knight Dialer.
class Solution {
public:
    int MOD = 1e9+7;
    vector<vector<int>> edges;
    vector<vector<int>> memo;
    
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
        
        vector<vector<int>> dp(10, vector<int>(N, 0));
        
        for(int n = 0; n < N; n++){
            for(int cur = 0; cur <= 9; cur++){
                if(n == 0){
                    dp[cur][n] = 1;
                }else if(n == 1){
                    dp[cur][n] = edges[cur].size();
                }else{
                    for(int nei : edges[cur]){
                        dp[cur][n] = (dp[cur][n] + dp[nei][n-1]) % MOD;
                    }
                }
                // cout << "(" << cur << ", " << n << "): " << dp[cur][n] << endl;
            }
        }
        
        for(int cur = 0; cur <= 9; cur++){
            ans = (ans + dp[cur][N-1]) % MOD;
        }
        
        return ans;
    }
};

//DP, space optimized
//Runtime: 184 ms, faster than 55.96% of C++ online submissions for Knight Dialer.
//Memory Usage: 6.1 MB, less than 88.12% of C++ online submissions for Knight Dialer.
class Solution {
public:
    int MOD = 1e9+7;
    vector<vector<int>> edges;
    vector<vector<int>> memo;
    
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
        
        vector<vector<int>> dp(2, vector<int>(10, 0));
        
        for(int n = 0; n < N; n++){
            for(int cur = 0; cur <= 9; cur++){
                if(n == 0){
                    dp[n%2][cur] = 1;
                }else if(n == 1){
                    dp[n%2][cur] = edges[cur].size();
                }else{
                    dp[n%2][cur] = 0;
                    for(int nei : edges[cur]){
                        dp[n%2][cur] = (dp[n%2][cur] + dp[(n-1)%2][nei]) % MOD;
                    }
                }
            }
        }
        
        for(int cur = 0; cur <= 9; cur++){
            ans = (ans + dp[(N-1)%2][cur]) % MOD;
        }
        
        return ans;
    }
};
