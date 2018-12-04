/**
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
**/

//Your runtime beats 53.22 % of cpp submissions.
class Solution {
public:
    static int toggle(int x){return 1-x;}
    int matrixScore(vector<vector<int>>& A) {
        int rows = A.size();
        int cols = A[0].size();
        
        //toggle a row when its first element is 0
        for(int i = 0; i < rows; i++){
            if(A[i][0]!=1){
                //in-place map elements of v to the function toggle
                transform(A[i].begin(), A[i].end(), A[i].begin(), toggle);
            }
            // copy(A[i].begin(), A[i].end(), ostream_iterator<int>(cout, " "));
            // cout << endl;
        }
        
        int sum = 0;
        //toggle columns and calculate the sum simultaneously
        for(int j = 0; j < cols; j++){
            int colSum = 0;
            for(int i = 0; i < rows; i++){
                colSum += A[i][j];
            }
            //toggle a column if toggling makes its sum bigger
            //, i.e. the original sum <= A.size()/2
            // cout << j << "'th colSum: " << colSum << ", rows/2: " << rows/2 << ", rows: " << rows << endl;
            colSum = colSum <= rows/2 ? rows-colSum : colSum;
            // cout << j << "'th colSum: " << colSum << ",shift: " << (cols-1-j) << ",final col sum: " << (colSum<<(cols-1-j)) << endl;
            sum += colSum<<(cols-1-j);
        }
        return sum;
    }
};

/**
Approach 1: Brute Force
Intuition

Notice that a 1 in the iith column from the right, contributes 2^i2 
i
  to the score.

Say we are finished toggling the rows in some configuration. Then for each column, (to maximize the score), we'll toggle the column if it would increase the number of 1s.

We can brute force over every possible way to toggle rows.

Algorithm

Say the matrix has R rows and C columns.

For each state, the transition trans = state ^ (state-1) represents the rows that must be toggled to get into the state of toggled rows represented by (the bits of) state.

We'll toggle them, and also maintain the correct column sums of the matrix on the side.

Afterwards, we'll calculate the score. If for example the last column has a column sum of 3, then the score is max(3, R-3), where R-3 represents the score we get from toggling the last column.

In general, the score is increased by max(col_sum, R - col_sum) * (1 << (C-1-c)), where the factor (1 << (C-1-c)) is the power of 2 that each 1 contributes.

Note that this approach may not run in the time allotted.

//Java
class Solution {
    public int matrixScore(int[][] A) {
        int R = A.length, C = A[0].length;
        int[] colsums = new int[C];
        for (int r = 0; r < R; ++r)
            for (int c = 0; c < C; ++c)
                colsums[c] += A[r][c];

        int ans = 0;
        for (int state = 0; state < (1<<R); ++state) {
            // Toggle the rows so that after, 'state' represents
            // the toggled rows.
            if (state > 0) {
                int trans = state ^ (state-1);
                for (int r = 0; r < R; ++r) {
                    if (((trans >> r) & 1) > 0) {
                        for (int c = 0; c < C; ++c) {
                            colsums[c] += A[r][c] == 1 ? -1 : 1;
                            A[r][c] ^= 1;
                        }
                    }
                }
            }

            // Calculate the score with the rows toggled by 'state'
            int score = 0;
            for (int c = 0; c < C; ++c)
                score += Math.max(colsums[c], R - colsums[c]) * (1 << (C-1-c));
            ans = Math.max(ans, score);
        }

        return ans;
    }
}

Complexity Analysis

Time Complexity: O(2^R * R * C), where R, C is the number of rows and columns in the matrix.

Space Complexity: O(C) in additional space complexity. 

**/

/**
Approach 2: Greedy
Intuition

Notice that a 1 in the iith column from the right, contributes 2^i to the score.

Since 2^n > 2^{n-1} + 2^{n-2} + ... + 2^0, 
maximizing the left-most digit is more important than any other digit. 
Thus, the rows should be toggled such that the left-most column is either all 0 or all 1 
(so that after toggling the left-most column [if necessary], the left column is all 1.)

Algorithm

If we toggle rows by the first column (A[r][c] ^= A[r][0]), then the first column will be all 0.

Afterwards, the base score is max(col, R - col) where col is the column sum; 
and (1 << (C-1-c)) is the power of 2 that each 1 in that column contributes to the score.

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int R = A.size(), C = A[0].size();
        int ans = 0;
        for (int c = 0; c < C; ++c) {
            int col = 0;
            for (int r = 0; r < R; ++r){
                // cout << "r: " << r << ", c: " << c << ", A[r][c] ^ A[r][0]: " << (A[r][c] ^ A[r][0]) << endl;
                //toggle all rows to have 0 at head(we should toggle all rows' head to either 0 or 1)
                //^:XOR, 0 if operands are the same, 1 if different
                col += A[r][c] ^ A[r][0];
            }
            ans += max(col, R - col) * (1 << (C-1-c));
        }
        return ans;
    }
};

Complexity Analysis

Time Complexity: O(R∗C), R, C is the number of rows and columns in the matrix.

Space Complexity: O(1) in additional space complexity. 
**/
