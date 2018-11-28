/**
There is a robot starting at position (0, 0), the origin, on a 2D plane. Given a sequence of its moves, judge if this robot ends up at (0, 0) after it completes its moves.

The move sequence is represented by a string, and the character moves[i] represents its ith move. Valid moves are R (right), L (left), U (up), and D (down). If the robot returns to the origin after it finishes all of its moves, return true. Otherwise, return false.

Note: The way that the robot is "facing" is irrelevant. "R" will always make the robot move to the right once, "L" will always make it move left, etc. Also, assume that the magnitude of the robot's movement is the same for each move.

Example 1:

Input: "UD"
Output: true 
Explanation: The robot moves up once, and then down once. All moves have the same magnitude, so it ended up at the origin where it started. Therefore, we return true.
 

Example 2:

Input: "LL"
Output: false
Explanation: The robot moves left twice. It ends up two "moves" to the left of the origin. We return false because it is not at the origin at the end of its moves.
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the length of moves. We iterate through the string.

Space Complexity: O(1)O(1). In Java, our character array is O(N)O(N).
**/

//Your runtime beats 50.93 % of cpp submissions.
/**
class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0, y = 0;
        for(int i = 0; i< moves.size(); i++){
            switch(moves[i]){
                case 'R':
                    x+=1;
                    break; //don't forget the break!
                case 'L':
                    x-=1;
                    break;
                case 'U':
                    y+=1;
                    break;
                case 'D':
                    y-=1;
            }
        }
        return (x==0 && y==0);
    }
};
**/

class Solution {
public:
    bool judgeCircle(string moves) {
        int x = 0, y = 0;
        for(int i = 0; i< moves.size(); i++){
            switch(moves[i]){
                case 'U':
                case 'R':
                    x+=1;
                    break;
                case 'L':
                case 'D':
                    x-=1;
            }
        }
        return x==0;
    }
};
