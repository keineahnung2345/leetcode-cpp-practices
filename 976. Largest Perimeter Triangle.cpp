/**
Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

 

Example 1:

Input: [2,1,2]
Output: 5
Example 2:

Input: [1,2,1]
Output: 0
Example 3:

Input: [3,2,3,4]
Output: 10
Example 4:

Input: [3,6,2,3]
Output: 8
 

Note:

3 <= A.length <= 10000
1 <= A[i] <= 10^6
**/

/**
Approach 1: Sort
Intuition

Without loss of generality, say the sidelengths of the triangle are a≤b≤c. 
The necessary and sufficient condition for these lengths to form a triangle of non-zero area is a+b>c.

Say we knew cc already.
There is no reason not to choose the largest possible a and b from the array. 
If a+b>c, then it forms a triangle, otherwise it doesn't.

Algorithm

This leads to a simple algorithm: Sort the array. 
For any c in the array, we choose the largest possible a≤b≤c: 
these are just the two values adjacent to c. 
If this forms a triangle, we return the answer.
**/

/**
Complexity Analysis
Time Complexity: O(NlogN), where N is the length of A.
Space Complexity: O(1). 
**/

//Runtime: 56 ms, faster than 64.97% of C++ online submissions for Largest Perimeter Triangle.
//Memory Usage: 10.7 MB, less than 99.20% of C++ online submissions for Largest Perimeter Triangle.

class Solution {
public:
    int largestPerimeterFromSorted(vector<int>& A){
        int cur = A.size();
        
        while(cur >= 3 && A[cur-3] + A[cur-2] <= A[cur-1]){
            cur--;
        }
        
        if(cur < 3){
            return 0;
        }
        
        return A[cur-3] + A[cur-2] + A[cur-1];
    }
    
    int largestPerimeter(vector<int>& A) {
        sort(A.begin(), A.end());
        return largestPerimeterFromSorted(A);
    }
};
