//DP
//https://leetcode.com/problems/ugly-number-ii/discuss/69364/My-16ms-C%2B%2B-DP-solution-with-short-explanation
//Runtime: 32 ms, faster than 36.62% of C++ online submissions for Ugly Number II.
//Memory Usage: 7.8 MB, less than 59.06% of C++ online submissions for Ugly Number II.
class Solution {
public:
    int nthUglyNumber(int n) {
        if(n <= 0) return 0;
        if(n == 1) return 1;
        
        vector<int> dp(n);
        int t2 = 0, t3 = 0, t5 = 0;
        
        dp[0] = 1;
        for(int i = 1; i < n; ++i){
            dp[i] = min({dp[t2]*2, dp[t3]*3, dp[t5]*5});
            /*
            when we go from 
            "t2: 2, t3: 1, t5: 1, i: 4, val: 5"
            to 
            "t2: 3, t3: 2, t5: 1, i: 5, val: 6",
            both t2 and t3 are increased,
            because 6 = dp[2]*2 = dp[1]*3 
            (dp[2] = 2, dp[3] = 3)
            we increase both t2 and t3 so that 6 won't be 
            visited again
            */
            if(dp[i] == dp[t2]*2) ++t2;
            if(dp[i] == dp[t3]*3) ++t3;
            if(dp[i] == dp[t5]*5) ++t5;
            // cout << "t2: " << t2 << ", t3: " << t3 << ", t5: " << t5 << ", i: " << i << ", val: " << dp[i] << endl;
        }
        
        return dp[n-1];
    }
};
