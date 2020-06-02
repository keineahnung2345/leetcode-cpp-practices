//0/1 Knapsack Problem
//https://leetcode.com/problems/partition-equal-subset-sum/discuss/90592/01-knapsack-detailed-explanation
//Runtime: 1032 ms, faster than 5.04% of C++ online submissions for Partition Equal Subset Sum.
//Memory Usage: 11 MB, less than 47.06% of C++ online submissions for Partition Equal Subset Sum.
//time: O(NW), space: O(NW)
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(); //number of objects
        int capacity = accumulate(nums.begin(), nums.end(), 0);
        if((capacity & 1) == 1) return false;
        capacity /= 2;
        
        /*
        the +1 is not padding, it's meaningful!
        i: number of objects in the backpack
        j: current weight of backpack
        dp[i][j]: whether the state: (i, j) exists or not
        our goal is to find out dp[n][capacity]
        */
        vector<vector<bool>> dp(n+1, vector<bool>(capacity+1, false));

        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= capacity; j++){
                if(i == 0 && j == 0){
                    //choose nothing, make up weight = 0
                    dp[i][j] = true;
                    continue;
                }else if(j == 0){
                    //make up weight = 0
                    dp[i][j] = true;
                    continue;
                }else if(i == 0){
                    //no object to choose, but need to make up weight j > 0
                    dp[i][j] = false;
                    continue;
                }
                /*
                not choose this object,
                so the weight remains the same(= j)
                */
                dp[i][j] = dp[i-1][j];
                /*
                need to check whether the remaining capacity 
                still allows us to choose object i:
                j >= nums[i] means we still have enough capacity
                
                note that dp[i] corresponds to nums[i-1]!!
                (because the i in dp[i] means number of items!)
                */
                if(j - nums[i-1] >= 0){
                    dp[i][j] = dp[i][j] | dp[i-1][j-nums[i-1]];
                }
            }
        }

        return dp[n][capacity];
    }
};

//optimization, O(N) space
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(); //number of objects
        int capacity = accumulate(nums.begin(), nums.end(), 0);
        if((capacity & 1) == 1) return false;
        capacity /= 2;
        
        /*
        the +1 is not padding, it's meaningful!
        i: number of objects in the backpack
        j: current weight of backpack
        dp[i][j]: whether the state: (i, j) exists or not
        our goal is to find out dp[n][capacity]
        */
        vector<bool> dp(capacity+1, false);

        dp[0] = true;
        
        for(int i = 1; i <= n; i++){
            for(int j = capacity; j >= 0; j--){
                if(j == 0){
                    dp[j] = false;
                }
                
                if(j - nums[i-1] >= 0){
                    dp[j] = dp[j] | dp[j-nums[i-1]];
                }
            }
        }

        return dp[capacity];
    }
};
