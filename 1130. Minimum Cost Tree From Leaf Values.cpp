//dp
//Runtime: 32 ms, faster than 10.62% of C++ online submissions for Minimum Cost Tree From Leaf Values.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Minimum Cost Tree From Leaf Values.

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        //step is window size-1
        for(int step = 1; step < n; step++){
            //start point
            for(int i = 0; i+step < n; i++){
                int j = i+step;
                //split point
                for(int k = i; k+1 <= j; k++){
                    int cur = dp[i][k] + dp[k+1][j] + *max_element(arr.begin()+i, arr.begin()+k+1) * *max_element(arr.begin()+k+1, arr.begin()+j+1);
                    
                    dp[i][j] = (dp[i][j] == 0) ? cur : min(dp[i][j], cur);
                    // dp[i][j] = min(dp[i][j], cur);
                    
                    // cout << "[" << i << " " << k << "] " << dp[i][k] << ", " << *max_element(arr.begin()+i, arr.begin()+k+1) << " [" << k+1 << " " << j << "]" << dp[k+1][j] << ", " << *max_element(arr.begin()+k+1, arr.begin()+j+1) << endl;
                }
            }
        }
        // cout << endl;
        
        return dp[0][n-1];
    }
};
