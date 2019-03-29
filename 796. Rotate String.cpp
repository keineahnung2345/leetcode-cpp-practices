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

/**
Approach #1: Brute Force [Accepted]
Complexity Analysis

Time Complexity: O(N^2)O(N 
2
 ), where NN is the length of A. For each rotation s, we check up to NN elements in A and B.

Space Complexity: O(1)O(1). We only use pointers to elements of A and B.
**/

/**
Approach #2: Simple Check [Accepted]
Intuition and Algorithm

All rotations of A are contained in A+A. Thus, we can simply check whether B is a substring of A+A. We also need to check A.length == B.length, otherwise we will fail cases like A = "a", B = "aa".
**/
/**
Complexity Analysis

Time Complexity: O(N^2)O(N 
2
 ), where NN is the length of A.

Space Complexity: O(N)O(N), the space used building A+A.
**/
/**
class Solution {
public:
    bool rotateString(string A, string B) {
        return A.size() == B.size() && (A+A).find(B)!=string::npos;
    }
};
**/


