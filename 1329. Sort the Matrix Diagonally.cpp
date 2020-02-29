//Runtime: 28 ms, faster than 86.54% of C++ online submissions for Sort the Matrix Diagonally.
//Memory Usage: 10.4 MB, less than 100.00% of C++ online submissions for Sort the Matrix Diagonally.

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        
        int diag_num = (m-1)+1+(n-1);
        
        // for(int i = 0; i < m; i++){
        //     for(int j = 0; j < n; j++){
        //         cout << mat[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        for(int k = 0; k < diag_num; k++){
            vector<int> tmp;
            
            for(int i = max(m-1-k, 0), j = max(k-m+1, 0); i < m && j < n; i++, j++){
                // cout << "i: " << i << ", j: " << j << endl;
                tmp.push_back(mat[i][j]);
            }
            // cout << "tmp: " << tmp.size() << endl;
            sort(tmp.begin(), tmp.end());
            for(int i = max(m-1-k, 0), j = max(k-m+1, 0), t = 0; i < m && j < n; i++, j++, t++){
                mat[i][j] = tmp[t];
            }
        }
        
        // for(int i = 0; i < m; i++){
        //     for(int j = 0; j < n; j++){
        //         cout << mat[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        return mat;
    }
};
