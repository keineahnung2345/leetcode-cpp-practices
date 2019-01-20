/**
Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

 

Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Note:

1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.
**/

//Runtime: 124 ms, faster than 100.00% of C++ online submissions for Squares of a Sorted Array.
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        for(int i = 0; i < A.size(); i++){
            A[i] *= A[i];
        }
        
        sort(A.begin(), A.end());
        
        return A;
    }
};

/**
Approach 1: Sort
Intuition and Algorithm

Create an array of the squares of each element, and sort them.

Complexity Analysis

Time Complexity: O(NlogN), where N is the length of A.

Space Complexity: O(N). 
**/

/**
Approach 2: Two Pointer
Intuition

Since the array A is sorted, loosely speaking it has some negative elements with squares in decreasing order, then some non-negative elements with squares in increasing order.

For example, with [-3, -2, -1, 4, 5, 6], we have the negative part [-3, -2, -1] with squares [9, 4, 1], and the positive part [4, 5, 6] with squares [16, 25, 36]. Our strategy is to iterate over the negative part in reverse, and the positive part in the forward direction.

Algorithm

We can use two pointers to read the positive and negative parts of the array - one pointer j in the positive direction, and another i in the negative direction.

Now that we are reading two increasing arrays (the squares of the elements), we can merge these arrays together using a two-pointer technique.
**/

/**
//Runtime: 104 ms, faster than 100.00% of C++ online submissions for Squares of a Sorted Array.
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int N = A.size();
        int forward = 0;
        while(forward < N && A[forward] < 0){
            forward++;
        }
        int backward = forward - 1; 
        
        //now A[forward] >=0 and A[backward] < 0
        
        vector<int> ans(N);
        int cursor = 0; 
        
        while(backward >= 0 && forward < N){
            if(A[backward]*A[backward] < A[forward]*A[forward]){
                ans[cursor++] = A[backward]*A[backward];
                backward--;
            } else{
                ans[cursor++] = A[forward]*A[forward];
                forward++;
            }
        }
        
        while(backward >= 0){
            ans[cursor++] = A[backward]*A[backward];
            backward--;
        }
        
        while(forward < N){
            ans[cursor++] = A[forward]*A[forward];
            forward++;
        }
        return ans;
    }
};
**/

/**
Complexity Analysis

Time Complexity: O(N), where N is the length of A.

Space Complexity: O(N). 
**/

