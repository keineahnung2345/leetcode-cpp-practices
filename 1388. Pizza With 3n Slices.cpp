//https://leetcode.com/problems/pizza-with-3n-slices/discuss/547699/C%2B%2B-Simple-DP
//Runtime: 24 ms, faster than 27.27% of C++ online submissions for Pizza With 3n Slices.
//Memory Usage: 12.4 MB, less than 100.00% of C++ online submissions for Pizza With 3n Slices.
class Solution {
public:
    int maxSizeSlices(vector<int>& slices, int l, int r){
        //l and r are inclusive
        int N = slices.size();
        int k = N/3; //we can take k pieces
        vector<vector<int>> dp(N, vector<int>(k, 0));
        
        for(int i = l; i <= r; i++){
            for(int j = 0; j < k; j++){
                /*
                1. don't take current piece
                2. take current piece, plus the value when we take (j-1)th piece of cake at position (i-2)
                */
                dp[i][j] = max((i-1 >= 0 ? dp[i-1][j] : 0), 
                    (((i-2 >= 0) && (j-1 >= 0)) ? dp[i-2][j-1] : 0) + slices[i]);
            }
        }
        
        return dp[r][k-1];
    };
    
    int maxSizeSlices(vector<int>& slices) {
        int N = slices.size();
        return max(maxSizeSlices(slices, 0, N-2),
                   maxSizeSlices(slices, 1, N-1));
    }
};
