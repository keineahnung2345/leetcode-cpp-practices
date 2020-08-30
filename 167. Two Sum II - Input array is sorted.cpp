/**
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

Your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution and you may not use the same element twice.
Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
**/

/**
Runtime: 12 ms, faster than 69.38% of C++ online submissions for Two Sum II - Input array is sorted.
Memory Usage: 9.7 MB, less than 72.70% of C++ online submissions for Two Sum II - Input array is sorted.
**/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        
        int i = 0, j = n-1;
        
        while(i < j){
            if(numbers[i] + numbers[j] == target){
                return {i+1, j+1};
            }else if(numbers[i] + numbers[j] > target){
                --j;
            }else{
                ++i;
            }
        }
        
        return {0,0};
    }
};
