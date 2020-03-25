//Runtime: 104 ms, faster than 5.08% of C++ online submissions for Sliding Puzzle.
//Memory Usage: 17.8 MB, less than 16.67% of C++ online submissions for Sliding Puzzle.
struct Board{
    vector<vector<int>> board;
    //where zero is
    int i;
    int j;
    //how many moves to this state
    int depth;
    
    Board(vector<vector<int>> b, int i, int j, int d):board(b), i(i), j(j), depth(d){};
    
};

class Solution {
public:
    bool isSolved(vector<vector<int>>& board){
        if(board[1][2] != 0) return false;
        
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 3; j++){
                //skip checking the last element
                if(!(i == 1 && j == 2) && board[i][j] != i * 3 + (j+1)){
                    return false;
                }
            }
        }
        return true;
    };
    
    int slidingPuzzle(vector<vector<int>>& board) {
        queue<Board> q;
        set<vector<vector<int>>> visited;
        
        vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        
        int i, j;
        
        for(i = 0; i < 2; i++){
            auto it = find(board[i].begin(), board[i].end(), 0);
            if(it != board[i].end()){
                j = it - board[i].begin();
                break;
            }
        }
        
        q.push(Board(board, i, j, 0));
        
        while(!q.empty()){
            Board b = q.front(); q.pop();
            // cout << b.i << " " << b.j << " " << b.depth << endl;
            
            if(isSolved(b.board)) return b.depth;
            
            for(vector<int> dir : dirs){
                int newI = b.i + dir[0], newJ = b.j + dir[1];
                if(newI >= 0 && newI < 2 && newJ >= 0 && newJ < 3){
                    vector<vector<int>> newBoard = b.board;
                    swap(newBoard[b.i][b.j], newBoard[newI][newJ]);
                    if(visited.insert(newBoard).second){
                        q.push(Board(newBoard, newI, newJ, b.depth+1));
                    }
                }
            }
        }
        
        return -1;
    }
};
