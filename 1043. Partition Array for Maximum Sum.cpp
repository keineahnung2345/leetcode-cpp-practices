//https://leetcode.com/problems/partition-array-for-maximum-sum/discuss/290863/JavaC%2B%2BPython-DP
//Runtime: 16 ms, faster than 74.57% of C++ online submissions for Partition Array for Maximum Sum.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Partition Array for Maximum Sum.

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        vector<int> dp(A.size());
        
        for(int i = 0; i < A.size(); i++){
            int curmax = 0;
            //split btw i-k and i-k+1, 0,...,i-k | (i-k+1, ... , i)
            //(i-k+1, ..., i) will all become curmax
            //from right to left
            for(int k = 1; k <= K && i-(k-1) >= 0; k++){
                curmax = max(curmax, A[i-(k-1)]);
                //dp[i-k] + (dp[i-(k-1)] + ... + dp[i])
                //dp[i-(k-1)], ..., dp[i] all become curmax
                dp[i] = max(dp[i], ((i-k >= 0) ? dp[i-k] : 0) + curmax * k);
            }
            cout << dp[i] << endl;
        }
        
        return dp[A.size()-1];
    }
};
