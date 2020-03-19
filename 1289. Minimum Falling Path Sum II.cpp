//Runtime: 32 ms, faster than 91.25% of C++ online submissions for Minimum Falling Path Sum II.
//Memory Usage: 13.1 MB, less than 100.00% of C++ online submissions for Minimum Falling Path Sum II.
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int m = arr.size(), n = arr[0].size();
        int ans = INT_MAX;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        //initialize dp's first row
        for(int j = 0; j < n; j++){
            dp[0][j] = arr[0][j];
        }
        
        for(int i = 1; i < m; i++){
            vector<int> last_row(dp[i-1].begin(), dp[i-1].end());
            // for(int e : last_row) cout << e << " ";
            // cout << endl;
            auto last_row_min_it = min_element(last_row.begin(), last_row.end());
            int last_row_min_idx = last_row_min_it - last_row.begin();
            // cout << "min at " << last_row_min_idx << endl;
            int last_row_min = *last_row_min_it;
            nth_element(last_row.begin(), last_row.begin()+1, last_row.end(), less<int>());
            int last_row_2min = last_row[1];
            // cout << "min: " << last_row_min << ", 2nd min: " << last_row_2min << endl;
            for(int j = 0; j < n; j++){
                if(j == last_row_min_idx){
                    dp[i][j] = arr[i][j] + last_row_2min;
                }else{
                    dp[i][j] = arr[i][j] + last_row_min;
                }
            }
        }
        // for(int e : dp[m-1]) cout << e << " ";
        // cout << endl;
        
        return *min_element(dp[m-1].begin(), dp[m-1].end());        
    }
};
