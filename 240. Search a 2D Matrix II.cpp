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
