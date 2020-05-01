//DP
//Runtime: 212 ms, faster than 5.27% of C++ online submissions for Arithmetic Slices.
//Memory Usage: 149.1 MB, less than 6.25% of C++ online submissions for Arithmetic Slices.
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> dp(n, vector(n, INT_MIN));
        int ans = 0;
        
        for(int w = 2; w <= n; w++){
            for(int l = 0; l+w-1 < n; l++){
                int r = l+w-1;
                //base case
                if(w == 2){
                    // cout << l << ", " << r << endl;
                    dp[l][r] = A[r] - A[l];
                }else{
                    if((dp[l+1][r] != INT_MIN) && (dp[l+1][r] == dp[l][r-1])){
                        /*
                        [l...r] is valid only if 
                        windows of size w-1 are valid,
                        and the two windows' common differences are same
                        */
                        dp[l][r] = dp[l+1][r]+1;
                    }
                    if(dp[l][r] != INT_MIN){
                        // cout << l << ", " << r << endl;
                        ans++;
                    }
                }
            }
        }
        
        return ans;
    }
};
