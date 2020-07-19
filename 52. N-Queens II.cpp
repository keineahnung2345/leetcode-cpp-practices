//Backtracking
//Runtime: 8 ms, faster than 52.40% of C++ online submissions for N-Queens II.
//Memory Usage: 6 MB, less than 84.99% of C++ online submissions for N-Queens II.
class Solution {
public:
    int n;
    
    void backtrack(vector<bool>& used_col, vector<bool>& used_pos_diag, 
                   vector<bool>& used_neg_diag, int r, int& ans){
        if(r == n){
            ++ans;
        }else{
            for(int c = 0; c < n; ++c){
                if(!used_col[c] && !used_pos_diag[r-c+n-1] && !used_neg_diag[r+c]){
                    used_col[c] = true;
                    used_pos_diag[r-c+n-1] = true;
                    used_neg_diag[r+c] = true;
                    
                    backtrack(used_col, used_pos_diag, used_neg_diag, r+1, ans);
                    
                    used_col[c] = false;
                    used_pos_diag[r-c+n-1] = false;
                    used_neg_diag[r+c] = false;
                }
            }
        }
    };
    
    int totalNQueens(int n) {
        this->n = n;
        int ans = 0;
        vector<bool> used_col(n, false);
        vector<bool> used_pos_diag(2*n-1, false);
        vector<bool> used_neg_diag(2*n-1, false);
        
        backtrack(used_col, used_pos_diag, used_neg_diag, 0, ans);
        
        return ans;
    }
};
