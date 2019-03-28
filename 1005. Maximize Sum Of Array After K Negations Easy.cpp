/**
Given an array A of integers, we must modify the array in the following way: we choose an i and replace A[i] with -A[i], and we repeat this process K times in total.  (We may choose the same index i multiple times.)

Return the largest possible sum of the array after modifying it in this way.

 

Example 1:

Input: A = [4,2,3], K = 1
Output: 5
Explanation: Choose indices (1,) and A becomes [4,-2,3].
Example 2:

Input: A = [3,-1,0,2], K = 3
Output: 6
Explanation: Choose indices (1, 2, 2) and A becomes [3,1,0,2].
Example 3:

Input: A = [2,-3,-1,5,-4], K = 2
Output: 13
Explanation: Choose indices (1, 4) and A becomes [2,3,-1,5,4].
 

Note:

1 <= A.length <= 10000
1 <= K <= 10000
-100 <= A[i] <= 100
**/

//Runtime: 20 ms, faster than 10.38% of C++ online submissions for Maximize Sum Of Array After K Negations.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Maximize Sum Of Array After K Negations.
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        for(int i = 0; i < K; i++){
            //every time reverse the smallest element
            vector<int>::iterator it = min_element(A.begin(), A.end());
            *it = -*it;
        }
        
        return accumulate(A.begin(), A.end(), 0);
    }
};
