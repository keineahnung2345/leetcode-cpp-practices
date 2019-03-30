/**
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:

Input: [1,2,3]
Output: 6
 

Example 2:

Input: [1,2,3,4]
Output: 24
 

Note:

The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.
**/

/**
Approach 2: Using Sorting
Another solution could be to sort the given numsnums array(in ascending order) and find out the product of the last three numbers.

But, we can note that this product will be maximum only if all the numbers in numsnums array are positive. But, in the given problem statement, negative elements could exist as well.

Thus, it could also be possible that two negative numbers lying at the left extreme end could also contribute to lead to a larger product if the third number in the triplet being considered is the largest positive number in the numsnums array.

Thus, either the product nums[0] \times nums[1] \times nums[n-1]nums[0]×nums[1]×nums[n−1] or nums[n-3] \times nums[n-2] \times nums[n-1]nums[n−3]×nums[n−2]×nums[n−1] will give the required result. Thus, we need to find the larger one from out of these values.
**/
/**
Complexity Analysis

Time complexity : O\big(n\log n\big)O(nlogn). Sorting the numsnums array takes n\log nnlogn time.

Space complexity : O(\log n)O(logn). Sorting takes O(\log n)O(logn) space. 
**/
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        return max(nums[0]*nums[1]*nums[n-1], nums[n-3]*nums[n-2]*nums[n-1]);
    }
};

/**
Approach 3: Single Scan
**/

/**
Complexity Analysis

Time complexity : O(n)O(n). Only one iteration over the numsnums array of length nn is required.

Space complexity : O(1)O(1). Constant extra space is used. 
**/

//Runtime: 48 ms, faster than 86.06% of C++ online submissions for Maximum Product of Three Numbers.
//Memory Usage: 10.9 MB, less than 97.89% of C++ online submissions for Maximum Product of Three Numbers.

/**
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        
        for(int n : nums){
            if(n <= min1){
                min2 = min1;
                min1 = n;
            }else if(n <= min2){
                min2 = n;
            }
            
            if(n >= max1){
                max3 = max2;
                max2 = max1;
                max1 = n;
            }else if(n >= max2){
                max3 = max2;
                max2 = n;
            }else if(n >= max3){
                max3 = n;
            }
        }
        return max(min1*min2*max1, max1*max2*max3);
    }
};
**/
