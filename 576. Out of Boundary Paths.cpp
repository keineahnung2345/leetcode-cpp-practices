//dfs + memorization
//TLE
//22 / 94 test cases passed.
//without memorization: time: O(4^N), space: O(N)
//time: O(mnN), space: O(mnN)
class Solution {
public:
    int dp[51][50][50];
    int MOD = 1e9+7;
    
    int dfs(int m, int n, int N, int i, int j) {
        if(i < 0 || i == m || j < 0 || j == n) return 1;
        if(N == 0) return 0;
        if(dp[N][i][j] >= 0) return dp[N][i][j];
        
        int a = findPaths(m, n, N-1, i, j-1);
        int b = findPaths(m, n, N-1, i, j+1);
        int c = findPaths(m, n, N-1, i-1, j);
        int d = findPaths(m, n, N-1, i+1, j);
        
        return dp[N][i][j] = (((a+b)%MOD + c)%MOD +d) % MOD;
    }
    
    int findPaths(int m, int n, int N, int i, int j) {
        if(i < 0 || i == m || j < 0 || j == n) return 1;
        if(N == 0) return 0;
        
        memset(dp, -1, sizeof(dp));
        
        return dfs(m, n, N, i, j);
    }
};
