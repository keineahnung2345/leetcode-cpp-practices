//Runtime: 360 ms, faster than 16.09% of C++ online submissions for Count Square Submatrices with All Ones.
//Memory Usage: 16 MB, less than 100.00% of C++ online submissions for Count Square Submatrices with All Ones.

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int count = 0;
        
        for(int len = 1; len <= min(m, n); len++){
            for(int i = 0; i < m-(len-1); i++){
                for(int j = 0; j < n-(len-1); j++){
                    bool valid = true;
                    for(int si = 0; si < len; si++){
                        for(int sj = 0; sj < len; sj++){
                            if(!matrix[i+si][j+sj]){
                                valid = false;
                                break;
                            } 
                        }
                        if(!valid) break;
                    }
                    if(valid)count++;
                }
            }
        }
        
        return count;
    }
};

//https://leetcode.com/problems/count-square-submatrices-with-all-ones/discuss/441306/Python-DP-solution
//Runtime: 76 ms, faster than 36.81% of C++ online submissions for Count Square Submatrices with All Ones.
//Memory Usage: 16 MB, less than 100.00% of C++ online submissions for Count Square Submatrices with All Ones.

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int count = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i > 0 && j > 0 && matrix[i][j]){
                    matrix[i][j] = min({matrix[i-1][j], matrix[i][j-1], matrix[i-1][j-1]}) + 1;
                }
                //matrix[i][j]: the number of squares(of any size) whose right-bottom corner is at (i, j)
                count += matrix[i][j];
            }
        }
        return count;
    }
};

//DP, O(n^3)
//Hint 1: Create an additive table that counts the sum of elements of submatrix with the superior corner at (0,0).
//Hint 2: Loop over all subsquares in O(n^3) and check if the sum make the whole array to be ones, if it checks then add 1 to the answer.
//Runtime: 1980 ms, faster than 5.08% of C++ online submissions for Count Square Submatrices with All Ones.
//Memory Usage: 26.5 MB, less than 100.00% of C++ online submissions for Count Square Submatrices with All Ones.
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        /*
        padding a row and a column ahead
        so submatrixSum[i][j] corresponds to matrix[i-1][j-1]
        */
        vector<vector<int>> sms(m+1, vector(n+1, 0)); //submatrixSum
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                /*
                submatrix down to prev row + submatrix right to prev column - submatrix to its left-top
                plus
                current element
                */
                sms[i][j] += sms[i-1][j] + sms[i][j-1] - sms[i-1][j-1] + matrix[i-1][j-1];
                // cout << sms[i][j] << " ";
            }
            // cout << endl;
        }
        
        int ans = 0;
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                //the length of the edge of the square
                for(int len = 1; len <= min(i, j); len++){
                    /*
                    use sms[i][j] - sms[i-len][j] - sms[i][j-len] + sms[i-len][j-len] to
                    calculate the sum of matrix[i-len...i-1, j-len...j-1]
                    */
                    if(sms[i][j] - sms[i-len][j] - sms[i][j-len] + sms[i-len][j-len] == len * len){
                        // cout << "(" << i << ", " << j << "), length: " << len << endl;
                        ans++;
                    }
                }
            }
        }
        
        return ans;
    }
};
