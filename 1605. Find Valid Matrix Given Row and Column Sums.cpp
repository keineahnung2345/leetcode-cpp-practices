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

//Greedy
//https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/discuss/876845/JavaC%2B%2BPython-Easy-and-Concise-with-Prove
//Runtime: 108 ms, faster than 50.00% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
//Memory Usage: 33.8 MB, less than 25.00% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
//time: O(mn), space: O(mn)
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size();
        int n = colSum.size();
        
        vector<vector<int>> mat(m, vector<int>(n, 0));
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                mat[i][j] = min(rowSum[i], colSum[j]);
                rowSum[i] -= mat[i][j];
                colSum[j] -= mat[i][j];
            }
        }
        
        return mat;
    }
};

//Greedy
//https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/discuss/876845/JavaC%2B%2BPython-Easy-and-Concise-with-Prove
//Runtime: 76 ms, faster than 75.00% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
//Memory Usage: 33.6 MB, less than 25.00% of C++ online submissions for Find Valid Matrix Given Row and Column Sums.
//time: O(mn) for initialization, O(m+n) for process, space: O(mn)
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size();
        int n = colSum.size();
        
        vector<vector<int>> mat(m, vector<int>(n, 0));
        
        int i = 0, j = 0;
        
        while(i < m && j < n){
            mat[i][j] = min(rowSum[i], colSum[j]);
            rowSum[i] -= mat[i][j];
            colSum[j] -= mat[i][j];
            //done for ith row
            if(rowSum[i] == 0) ++i;
            //done for jth col
            if(colSum[j] == 0) ++j;
        }
        
        return mat;
    }
};
