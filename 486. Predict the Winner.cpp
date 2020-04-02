//recursion + memo
//Runtime: 4 ms, faster than 46.97% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Predict the Winner.
class Solution {
public:
    vector<int> nums;
    vector<vector<int>> memo;
    
    int scoreInRange(int i, int j){
        //i, j are inclusive
        if(j - i + 1 == 2) return max({nums[i], nums[j]});
        if(memo[i][j] != -1) return memo[i][j];
        
        memo[i][j] = max(
            nums[i] + accumulate(nums.begin()+i+1, nums.begin()+j+1, 0) - scoreInRange(i+1, j), 
            nums[j] + accumulate(nums.begin()+i, nums.begin()+j, 0) - scoreInRange(i, j-1)
            );
        
        return memo[i][j];
    };
    
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return true;
        this->nums = nums;
        
        memo = vector<vector<int>>(n, vector<int>(n, -1));
        
        scoreInRange(0, n-1);
        
        return memo[0][n-1] >= accumulate(nums.begin(), nums.end(), 0)/2.0;
    }
};

//DP
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Predict the Winner.
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return true;
        
        vector<vector<int>> dp = vector<vector<int>>(n, vector<int>(n, -1));
        
        for(int dist = 1; dist < n; dist++){
            for(int i = 0; i+dist < n; i++){
                int j = i+dist;
                if(dist == 1){
                    dp[dist][i] = max(nums[i], nums[j]);
                }else{
                    dp[dist][i] = max(
                        nums[i] + accumulate(nums.begin()+i+1, nums.begin()+j+1, 0)-dp[dist-1][i+1],
                        nums[j] + accumulate(nums.begin()+i, nums.begin()+j,0) - dp[dist-1][i]);
                }
            }
        }
        
        return dp[n-1][0] >= accumulate(nums.begin(), nums.end(), 0)/2.0;
    }
};
