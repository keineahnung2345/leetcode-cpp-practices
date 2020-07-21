//dfs
//Runtime: 116 ms, faster than 54.80% of C++ online submissions for Word Search.
//Memory Usage: 11.8 MB, less than 65.02% of C++ online submissions for Word Search.
class Solution {
public:
    int m, n;
    vector<vector<int>> dirs;
    
   	bool dfs(vector<vector<char>>& board, string& word, vector<vector<bool>>& visited, int ci, int cj, int cix) {
        if(cix == word.size()){
            return true;
        }else if(board[ci][cj] != word[cix]){
            return false;
        }else{
            // cout << cix << " : " << "(" << ci << ", " << cj << ")" << endl;
            for(vector<int>& dir : dirs){
                int ni = ci + dir[0];
                int nj = cj + dir[1];
                if(ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]){
                    visited[ni][nj] = true;
                    if(dfs(board, word, visited, ni, nj, cix+1)) return true;
                    visited[ni][nj] = false;
                }
            }
            /*
            to deal with the case: 
            [["a"]]
            "a"
            */
            return cix+1 == word.size();
        }
    };
    
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        if(m == 0) return false;
        n = board[0].size();
        if(n == 0) return false;
        
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                visited[i][j] = true;
                if(dfs(board, word, visited, i, j, 0)){
                    return true;
                }
                visited[i][j] = false;
            }
        }
        
        return false;
    }
};
