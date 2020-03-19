//Runtime: 284 ms, faster than 13.67% of C++ online submissions for Search a 2D Matrix II.
//Memory Usage: 12.3 MB, less than 100.00% of C++ online submissions for Search a 2D Matrix II.
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();
        if(n == 0) return false;
        int r = n;
        // cout << m << " " << n << " " << r << endl;
        
        for(vector<int>& row : matrix){
            //upper_bound: Unlike lower_bound, the value pointed by the iterator returned by this function cannot be equivalent to val, only greater.
            //the search range becomes smaller and smaller
            auto it = upper_bound(row.begin(), row.begin() + r, target);
            //if we've found an element larger than target, we can shrink the range
            //o.w. the range remains the same
            if(it !=  row.begin() + r){
                r =  it - row.begin();
            }
            //r is the position where row[r] > target(notice it's not >= !!)
            // cout << r << endl;
            /*
            row[r] is the minimum element we can find, 
            and it is larger than target, 
            so we will not find target in the remaining part of the matrix
            */
            if(r == 0) return false;
            if(row[r-1] == target) return true;
        }
        
        return false;
    }
};

//https://leetcode.com/problems/search-a-2d-matrix-ii/discuss/66140/My-concise-O(m%2Bn)-Java-solution
//Runtime: 64 ms, faster than 85.79% of C++ online submissions for Search a 2D Matrix II.
//Memory Usage: 12.1 MB, less than 100.00% of C++ online submissions for Search a 2D Matrix II.
//time: O(m+n)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();
        if(n == 0) return false;
        
        int row = 0, col = n-1;
        while(col >= 0 && row < m){
            if(matrix[row][col] == target){
                return true;
            }else if(target < matrix[row][col]){
                //the current column's value are all larger than target
                col--;
            }else{
                //the current row's value are all smaller than target
                row++;
            }
        }
        
        return false;
    }
};

//divide and conquer
//https://leetcode.com/problems/search-a-2d-matrix-ii/discuss/66285/C%2B%2BC-divide-and-conquer-solution
//Runtime: 160 ms, faster than 22.49% of C++ online submissions for Search a 2D Matrix II.
//Memory Usage: 12.5 MB, less than 100.00% of C++ online submissions for Search a 2D Matrix II.
class Solution {
public:
    bool binarySearch(vector<vector<int>>& matrix, int target
        , int row_min, int row_max, int col_min, int col_max){
        if(row_min > row_max) return false;
        if(col_min > col_max) return false;
        int row = (row_min + row_max)/2;
        int col = (col_min + col_max)/2;
        
        if(target == matrix[row][col]){
            return true;
        }else if(target > matrix[row][col]){
            //exclude matrix[row_min:row][col_min:col] from matrix[row_min:row_max][col_min:col_max]
            return binarySearch(matrix, target, row_min, row_max, col+1, col_max) ||
                binarySearch(matrix, target, row+1, row_max, col_min, col);
        }else{
            //these two rectangle together with matrix[row][col] construct matrix[row_min:row][col_min:col]
            return binarySearch(matrix, target, row_min, row_max, col_min, col-1) ||
                binarySearch(matrix, target, row_min, row-1, col, col_max);
        }
    };
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();
        if(n == 0) return false;
        return binarySearch(matrix, target, 0, m-1, 0, n-1);
    }
};
