//Runtime: 4 ms, faster than 80.00% of C++ online submissions for Running Sum of 1d Array.
//Memory Usage: 8.8 MB, less than 20.00% of C++ online submissions for Running Sum of 1d Array.
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        if(nums.size() < 2) return nums;
        
        for(int i = 1; i < nums.size(); i++){
            nums[i] += nums[i-1];
        }
        
        return nums;
    }
};
