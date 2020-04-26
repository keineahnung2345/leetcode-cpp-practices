//DP
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for House Robber II.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for House Robber II.
class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return 0;
        if(N <= 3) return *max_element(nums.begin(), nums.end());
        vector<int> dpA = nums, dpB = nums;
        
        //0~N-2
        for(int i = N-3; i >= 0; i--){
            dpA[i] += max(((i+2 < N-1) ? dpA[i+2] : 0), 
                          ((i+3 < N-1) ? dpA[i+3] : 0));
        }
        
        //1~N-1
        for(int i = N-3; i >= 1; i--){
            dpB[i] += max(((i+2 < N) ? dpB[i+2] : 0), 
                          ((i+3 < N) ? dpB[i+3] : 0));
        }
        
        return max(max(dpA[0], dpA[1]), 
                   max(dpB[1], dpB[2]));
        
        // return max(dpA[0], dpB[1]);
    }
};

//DP, forward
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for House Robber II.
//Memory Usage: 6.3 MB, less than 100.00% of C++ online submissions for House Robber II.
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        if(n == 0) return 0;
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        
        vector<int> dpNoLast(n-1);
        vector<int> dpNoFirst(n); //padding 0 first
        
        dpNoLast[0] = nums[0];
        dpNoLast[1] = max(nums[0], nums[1]);
        
        for(int i = 2; i < dpNoLast.size(); i++){
            //if we rob the ith house, we can add dp[i-2] because there is no alear
            dpNoLast[i] = max(dpNoLast[i-1], dpNoLast[i-2]+nums[i]);
        }
        
        //start from index 1
        //index 0 is just used for padding
        dpNoFirst[1] = nums[1];
        dpNoFirst[2] = max(nums[1], nums[2]);
        
        for(int i = 3; i < dpNoFirst.size(); i++){
            //if we rob the ith house, we can add dp[i-2] because there is no alear
            dpNoFirst[i] = max(dpNoFirst[i-1], dpNoFirst[i-2]+nums[i]);
        }
        
        return max(dpNoLast.back(), dpNoFirst.back());
    }
};
