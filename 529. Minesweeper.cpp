//TLE
//28 / 54 test cases passed.
class Solution {
public:
    vector<vector<int>> dirs;
    
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        queue<vector<int>> q;
        vector<int> cur;
        int curR, curC;
        
        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
        
        map<vector<int>, int> mCounts;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] != 'M') continue;
                for(vector<int>& dir : dirs){
                    int nextI = i + dir[0], nextJ = j + dir[1];
                    if(nextI >= 0 && nextI < m && nextJ >= 0 && nextJ < n){
                        mCounts[{nextI, nextJ}]++;
                    }
                }
            }
        }
        
        q.push(click);
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            curR = cur[0], curC = cur[1];
            visited[curR][curC] = true;
            if(board[curR][curC] == 'M'){
                board[curR][curC] = 'X';
                break;
            }
            
            // int mCount = 0;
            // for(vector<int>& dir : dirs){
            //     int nextR = curR + dir[0];
            //     int nextC = curC + dir[1];
            //     if(nextR >= 0 && nextR < m && nextC >= 0 && nextC < n){
            //         if(board[nextR][nextC] == 'M'){
            //             mCount++;
            //         }
            //     }
            // }
            
            int mCount = mCounts[{curR,curC}];
            
            if(mCount == 0){
                board[curR][curC] = 'B';
                //continue to reveal
                for(vector<int>& dir : dirs){
                    int nextR = curR + dir[0];
                    int nextC = curC + dir[1];
                    if(nextR >= 0 && nextR < m && nextC >= 0 && nextC < n && !visited[nextR][nextC]){
                        q.push({nextR, nextC});
                    }
                }
            }else{
                board[curR][curC] = ('0'+mCount);
                //stop revealing
            }
        }
        
        return board;
    }
};
