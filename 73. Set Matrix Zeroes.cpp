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

//Approach 2: O(1) Space, Efficient Solution
//Runtime: 24 ms, faster than 92.32% of C++ online submissions for Set Matrix Zeroes.
//Memory Usage: 13.6 MB, less than 9.84% of C++ online submissions for Set Matrix Zeroes.
//time: O(m*n), space: O(1)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return;
        int n = matrix[0].size();
        if(n == 0) return;
        
        /*
        matrix[0][0] indicates the first row should be zero out,
        so we need this variable whether first col should be zero out or not
        */
        bool firstCol = false;
        
        for(int i = 0; i < m; ++i){
            //special case: first column
            if(matrix[i][0] == 0){
                firstCol = true;
            }
            
            //for 2nd and later columns, we use the first row as indicator
            for(int j = 1; j < n; ++j){
                if(matrix[i][j] == 0){
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        
        /*
        note that i starts from 1!
        we zero out the part right and down to matrix[1][1](included) first
        */
        for(int i = 1; i < m; ++i){
            if(matrix[i][0] == 0){
                //j starts from 1
                for(int j = 1; j < n; ++j){
                    matrix[i][j] = 0;
                }
            }
        }
        
        //j starts from 1
        for(int j = 1; j < n; ++j){
            if(matrix[0][j] == 0){
                //i starts from 1
                for(int i = 1; i < m; ++i){
                    matrix[i][j] = 0;
                }
            }
        }
        
        // for(int i = 0; i < m; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << matrix[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "===================" << endl;
        
        /*
        finally zero out the first row
        */
        if(matrix[0][0] == 0){
            for(int j = 1; j < n; ++j){
                matrix[0][j] = 0;
            }
        }
        
        // for(int i = 0; i < m; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << matrix[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "===================" << endl;
        
        /*
        finally zero out the first col
        */
        if(firstCol){
            //i starts from 0
            for(int i = 0; i < m; ++i){
                matrix[i][0] = 0;
            }
        }
        
        // for(int i = 0; i < m; ++i){
        //     for(int j = 0; j < n; ++j){
        //         cout << matrix[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "===================" << endl;
    }
};
