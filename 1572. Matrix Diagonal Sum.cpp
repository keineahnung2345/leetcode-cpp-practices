//Runtime: 32 ms, faster than 50.00% of C++ online submissions for Matrix Diagonal Sum.
//Memory Usage: 11.4 MB, less than 83.33% of C++ online submissions for Matrix Diagonal Sum.
class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat.size();
        
        int sum = 0;
        
        for(int i = 0; i < n; ++i){
            sum += mat[i][i];
            sum += mat[i][n-1-i];
        }
        
        if(n&1) sum -= mat[n/2][n/2];
        
        return sum;
    }
};
