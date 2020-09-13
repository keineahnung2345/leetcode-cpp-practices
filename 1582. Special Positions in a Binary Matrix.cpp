//Runtime: 44 ms, faster than 100.00% of C++ online submissions for Special Positions in a Binary Matrix.
//Memory Usage: 13 MB, less than 33.33% of C++ online submissions for Special Positions in a Binary Matrix.
//time: O(N^3)
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        int ans = 0;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(mat[i][j] == 1){
                    int rcount = 0;
                    for(int ii = 0; ii < m; ++ii){
                        if(mat[ii][j] == 1){
                            ++rcount;
                            if(rcount > 1) break;
                        }
                    }
                    
                    int ccount = 0;
                    for(int jj = 0; jj < n; ++jj){
                        if(mat[i][jj] == 1){
                            ++ccount;
                            if(ccount > 1) break;
                        }
                    }
                    
                    if(rcount == 1 && ccount == 1){
                        ++ans;
                    }
                }
            }
        }
        
        return ans;
    }
};

//two pass, O(N^2)
//Runtime: 44 ms, faster than 100.00% of C++ online submissions for Special Positions in a Binary Matrix.
//Memory Usage: 13.2 MB, less than 33.33% of C++ online submissions for Special Positions in a Binary Matrix.
//https://leetcode.com/problems/special-positions-in-a-binary-matrix/discuss/843949/C%2B%2B-2-passes
//time: O(N^2)
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        vector<int> rows(m), cols(n);
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(mat[i][j] == 1){
                    ++rows[i];
                    ++cols[j];
                }
            }
        }
        
        int ans = 0;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(mat[i][j] == 1 && rows[i] == 1 && cols[j] == 1){
                    ++ans;
                }
            }
        }
        
        return ans;
    }
};
