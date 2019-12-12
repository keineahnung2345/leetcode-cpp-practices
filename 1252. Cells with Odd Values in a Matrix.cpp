//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Cells with Odd Values in a Matrix.
//Memory Usage: 9.6 MB, less than 100.00% of C++ online submissions for Cells with Odd Values in a Matrix.

class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        vector<vector<int>> ans(n, vector<int>(m));
        int numOdd = 0;
        
        for(vector<int> index : indices){
            for(int j = 0; j < m; j++){
                ans[index[0]][j]++;
            }
            for(int i = 0; i < n; i++){
                ans[i][index[1]]++;
            }
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(ans[i][j]%2 == 1){
                    numOdd++;
                }
            }
        }
        
        return numOdd;
    }
};
