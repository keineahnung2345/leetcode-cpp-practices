//TLE
//545 / 588 test cases passed.
class Solution {
public:
    int numSquares(int n) {
        //padding ahead
        vector<int> dp(n+1, 0);
        
        for(int i = 1; i*i <= n; ++i){
            dp[i*i] = 1;
        }
        
        for(int i = 1; i <= n; ++i){
            if(dp[i] == 0){
                //cout << "i: " << i << endl;
                int count = INT_MAX;
                for(int j = 1; j <= i/2; ++j){
                    //cout << j << " and " << i-j << " : " << dp[j] << " and " << dp[i-j] << endl;
                    count = min(count, dp[j] + dp[i-j]);
                }
                dp[i] = count;
                //cout << "i: " << i << ", dp[i]: " << dp[i] << endl;
            }
        }
        
        return dp[n];
    }
};

//DP
//https://leetcode.com/problems/perfect-squares/discuss/71488/Summary-of-4-different-solutions-(BFS-DP-static-DP-and-mathematics)
//Runtime: 320 ms, faster than 29.50% of C++ online submissions for Perfect Squares.
//Memory Usage: 9 MB, less than 69.72% of C++ online submissions for Perfect Squares.
class Solution {
public:
    int numSquares(int n) {
        //padding ahead
        vector<int> dp(n+1, 0);
        
        for(int i = 1; i <= n; ++i){
            int count = INT_MAX;
            /*
            i = j*j + (i-j*j) for j <= sqrt(i)
            */
            for(int j = 1; j*j <= i; ++j){
                count = min(count, dp[i-j*j]+1);
            }
            dp[i] = count;
        }
        
        return dp[n];
    }
};

//static DP
//https://leetcode.com/problems/perfect-squares/discuss/71512/Static-DP-C%2B%2B-12-ms-Python-172-ms-Ruby-384-ms
//Runtime: 8 ms, faster than 95.54% of C++ online submissions for Perfect Squares.
//Memory Usage: 6.2 MB, less than 84.31% of C++ online submissions for Perfect Squares.
class Solution {
public:
    int numSquares(int n) {
        //padding ahead
        /*
        https://leetcode.com/problems/perfect-squares/discuss/71512/Static-DP-C++-12-ms-Python-172-ms-Ruby-384-ms/173951
        it's not magic by C++, but from leetcode, to save computing, leetcode will not clear your initialization in each testcase. that means, if you use static, your previous caching will be used by later case. you know, this is cheating. and I don't recommend people to use leetcode specified code. in the real interview, you won't have the cheating chance.
        */
        static vector<int> dp = {0};
        
        while(dp.size() <= n){
            int i = dp.size();
            int count = INT_MAX;
            /*
            i = j*j + (i-j*j) for j <= sqrt(i)
            */
            // cout << "i: " << i << endl;
            for(int j = 1; j*j <= i; ++j){
                // cout << i-j*j << endl;
                count = min(count, dp[i-j*j]+1);
            }
            dp.push_back(count);
        }
        
        // cout << "n: " << n << endl;
        return dp[n];
    }
};
