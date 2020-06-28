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
