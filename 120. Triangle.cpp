//DP
//Runtime: 8 ms, faster than 60.43% of C++ online submissions for Triangle.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Triangle.
//time: O(N^2), space: O(N^2)
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector(n, 0));
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= i; j++){
                // cout << i << ", " << j << endl;
                if(i == 0){
                    dp[i][j] = triangle[i][j];
                }else{
                    //when j == 0, dp[i-1][j-1] is out of range
                    //when j == i, dp[i-1][j] is out of range
                    dp[i][j] = min(j > 0 ? dp[i-1][j-1] : INT_MAX, 
                                   j < i ? dp[i-1][j] : INT_MAX) + 
                                triangle[i][j];
                }
                // cout << dp[i][j] << " ";
            }
            // cout << endl;
        }
        
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};

//DP, O(n) space
//Runtime: 12 ms, faster than 26.32% of C++ online submissions for Triangle.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Triangle.
//time: O(N^2), space: O(N)
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n, 0);
        int ans = 0;
        int dp_is1_js1, dp_is1_j;
        
        for(int i = 0; i < n; i++){
            /*
            when j is 0, this is meaningless, 
            reset when meeting a new row
            */
            dp_is1_js1 = INT_MAX;
            for(int j = 0; j <= i; j++){
                dp_is1_j = dp[j];
                if(i == 0){
                    dp[j] = triangle[i][j];
                }else{
                    dp[j] = min(j > 0 ? dp_is1_js1 : INT_MAX, 
                                j < i ? dp[j] : INT_MAX) + 
                                triangle[i][j];
                }
                dp_is1_js1 = dp_is1_j;
            }
        }
        
        return *min_element(dp.begin(), dp.end());
    }
};
