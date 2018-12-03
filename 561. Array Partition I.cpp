/**
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
**/

//Your runtime beats 8.12 % of cpp submissions. using sort()
//Your runtime beats 31.66 % of cpp submissions. using qsort()

class Solution {
public:
    static int compare (const void * a, const void * b)
    {
      return ( *(int*)a - *(int*)b );
    }
    
    int arrayPairSum(vector<int>& nums) {
        int ans = 0;
        // sort(nums.begin(), nums.end());
        
        //https://stackoverflow.com/questions/12308243/trying-to-use-qsort-with-vector
        qsort(&nums[0], nums.size(), sizeof(int), compare);
        
        for(int i = 0; i < nums.size(); i++){
            if(i%2==0) ans+=nums[i];
        }
        return ans;
    }
};
