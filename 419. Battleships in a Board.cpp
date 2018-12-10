/**
Given an 2D board, count how many battleships are in it. The battleships are represented with 'X's, empty slots are represented with '.'s. You may assume the following rules:
You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:
X..X
...X
...X
In the above board there are 2 battleships.
Invalid Example:
...X
XXXX
...X
This is an invalid board that you will not receive - as battleships will always have a cell separating between them.
Follow up:
Could you do it in one-pass, using only O(1) extra memory and without modifying the value of the board?
**/

//Discuss by Code1404
/**
Whenever we encounter an "X" (ship) in the grid, check if its previous row/col has a Ship as well. 
Remember from the question that "At least one horizontal or vertical cell separates between two battleships - 
there are no adjacent battleships". So if its present, then its a continuation of an earlier ship, else its a new ship.
**/

//Your runtime beats 32.22 % of cpp submissions.
//Your runtime beats 98.77 % of cpp submissions.
class Solution {
public:
    bool hasShip(vector<vector<char>>& board, int r, int c){
        if(r<0 || c<0 || r>=board.size() || c>=board[0].size())
            return false;
        return board[r][c]=='X';
    }
    int countBattleships(vector<vector<char>>& board) {
        int count = 0;
        
        //Your runtime beats 32.22 % of cpp submissions.
        for(int r = 0; r < board.size(); r++){
            for(int c = 0; c < board[0].size(); c++){

        //Your runtime beats 98.77 % of cpp submissions.
        int rows = board.size();
        int cols = board[0].size();
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                if(board[r][c]=='.') continue;
                //we have counted the ship before
                if(hasShip(board, r-1, c) || hasShip(board, r, c-1))continue;
                count++;
            }
        }
        return count;
    }
};
