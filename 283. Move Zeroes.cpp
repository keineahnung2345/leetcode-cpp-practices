/**
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.
**/

//Runtime: 16 ms, faster than 99.76% of C++ online submissions for Move Zeroes.
//Memory Usage: 9.5 MB, less than 91.39% of C++ online submissions for Move Zeroes.
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int fast = 0, slow = 0;
        for(; fast < nums.size(); fast++){
            if(nums[fast]){
                nums[slow++] = nums[fast];
            }
        }
        
        for(; slow < nums.size(); slow++){
            nums[slow] = 0;
        }
    }
};
