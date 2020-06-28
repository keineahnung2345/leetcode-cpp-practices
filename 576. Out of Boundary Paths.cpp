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

//Approach 3: Dynamic Programming
//bottom-up DP
//Runtime: 12 ms, faster than 69.88% of C++ online submissions for Out of Boundary Paths.
//Memory Usage: 9.3 MB, less than 54.36% of C++ online submissions for Out of Boundary Paths.
//time: O(mnN), space: O(mn)
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        int MOD = 1e9+7;
        //how many possible ways to go to (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        //take 0 moves
        dp[i][j] = 1;
        
        //how many possible ways to cross the boundary
        int ans = 0;
        
        //take N moves
        while(N-- > 0){
            vector<vector<int>> tmp(m, vector<int>(n, 0));
            
            for(int i = 0; i < m; ++i){
                for(int j = 0; j < n; ++j){
                    //cross boundary, update ans
                    if(i == 0)   ans = (ans+dp[i][j])%MOD;
                    if(i == m-1) ans = (ans+dp[i][j])%MOD;
                    if(j == 0)   ans = (ans+dp[i][j])%MOD;
                    if(j == n-1) ans = (ans+dp[i][j])%MOD;
                    
                    //update (i,j)'s count, from 4 directions
                    int a = (i>0) ? dp[i-1][j] : 0;
                    int b = (i<m-1) ? dp[i+1][j] : 0;
                    int c = (j>0) ? dp[i][j-1] : 0;
                    int d = (j<n-1) ? dp[i][j+1] : 0;
                    
                    tmp[i][j] = (((a+b)%MOD + c)%MOD + d)%MOD;
                }
            }
            
            swap(dp, tmp);
        }
        
        return ans;
    }
};
