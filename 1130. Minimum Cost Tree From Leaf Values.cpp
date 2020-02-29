//dp
//Runtime: 32 ms, faster than 10.62% of C++ online submissions for Minimum Cost Tree From Leaf Values.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Minimum Cost Tree From Leaf Values.
//time: O(N^3), space: O(N^2)

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

//https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/discuss/339959/One-Pass-O(N)-Time-and-Space
//merge node
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Minimum Cost Tree From Leaf Values.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Minimum Cost Tree From Leaf Values.
//time: O(N^2), space: O(N)
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int ans = 0;
        
        while(arr.size() > 1){
            auto min_it = min_element(arr.begin(), arr.end());
            int min_index = min_it - arr.begin();
            // merge with its left or right neighbor
            // it either neighbor not exist, use INT_MAX to replace it
            ans += min(min_index >= 1 ? arr[min_index-1]: INT_MAX,
                       min_index+1 < arr.size() ? arr[min_index+1] : INT_MAX) 
                   * (*min_it);
            // current node is already merged, 
            //it's now represented by the the larger value in same subtree
            arr.erase(arr.begin() + min_index);
        }
        
        return ans;
    }
};
