//DP
//TLE
//64 / 121 test cases passed.
//time: O(KN^2), space: O(KN)
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
//time: O(KNlogN), space: O(KN)
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

//DP, different definition
//https://github.com/keineahnung2345/fucking-algorithm/blob/note/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%B3%BB%E5%88%97/%E9%AB%98%E6%A5%BC%E6%89%94%E9%B8%A1%E8%9B%8B%E8%BF%9B%E9%98%B6.md
//time: O(KN), space: O(KN)
//Runtime: 12 ms, faster than 61.24% of C++ online submissions for Super Egg Drop.
//Memory Usage: 29.7 MB, less than 14.29% of C++ online submissions for Super Egg Drop.
class Solution {
public:
    int superEggDrop(int K, int N) {
        /*
        dp[k][m]: how many floor we can test if we have k eggs and can throw m times
        for k = 0(no eggs to throw) or m = 0(no chances to throw) dp[k][m] should be 0
        */
        vector<vector<int>> dp(K+1, vector(N+1, 0));
        int m = 0;
        
        //keep increasing m until dp[k][m] can test n floors
        while(dp[K][m] < N){
            m++;
            for(int k = 1; k <= K; k++){
                /*
                we throw an egg at current floor,
                if the egg does not break, we then go up, 
                we still have k eggs and m-1 times to throw eggs
                dp[k][m-1]: how many floors higher than current floor
                
                1: current floor
                
                if the egg breaks, we then go down,
                we still have k-1 eggs and m-1 times to throw eggs
                dp[k-1][m-1]: how many floors lower than current floor
                */
                dp[k][m] = dp[k][m-1] + 1 + dp[k-1][m-1];
            }
        }
        return m;
    }
};

//Approach 3: Mathematical
//time: O(KlogN), space: O(1)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Super Egg Drop.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Super Egg Drop.
class Solution {
public:
    int comb(int K, int N){
        /*
        N!/((N-K)! * K!)
        = N * (N-1) * (N-2) * ... * (N-(K-1)) / K!
        */
        
        int res = 1;
        
        for(int i = 1; i <= K; i++){
            res *= i * (N-(i-1));
        }
        
        return res;
    }
    
    /*
    f(T, K) -> N
    T: #moves, K: #eggs, N: #floors we can test
    
    // ...  = egg breaks + current try + egg not break
    f(T, K) = f(T-1, K-1) + 1 + f(T-1, K)
    
    now define g(T, K) = f(T, K) - f(T, K-1)
    g(T, K) = [f(T-1, K-1)-f(T-1, K-2)] + [f(T-1, K)-f(T-1, K-1)]
    = g(T-1, K-1) + g(T-1, K)
    
    they are just binomial coefficient! 
    (https://en.wikipedia.org/wiki/Binomial_coefficient)
    so g(T, K) = comb(T, K)
    
    now we can write f(T, K)
    = [f(T, K) - f(T, K-1)] + [f(T, K-1) - f(T, K-2)] + ... + [f(T,2)-f(T,1)] + f(T,1)
    = g(T, K) + g(T, K-1) + ... g(T, 2) + f(T, 1)
    because f(T, 1) = 1(only one eggs to try),
    and g(T, 1) = comb(T, 1) = T = f(T, 1)
    so f(T, K) = g(T, K) + g(T, K-1) + ... g(T, 2) + g(T, 1)
    = sigma(x = 1 to K) g(T, x)
    = sigma(x = 1 to K) comb(T, x)
    */
    int f_slow(int T, int K, int N){
        //T: #moves
        int res = 0;
        for(int x = 1; x <= K; x++){
            res += comb(K, N);
            if(res >= N) break;
        }
        return res;
    }
    
    //efficient version
    int f(int T, int K, int N){
        //T: #moves
        int comb_N_x = 1;
        int res = 0;
        /*
        comb_N_1: T/1 = T
        comb_N_2: T*(T-1)/2
        comb_N_3: T*(T-1)*(T-2)/(2*3)
        ...
        comb_N_K: T*(T-1)*(T-2)*...*(T-K)/K!
        */
        for(int x = 1; x <= K; x++){
            comb_N_x *= (T-(x-1));
            comb_N_x /= x;
            res += comb_N_x;
            if(res >= N) break;
        }
        return res;
    }
    
    int superEggDrop(int K, int N) {
        /*
        moves taken to decide what F is,
        it's in the range [1,N]
        
        note that when K=1 and N=1, 
        we need to take 1 move to decide what F is
        */
        int lo = 1, hi = N;
        
        //binary search to find a mid s.t. f(mid, K, N)
        while(lo <= hi){
            int mid = (lo+hi)/2;
            
            int tmp;
            if((tmp = f(mid, K, N)) == N){
                return mid;
            }else if(tmp < N){
                lo = mid+1;
            }else if(tmp > N){
                hi = mid-1;
            }
        }
        
        return lo;
    }
};
