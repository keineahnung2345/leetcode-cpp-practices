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

//Approach #1 Recursion, Min-Max algorithm
//Runtime: 276 ms, faster than 5.16% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for Predict the Winner.
//time: O(2^n), space: O(n)
class Solution {
public:
    int winner(vector<int>& nums, int s, int e, int turn){
        if(s == e) return turn * nums[s];
        int a = turn * nums[s] + winner(nums, s+1, e, -turn);
        int b = turn * nums[e] + winner(nums, s, e-1, -turn);
        /*
        for player2, it equals to -max(-a,-b) = min(a, b)
        it want to minimize the score
        */
        return turn * max(turn*a, turn*b);
    };
    
    bool PredictTheWinner(vector<int>& nums) {
        //it calculates Player1's score - Player2's score
        return winner(nums, 0, nums.size()-1, 1) >= 0;
    }
};

//Approach #2 Similar Approach, Recursion, min-max, memorization
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for Predict the Winner.
//time: O(n^2), space: O(n^2)
class Solution {
public:
    vector<vector<int>> memo;
    
    int winner(vector<int>& nums, int s, int e){
        if(memo[s][e] != -1) return memo[s][e];
        if(s == e){
            memo[s][e] = nums[s];
            return memo[s][e];
        }
        //score's definition is still player1' score - player2's score
        //notice the minus sign here
        int a = nums[s] - winner(nums, s+1, e);
        int b = nums[e] - winner(nums, s, e-1);
        memo[s][e] = max(a, b);
        return memo[s][e];
    };
    
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        memo = vector(n, vector(n, -1));
        
        winner(nums, 0, n-1);
        return memo[0][n-1] >= 0;
    }
};

//Approach #3 O(n^2) space Dynamic Programming
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.6 MB, less than 100.00% of C++ online submissions for Predict the Winner.
//time: O(n^2), space: O(n^2)
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp = vector(n, vector(n, 0));
        
        for(int s = n-1; s >= 0; s--){
            for(int e = s+1; e < n; e++){
                /*
                if e == s+1, dp[s+1][e] and dp[s][e-1] equal to 0,
                so a = nums[s] and b = nums[e],
                this is edge case
                */
                /*
                note that we use dp[s+1] here, 
                so we should iterate s in reverse order
                */
                int a = nums[s] - dp[s+1][e];
                /*
                note that we use dp[s][e-1] here, 
                so we should iterate e in increasing order
                */
                int b = nums[e] - dp[s][e-1];
                dp[s][e] = max(a, b);
            }
        }
        
        return dp[0][n-1] >= 0;
    }
};

//Approach #4 O(n) space Dynamic Programming
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Predict the Winner.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Predict the Winner.
//time: O(n^2), space: O(n)
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        for(int s = n-2; s >= 0; s--){
            for(int e = s+1; e < n; e++){
                //dp[e] is dp[s+1][e] in previous approach
                int a = nums[s] - dp[e];
                /*
                dp[e-1] is dp[s][e-1] in previous approach,
                because we increase e in each iteration,
                when we are calculating dp[e], dp[e-1] is already calculated
                */
                int b = nums[e] - dp[e-1];
                //we can overwrite the only row
                dp[e] = max(a, b);
            }
        }
        return dp[n-1] >= 0;
    }
};
