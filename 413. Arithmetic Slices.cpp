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

//Approach #2 Better Brute Force
//time: O(N^2), space: O(1)
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int ans = 0;
        int n = A.size();
        
        for(int l = 0; l+2 < n; l++){
            int d = A[l+1] - A[l];
            //looking at [l...l+2], [l...l+3], [l...l+4], [l...n-1]
            for(int r = l+2; r < n; r++){
                //only check last pair to determine if a slice is valid
                if(A[r] - A[r-1] == d){
                    ans++;
                }else{
                    //skip all [l...r+1], ... [l...n-1] if [l...r] is invalid
                    break;
                }
            }
        }
        
        return ans;
    }
};
