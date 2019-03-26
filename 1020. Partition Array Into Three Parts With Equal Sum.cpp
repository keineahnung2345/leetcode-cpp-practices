/**
Given an array A of integers, return true if and only if we can partition the array into three non-empty parts with equal sums.

Formally, we can partition the array if we can find indexes i+1 < j with (A[0] + A[1] + ... + A[i] == A[i+1] + A[i+2] + ... + A[j-1] == A[j] + A[j-1] + ... + A[A.length - 1])

 

Example 1:

Input: [0,2,1,-6,6,-7,9,1,2,0,1]
Output: true
Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
Example 2:

Input: [0,2,1,-6,6,7,9,-1,2,0,1]
Output: false
Example 3:

Input: [3,3,6,5,-2,2,5,1,-9,4]
Output: true
Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 

Note:

3 <= A.length <= 50000
-10000 <= A[i] <= 10000
**/

//Runtime: 80 ms, faster than 21.72% of C++ online submissions for Partition Array Into Three Parts With Equal Sum.
//Memory Usage: 12.5 MB, less than 100.00% of C++ online submissions for Partition Array Into Three Parts With Equal Sum.

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int sum = accumulate(A.begin(), A.end(), 0);
        int firstSum = 0;
        
        for(int s1 = 0; s1 < A.size()-1; s1++){
            firstSum += A[s1];
            if(firstSum*3 == sum){
                int secondSum = 0;
                for(int s2 = s1+1; s2 < A.size(); s2++){
                    secondSum += A[s2];
                    if(secondSum == firstSum) return true;
                }
            }
        }
        
        return false;
    }
};
