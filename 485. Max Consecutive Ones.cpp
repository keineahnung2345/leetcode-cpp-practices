/**
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
**/

//Runtime: 40 ms, faster than 63.46% of C++ online submissions for Max Consecutive Ones.
//Memory Usage: 11.9 MB, less than 55.07% of C++ online submissions for Max Consecutive Ones.
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int lastMax = 0, curMax = 0;
        for(int num : nums){
            if(num){
                curMax++;
            }else{
                lastMax = max(lastMax, curMax);
                curMax = 0;
            }
        }
        return max(lastMax, curMax);
    }
};
