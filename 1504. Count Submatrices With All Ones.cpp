//TLE
//67 / 72 test cases passed.
//time: O(m^2 * n^2)
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        if(m == 0) return 0;
        int n = mat[0].size();
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
                sms[i][j] += sms[i-1][j] + sms[i][j-1] - sms[i-1][j-1] + mat[i-1][j-1];
                // cout << sms[i][j] << " ";
            }
            // cout << endl;
        }
        
        int ans = 0;
        
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                //the length of the edge of the square
                for(int li = 1; li <= i; li++){
                    for(int lj = 1; lj <= j; lj++){
                        /*
                        use sms[i][j] - sms[i-len][j] - sms[i][j-len] + sms[i-len][j-len] to
                        calculate the sum of matrix[i-len...i-1, j-len...j-1]
                        */
                        if(sms[i][j] - sms[i-li][j] - sms[i][j-lj] + sms[i-li][j-lj] == li * lj){
                            // cout << "(" << i << ", " << j << "), length: " << len << endl;
                            ans++;
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};
