//Greedy: each time fill the cell pointed by min rowSum and min colSum
//Runtime: 140 ms, faster than 12.50% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
//Memory Usage: 33.6 MB, less than 25.00% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size(), n = colSum.size();
        vector<vector<int>> mat(m, vector<int>(n, 0));
        
        do{
            int min_row = min_element(rowSum.begin(), rowSum.end()) - rowSum.begin();
            int min_col = min_element(colSum.begin(), colSum.end()) - colSum.begin();
            
            // cout << min_row << ", " << min_col << endl;
            
            if((rowSum[min_row] == INT_MAX) && (colSum[min_col] == INT_MAX)) break;
            
            int val = min(rowSum[min_row], colSum[min_col]);
            
            // cout << "val: " << val << endl;
            
            mat[min_row][min_col] = val;
            rowSum[min_row] -= val; if(rowSum[min_row] == 0) rowSum[min_row] = INT_MAX;
            colSum[min_col] -= val; if(colSum[min_col] == 0) colSum[min_col] = INT_MAX;
            
            // cout << "rowSum" << endl;
            // for(int i = 0; i < m; ++i){
            //     cout << rowSum[i] << " ";
            // }
            // cout << endl;
            
            // cout << "colSum" << endl;
            // for(int j = 0; j < n; ++j){
            //     cout << colSum[j] << " ";
            // }
            // cout << endl;
        }while(true);
        
        return mat;
    }
};
