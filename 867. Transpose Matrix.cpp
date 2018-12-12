/**
Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal, switching the row and column indices of the matrix.

 

Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Example 2:

Input: [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
 

Note:

1 <= A.length <= 1000
1 <= A[0].length <= 1000
**/

//Your runtime beats 35.18 % of cpp submissions.
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        vector<vector<int>> B(A[0].size(), vector<int>(A.size(),0));
        for(int r = 0; r < A.size(); r++){
            for(int c = 0; c < A[0].size(); c++){
                B[c][r] = A[r][c];
            }
        }
        return B;
    }
};

/**
Approach 1: Copy Directly
Intuition and Algorithm

The transpose of a matrix A with dimensions R x C is a matrix ans with dimensions C x R for which ans[c][r] = A[r][c].

Let's initialize a new matrix ans representing the answer. Then, we'll copy each entry of the matrix as appropriate.

Complexity Analysis

Time Complexity: O(R * C), where R and C are the number of rows and columns in the given matrix A.

Space Complexity: O(R * C), the space used by the answer. 
**/
