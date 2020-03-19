//Divide and conquer and memorization
//https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
//Runtime: 28 ms, faster than 27.14% of C++ online submissions for Burst Balloons.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Burst Balloons.
class Solution {
public:
    int burst(vector<vector<int>>& memo, vector<int>& nums, int left, int right){
        //we can only burst balloons in the range [left+1, right-1], which is empty
        if(left + 1 == right) return 0;
        if(memo[left][right] > 0) return memo[left][right];
        int ans = 0;
        for(int i = left+1; i <= right-1; i++){
            //balloon i is the last to be burst, so its neighbors are left and right
            ans = max(ans, 
                        nums[i]*nums[left]*nums[right] + 
                        burst(memo, nums, left, i) + 
                        burst(memo, nums, i, right)
                     );
        }
        memo[left][right] = ans;
        return memo[left][right];
    };
    
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int N = nums.size();
        
        vector<vector<int>> memo(N, vector<int>(N, 0));
        
        //we can burst balloons in the range (0,N-1) = [1,N-2]
        return burst(memo, nums, 0, N-1);
    }
};

//DP
//https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
//Runtime: 16 ms, faster than 89.04% of C++ online submissions for Burst Balloons.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Burst Balloons.
//time: O(n^3)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int N = nums.size();
        
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        //width: the valid width of range of balloons able to be burst
        for(int width = 1; width <= N-2; width++){
            for(int left = 0; left + width + 1 < N; left++){
                //left, right: the outer element of valid range
                int right = left + width + 1;
                //split is the position of last balloon to burst
                //its valid range is (left, right)
                for(int split = left+1; split <= right-1; split++){
                    dp[left][right] = max(dp[left][right],
                        nums[left]*nums[split]*nums[right] + 
                        dp[left][split] +
                        dp[split][right]);
                }
            }
        }
        
        return dp[0][N-1];
    }
};
