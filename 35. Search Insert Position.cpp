//Runtime: 8 ms, faster than 98.48% of C++ online submissions for Search Insert Position.
//Memory Usage: 8.9 MB, less than 97.84% of C++ online submissions for Search Insert Position.

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        //find the first number larger than target
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] >= target) return i;
        }
        //if target is the largest
        return nums.size();
    }
};
