//Runtime: 8 ms, faster than 92.26% of C++ online submissions for Search a 2D Matrix.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Search a 2D Matrix.

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();
        
        int l = 0, r = m*n-1;
        
        while(l <= r){
            int mid = (l+r)/2;
            if(matrix[mid/n][mid%n] == target){
                return true;
            }else if(matrix[mid/n][mid%n] < target){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        
        return false;
    }
};
