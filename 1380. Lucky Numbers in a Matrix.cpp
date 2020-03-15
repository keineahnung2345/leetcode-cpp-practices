//Runtime: 28 ms, beat 58.33%
//Memory Usage: 9.8 MB
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> rowMinIdxs(m, -1);
        // vector<int> colMaxIdxs(n, -1);
        vector<int> ans;
        
        for(int i = 0; i < m; i++){
            int rowMinIdx = min_element(matrix[i].begin(), matrix[i].end()) - matrix[i].begin();
            rowMinIdxs[i] = rowMinIdx;
            // cout << rowMinIdx << " ";
        }
        // cout << endl;
        
        for(int j = 0; j < n; j++){
            vector<int> col(m);
            for(int i = 0; i < m; i++) col[i] = matrix[i][j];
            int colMaxIdx = max_element(col.begin(), col.end()) - col.begin();
            
            // cout << colMaxIdx << " " << rowMinIdxs[colMaxIdx] << " " << j << endl;
            if(rowMinIdxs[colMaxIdx] == j){
                // cout << "match" << endl;
                ans.push_back(matrix[colMaxIdx][j]);
            }
            
            // colMaxIdxs[j] = colMaxIdx;
            // cout << colMaxIdx << " ";
        }
        // cout << endl;
        
        return ans;
    }
};
