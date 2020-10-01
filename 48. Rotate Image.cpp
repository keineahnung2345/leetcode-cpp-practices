//https://leetcode.com/problems/rotate-image/discuss/18872/A-common-method-to-rotate-the-image
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Rotate Image.
//Memory Usage: 7.3 MB, less than 45.79% of C++ online submissions for Rotate Image.
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        for(int i = 0; i < n-1-i; ++i){
            swap(matrix[i], matrix[n-1-i]);
        }
        
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < i; ++j){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};
