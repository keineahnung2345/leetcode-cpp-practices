//Runtime: 148 ms, faster than 82.86% of C++ online submissions for Image Smoother.
//Memory Usage: 17.5 MB, less than 100.00% of C++ online submissions for Image Smoother.

class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int m = M.size(), n = M[0].size();
        
        vector<vector<int>> ans(m, vector<int>(n));
        vector<pair<int,int>> dirs = {{-1,-1}, {-1,0},{-1,1},
                                      {0,-1},{0,0},{0,1},
                                      {1,-1},{1,0},{1,1}};
        
        vector<int> v;
        int sum = 0, count = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                sum = 0; count = 0;
                
                for(auto dir : dirs){
                    int newi = i+dir.first, newj = j+dir.second;
                    if(newi >= 0 && newi < m
                      && newj >= 0 && newj < n){
                        sum += M[newi][newj];
                        count++;
                    }
                }
                
                ans[i][j] = sum/count;
            }
        }
        
        return ans;
    }
};
