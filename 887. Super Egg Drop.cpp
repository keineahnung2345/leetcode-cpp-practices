//DP
//TLE
//64 / 121 test cases passed.
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K+1, vector(N+1, INT_MAX));
        
        for(int k = 1; k <= K; k++){
            for(int n = 0; n <= N; n++){
                if(k == 1){
                    dp[k][n] = n;
                    continue;
                }
                
                if(n == 0){
                    dp[k][n] = 0;
                    continue;
                }
                
                for(int i = 1; i <= n; i++){
                    dp[k][n] = min(dp[k][n], 
                       /*egg breaks at ith floor, 
                       remain k-1 eggs, 
                       and i-1 floors to try
                       */
                       max(dp[k-1][i-1],
                       /*
                       egg does not break, 
                       remain k eggs, 
                       and n-i floors to try
                       */
                           dp[k][n-i]
                       //drop once
                       )+1);
                    // cout << "i: " << i << ", choose: " << "dp[" << k-1 << "][" << i-1 << "]: " << dp[k-1][i-1] << ", and dp[" << k << "][" << n-i << "]: " << dp[k][n-i] << endl;
                }
                // cout << "(" << k << ", " << n << "): " << dp[k][n] << endl;
            }
        }
                                   
        return dp[K][N];
    }
};

//recursion DP + binary search to speed up
//https://github.com/keineahnung2345/fucking-algorithm/blob/note/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E9%AB%98%E6%A5%BC%E6%89%94%E9%B8%A1%E8%9B%8B%E9%97%AE%E9%A2%98.md
//Runtime: 144 ms, faster than 26.59% of C++ online submissions for Super Egg Drop.
//Memory Usage: 29.5 MB, less than 14.29% of C++ online submissions for Super Egg Drop.
class Solution {
public:
    vector<vector<int>> dp;
    
    int dfs(int K, int N){
        if(dp[K][N] != INT_MAX){
            return dp[K][N];
        }
        
        if(K == 1){
            dp[K][N] = N;
            return dp[K][N];
        }

        if(N == 0){
            dp[K][N] = 0;
            return dp[K][N];
        }

        int l = 1, r = N;

        /*
        think of dfs(K-1, mid-1) as a function of mid, 
        and it increases with mid
        think of dfs(K, N-mid) as a function of mid, 
        and it decreases with mid
        we want to find where they intersect
        i.e. use binary search to find "valley"
        */
        while(l <= r){
            int mid = l + (r-l)/2;
            /*
            note that we need to use such recursive way,
            because we won't visit "dp" in order
            */
            int broken = dfs(K-1, mid-1);
            int not_broken = dfs(K, N-mid);
            if(broken > not_broken){
                /*
                broken > not_broken means mid is too large,
                (broken is an increasing function of mid,
                not_broken is an decreasing function of mid)
                so go left
                */
                r = mid-1;
                dp[K][N] = min(dp[K][N], broken+1);
            }else{
                /*
                not_broken > broken means mid is too small,
                so go right
                */
                l = mid+1;
                dp[K][N] = min(dp[K][N], not_broken+1);
            }
        }
         
        return dp[K][N];
    }
    
    int superEggDrop(int K, int N) {
        dp = vector<vector<int>>(K+1, vector(N+1, INT_MAX));
        return dfs(K, N);
    }
};
