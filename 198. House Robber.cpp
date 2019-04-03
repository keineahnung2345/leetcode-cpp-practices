//recursion
//TLE
/**
class Solution {
public:
    int robStart(vector<int>& nums, int s){
        if(s >= nums.size()) return 0;
        return nums[s] + max(robStart(nums, s+2), robStart(nums, s+3));
    }
    int rob(vector<int>& nums) {
        return max(robStart(nums, 0), robStart(nums, 1));
    }
};
**/

//DP
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for House Robber.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for House Robber.

class Solution {
public:
    vector<int> money;
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        else if(nums.size() == 1) return nums[0];
        
        int N = nums.size();
        money = nums;
        //so that we can access money[N]
        money.push_back(0);
        for(int i = N-3; i >= 0; i--){
            money[i] += max(money[i+2], money[i+3]);
        }
        return max(money[0], money[1]);
    }
};
