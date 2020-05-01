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

//Recursion?
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Arithmetic Slices.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Arithmetic Slices.
//time: O(N), space: O(N)
class Solution {
public:
    int sum = 0;
    
    int slices(vector<int>& A, int i){
        if(i < 2) return 0;
        int ap = 0;
        if(A[i] - A[i-1] == A[i-1] - A[i-2]){
            /*
            A[0...i]'s subsequence's count is that of A[0...i-1] + 1
            */
            ap = 1 + slices(A, i-1);
            sum += ap;
        }else{
            slices(A, i-1);
        }
        // cout << i << ", " << ap << ", " << sum << endl;
        return ap;
    };
    
    int numberOfArithmeticSlices(vector<int>& A) {
        slices(A, A.size()-1);
        return sum;
    }
};

//1-D DP
//Runtime: 4 ms, faster than 45.89% of C++ online submissions for Arithmetic Slices.
//Memory Usage: 7.5 MB, less than 100.00% of C++ online submissions for Arithmetic Slices.
//time: O(N), space: O(N)
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        vector<int> dp(n);
        int ans = 0;
        
        for(int r = 2; r < n; r++){
            if(A[r] - A[r-1] == A[r-1] - A[r-2]){
                /*
                dp[r-1] : count of arithmetic slices ending at r-1
                suppose these are [r-k...r-1], ..., [r-3...r-1]
                dp[r] : [r-k...r], ..., [r-3...r], its count is then be dp[r-1]+1
                */
                dp[r] = dp[r-1] + 1;
                ans += dp[r];
            }
        }
        
        return ans;
    }
};

//O(1) space DP
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Arithmetic Slices.
//Memory Usage: 7.4 MB, less than 100.00% of C++ online submissions for Arithmetic Slices.
//time: O(N), space: O(1)
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        int dp = 0;
        int ans = 0;
        
        for(int r = 2; r < n; r++){
            if(A[r] - A[r-1] == A[r-1] - A[r-2]){
                //we only need last dp value
                dp += 1;
                ans += dp;
            }else{
                //need to reset dp value!
                dp = 0;
            }
        }
        
        return ans;
    }
};
