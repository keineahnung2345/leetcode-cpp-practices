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
