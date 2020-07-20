//Backtracking
//Runtime: 12 ms, faster than 59.92% of C++ online submissions for N-Queens.
//Memory Usage: 8 MB, less than 32.76% of C++ online submissions for N-Queens.
class Solution {
public:
    int n;
    
    void backtrack(vector<bool>& used_col, vector<bool>& used_pos_diag, 
                   vector<bool>& used_neg_diag, int r, 
                   vector<int>& curpos, vector<vector<string>>& ans){
        if(r == n){
            vector<string> curans;
            for(int i = 0; i < n; ++i){
                string row(n, '.');
                row[curpos[i]] = 'Q';
                curans.push_back(row);
            }
            ans.push_back(curans);
        }else{
            for(int c = 0; c < n; ++c){
                if(!used_col[c] && !used_pos_diag[r-c+n-1] && !used_neg_diag[r+c]){
                    curpos.push_back(c);
                    used_col[c] = true;
                    used_pos_diag[r-c+n-1] = true;
                    used_neg_diag[r+c] = true;
                    
                    backtrack(used_col, used_pos_diag, used_neg_diag, r+1, curpos, ans);
                    
                    used_col[c] = false;
                    used_pos_diag[r-c+n-1] = false;
                    used_neg_diag[r+c] = false;
                    curpos.pop_back();
                }
            }
        }
    };
    
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        vector<int> curpos;
        vector<vector<string>> ans;
        //in each recursion, r is different, so there must be only one Q in a row
        //for each row, need to check if that column is used
        vector<bool> used_col(n, false);
        //also check if that positive diagonals is used
        //there are 2*n-1 positive diagonals
        vector<bool> used_pos_diag(2*n-1, false);
        //also check if that positive diagonals is used
        //there are 2*n-1 negative diagonals
        vector<bool> used_neg_diag(2*n-1, false);
        
        backtrack(used_col, used_pos_diag, used_neg_diag, 0, curpos, ans);
        
        return ans;
    }
};

//+speed up, vector<bool> -> vector<int>, build ans on the fly
//https://leetcode.com/problems/n-queens/discuss/19808/Accepted-4ms-c%2B%2B-solution-use-backtracking-and-bitmask-easy-understand
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for N-Queens.
//Memory Usage: 7.2 MB, less than 91.99% of C++ online submissions for N-Queens.
class Solution {
public:
    int n;
    
    void backtrack(vector<int>& used, int r, 
                   vector<string>& cur, vector<vector<string>>& ans){
        if(r == n){
            ans.push_back(cur);
        }else{
            for(int c = 0; c < n; ++c){
                if(!used[c] && !used[n+r-c+n-1] && !used[n+2*n-1+r+c]){
                    cur[r][c] = 'Q';
                    used[c] = used[n+r-c+n-1] = used[n+2*n-1+r+c] = true;
                    
                    backtrack(used, r+1, cur, ans);
                    
                    used[c] = used[n+r-c+n-1] = used[n+2*n-1+r+c] = false;
                    cur[r][c] = '.';
                }
            }
        }
    };
    
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        vector<string> cur(n, string(n, '.'));
        vector<vector<string>> ans;
        vector<int> used(n + 2*n-1 + 2*n-1, false);
        
        backtrack(used, 0, cur, ans);
        
        return ans;
    }
};
