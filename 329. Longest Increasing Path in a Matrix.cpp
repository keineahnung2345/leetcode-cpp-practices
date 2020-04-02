//DFS, iterative
//WA(because the visit order of children matters)
//68 / 138 test cases passed.
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                vector<vector<bool>> visited(m, vector(n, false));
                stack<vector<int>> stk;
                
                visited[i][j] = true;
                stk.push({i, j, 1});
                
                while(!stk.empty()){
                    vector<int> cur = stk.top(); stk.pop();
                    int ci = cur[0], cj = cur[1], cd = cur[2];
                    
                    ans = max(ans, cd);
                    
                    for(vector<int>& dir : dirs){
                        int ni = ci+dir[0];
                        int nj = cj+dir[1];
                        
                        if(ni >= 0 && ni < m && nj >= 0 && nj < n){
                            if(!visited[ni][nj] && matrix[ni][nj] > matrix[ci][cj]){
                                visited[ni][nj] = true;
                                //depth plus 1
                                stk.push({ni, nj, cd+1});
                            }
                        }
                    }
                }
            }
        }
        
        return ans;
    }
};
