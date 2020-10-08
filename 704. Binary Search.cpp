/**
Given a sorted (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. If target exists, then return its index, otherwise return -1.


Example 1:

Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
Explanation: 2 does not exist in nums so return -1
 

Note:

You may assume that all elements in nums are unique.
n will be in the range [1, 10000].
The value of each element in nums will be in the range [-9999, 9999].
**/

//Runtime: 72 ms, faster than 91.56% of C++ online submissions for Binary Search.
//Memory Usage: 27.9 MB, less than 15.64% of C++ online submissions for Binary Search.
class Solution {
public:
    int bSearch(vector<int>& nums, int target, int start, int end){
        if(end < start) return -1;
        int mid = (start+end)/2;
        // cout << mid << endl;
        if(nums[mid] == target){
            return mid;
        }else if(target < nums[mid]){
            return bSearch(nums, target, start, mid-1);
        }else{
            return bSearch(nums, target, mid+1, end);
        }
    }
    
    int search(vector<int>& nums, int target) {
        return bSearch(nums, target, 0, nums.size()-1);
    }
};
