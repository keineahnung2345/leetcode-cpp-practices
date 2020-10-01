//Runtime: 24 ms, faster than 92.32% of C++ online submissions for Set Matrix Zeroes.
//Memory Usage: 13.5 MB, less than 15.07% of C++ online submissions for Set Matrix Zeroes.
//time: O(m*n), space: O(m+n)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return;
        int n = matrix[0].size();
        if(n == 0) return;
        
        vector<bool> rows(m, false), cols(n, false);
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(matrix[i][j] == 0){
                    rows[i] = true;
                    cols[j] = true;
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            if(rows[i]){
                for(int j = 0; j < n; ++j){
                    matrix[i][j] = 0;
                }
            }
        }
        
        for(int j = 0; j < n; ++j){
            if(cols[j]){
                for(int i = 0; i < m; ++i){
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
