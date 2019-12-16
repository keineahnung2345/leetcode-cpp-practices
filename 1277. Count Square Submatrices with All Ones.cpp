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
