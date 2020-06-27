//Runtime: 4 ms, faster than 42.52% of C++ online submissions for Valid Tic-Tac-Toe State.
//Memory Usage: 8.4 MB, less than 91.51% of C++ online submissions for Valid Tic-Tac-Toe State.
class Solution {
public:
    vector<int> countLines(vector<string>& board, char c){
        int lines = 0;
        /*
        record (i,j) is passed by how many lines
        */
        vector<int> intersection(9, 0);
        
        //horizontal
        for(int i = 0; i < 3; ++i){
            if(count(board[i].begin(), board[i].end(), c) == 3){
                ++lines;
                ++intersection[i*3+0];
                ++intersection[i*3+1];
                ++intersection[i*3+2];
            }
        }
        
        //vertical
        for(int i = 0; i < 3; ++i){
            if(board[0][i] == c && board[1][i] == c && board[2][i] == c){
                ++lines;
                ++intersection[0*3+i];
                ++intersection[1*3+i];
                ++intersection[2*3+i];
            }
        }
        
        if(board[0][0] == c && board[1][1] == c && board[2][2] == c){
            ++lines;
            ++intersection[0*3+0];
            ++intersection[1*3+1];
            ++intersection[2*3+2];
        }
        
        if(board[0][2] == c && board[1][1] == c && board[2][0] == c){
            ++lines;
            ++intersection[0*3+2];
            ++intersection[1*3+1];
            ++intersection[2*3+0];
        }
        
        return {lines, *max_element(intersection.begin(), intersection.end())};
    };
    
    bool validTicTacToe(vector<string>& board) {
        int circle = 0, cross = 0;
        
        for(string& s : board){
            circle += count(s.begin(), s.end(), 'O');
            cross += count(s.begin(), s.end(), 'X');
        }
        
        //first player puts 'X'
        if(circle > cross) return false;
        
        //player 1 and 2 take turns
        if(cross >= circle+2) return false;
        
        vector<int> crossLines = countLines(board, 'X');
        vector<int> circleLines = countLines(board, 'O');
        
        //both players win
        if(crossLines[0] >= 1 && circleLines[0] >= 1) return false;
        
        if(crossLines[0] == 2){
            //one player get 2 lines and the game ends
            //need to check whether the 2 lines have intersection
            //if 'X' wins, cross-1 must equal to circle
            return (crossLines[1] == 2) && (cross-1 == circle);
        }else if(circleLines[0] == 2){
            return (circleLines[1] == 2) && (cross == circle);
        }
        
        //only one player win
        bool oneWin = ((crossLines[0] == 1) && (cross-1 == circle)) ||
                (circleLines[0] == 1) && (cross == circle);
        
        bool noWin = (crossLines[0] == 0) && (circleLines[0] == 0);
        
        return oneWin || noWin;
    }
};
