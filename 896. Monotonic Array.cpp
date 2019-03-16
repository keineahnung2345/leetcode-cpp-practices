/**
An array is monotonic if it is either monotone increasing or monotone decreasing.

An array A is monotone increasing if for all i <= j, A[i] <= A[j].  An array A is monotone decreasing if for all i <= j, A[i] >= A[j].

Return true if and only if the given array A is monotonic.

 

Example 1:

Input: [1,2,2,3]
Output: true
Example 2:

Input: [6,5,4,4]
Output: true
Example 3:

Input: [1,3,2]
Output: false
Example 4:

Input: [1,2,4,5]
Output: true
Example 5:

Input: [1,1,1]
Output: true
 

Note:

1 <= A.length <= 50000
-100000 <= A[i] <= 100000
**/

/**
Time Complexity: O(N), where N is the length of A.
Space Complexity: O(1). 
**/

//Runtime: 88 ms, faster than 52.38% of C++ online submissions for Monotonic Array.
//Memory Usage: 16.1 MB, less than 9.16% of C++ online submissions for Monotonic Array.
class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        bool isIncreasing = true, isDecreasing = true;
        //length 1 or 2 A is default to monotonic
        for(int i = 0; i < A.size()-1; i++){
            if(A[i+1]-A[i]<0){
                isIncreasing = false;
            }
            if(A[i+1]-A[i]>0){
                isDecreasing = false;
            }
            if(!isIncreasing && !isDecreasing){
                return false;
            }
        }
        return isIncreasing || isDecreasing;
    }
};

