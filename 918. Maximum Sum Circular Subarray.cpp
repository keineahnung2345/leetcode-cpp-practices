//TLE
//94 / 109 test cases passed.
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        
        vector<vector<int>> dp(n, vector(n, INT_MIN));
        int ans = INT_MIN;
        
        //i: start
        for(int i = n-1; i >= 0; i--){
            //j: end
            //the upper bound(exclusive) changes from n to i+n -> circular
            for(int j = i; j < i+n; j++){
                //length 1 subarray
                if(i == j){
                    dp[i][j%n] = A[i];
                }else{
                    dp[i][j%n] = max({dp[i][j%n], 
                                    (dp[(i+1)%n][j%n] == INT_MIN) ? INT_MIN : A[i]+dp[(i+1)%n][j%n], 
                                    (dp[i][(j-1+n)%n] == INT_MIN) ? INT_MIN : dp[i][(j-1+n)%n]+A[j%n]
                                    });
                }
                
                // if(dp[i][j%n] > ans){
                //     cout << "[" << i << ", " << j << "]: " << dp[i][j%n] << endl;
                // }
                ans = max(ans, dp[i][j%n]);
            }
        }
        
        return ans;
    }
};

//Kanade's Algorithm
//https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d
//O(n)
/*
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int n = A.size();
        int localMax = INT_MIN; // max sum of subarray which ends at i
        int globalMax = INT_MIN;
        
        for(int i = 0; i < n; i++){
            //enlong the old subarray or create a new one starting from i
            localMax = max(A[i], (localMax == INT_MIN) ? INT_MIN : A[i] + localMax);
            globalMax = max(globalMax, localMax);
        }
        
        return globalMax;
    }
};
*/
