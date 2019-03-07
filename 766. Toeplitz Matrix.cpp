/**
A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

Example 1:

Input:
matrix = [
  [1,2,3,4],
  [5,1,2,3],
  [9,5,1,2]
]
Output: True
Explanation:
In the above grid, the diagonals are:
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
In each diagonal all elements are the same, so the answer is True.
Example 2:

Input:
matrix = [
  [1,2],
  [2,2]
]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.
**/

//Runtime: 16 ms, faster than 98.28% of C++ online submissions for Toeplitz Matrix.
//Memory Usage: 12.4 MB, less than 64.08% of C++ online submissions for Toeplitz Matrix.
/**
Complexity Analysis

Time Complexity: O(M*N). 
(Recall in the problem statement that M, N are the number of rows and columns in matrix.)

Space Complexity: O(M+N).
**/
class Solution {
public:
    bool isDiagAllSame(vector<vector<int>>& matrix, int i, int j){
        //i, j: a point to identity a diagonal
        int base = matrix[i][j];
        bool allSame = true;
        
        i++;
        j++;
        
        while(i<matrix.size() && j<matrix[0].size()){
            if(matrix[i][j]!=base){
                allSame = false;
            }
            i++;
            j++;
        }
        return allSame;
    }
    
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        /*
        for M x N matrix
        (M-1, 0) -> (M-2, 0) -> ... -> (0, 0)
        -> (0, 1) -> (0, 2) -> (0, 3) -> (0, N-1)
        */
        for(int i = matrix.size()-1; i>=0; i--){
            if(!isDiagAllSame(matrix, i, 0)){
                return false;
            }
        }
        for(int j = 1; j<matrix[0].size(); j++){
            if(!isDiagAllSame(matrix, 0, j)){
                return false;
            }
        }
        return true;
    }
};
