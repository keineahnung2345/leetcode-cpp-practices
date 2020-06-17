//bfs
//Runtime: 80 ms, faster than 5.44% of C++ online submissions for Surrounded Regions.
//Memory Usage: 19.1 MB, less than 8.24% of C++ online submissions for Surrounded Regions.
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        if(m == 0) return;
        int n = board[0].size();
        if(n == 0) return;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs = {
            {0,1},
            {0,-1},
            {1,0},
            {-1,0}
        };
        vector<vector<int>> component;
        vector<int> cur;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                bool surrounded = true;
                component.clear();
                if(board[i][j] == 'O' && !visited[i][j]){
                    queue<vector<int>> q;
                    q.push({i, j});
                    visited[i][j] = true;
                    
                    while(!q.empty()){
                        cur = q.front(); q.pop();
                        if(cur[0] == 0 || cur[0] == m-1 || cur[1] == 0 || cur[1] == n-1){
                            surrounded = false;
                        }
                        component.push_back(cur);
                        
                        for(vector<int>& dir : dirs){
                            int ni = cur[0] + dir[0];
                            int nj = cur[1] + dir[1];
                            if(ni >= 0 && ni < m && nj >= 0 && nj < n && board[ni][nj] == 'O' && !visited[ni][nj]){        
                                visited[ni][nj] = true;
                                q.push({ni, nj});
                            }
                        }
                    }
                }
                
                if(surrounded && !component.empty()){
                    for(vector<int>& cur : component){
                        board[cur[0]][cur[1]] = 'X';
                    }
                }
            }
        }
    }
};
