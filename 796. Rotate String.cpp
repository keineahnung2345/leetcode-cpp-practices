/**
We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
Note:

A and B will have length at most 100.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Rotate String.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Rotate String.

class Solution {
public:
    bool rotateString(string A, string B) {
        if(A.size() != B.size()) return false;
        if(A.size() == 0) return true;
        
        vector<int> candidateA;
        
        for(int i = 0; i < A.size(); i++){
            if(A[i] == B[0]){
                candidateA.push_back(i);
            }
        }
        
        for(int start : candidateA){
            bool isRotate = true;
            for(int i = 0; i < A.size(); i++){
                if(A[(start+i)%A.size()] != B[i]){
                    isRotate = false;
                    break;
                }
            }
            if(isRotate){
                return true;
            }
        }
        
        return false;
    }
};

