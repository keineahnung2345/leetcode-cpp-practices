/**
On an 8 x 8 chessboard, there is one white rook.  There also may be empty squares, white bishops, and black pawns.  These are given as characters 'R', '.', 'B', and 'p' respectively. Uppercase characters represent white pieces, and lowercase characters represent black pieces.

The rook moves as in the rules of Chess: it chooses one of four cardinal directions (north, east, west, and south), then moves in that direction until it chooses to stop, reaches the edge of the board, or captures an opposite colored pawn by moving to the same square it occupies.  Also, rooks cannot move into the same square as other friendly bishops.

Return the number of pawns the rook can capture in one move.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Available Captures for Rook.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Available Captures for Rook.

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int Rx = 0, Ry = 0;
        
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                if(board[i][j] == 'R'){
                    Ry = i;
                    Rx = j;
                }
            }
        }
        
        int num_captures = 0;
        
        int cur = 0;
        char pos = '\0';
        string dirs = "rlud";
        
        for(int i = 0; i < dirs.size(); i++){
            char dir = dirs[i];
            if(dir=='r' or dir=='l'){
                cur = Rx;
            }else if(dir=='u' or dir=='d'){
                cur = Ry;
            }
            //cout << "dir: " << dir << ", Rx: " << Rx << ", Ry: " << Ry << endl;
            while(cur>=0 and cur < board.size()){
                if(dir=='r' or dir=='l'){
                    //cout << "Ry: " << Ry << ", cur: " << cur << ", pos: " << pos << endl;
                    pos = board[Ry][cur];
                }else if(dir=='u' or dir=='d'){
                    //cout << "cur: " << cur << ", Rx: " << Rx << ", pos: " << pos << endl;
                    pos = board[cur][Rx];
                }

                if(pos=='p'){
                    num_captures++;
                    break;
                }else if(pos=='B'){
                    break;
                }

                if(dir=='r' or dir=='d'){
                    cur++;
                }else if(dir=='l' or dir=='u'){
                    cur--;
                }
            }
        }
        
        return num_captures;
    }
};
