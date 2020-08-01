//backtracking
//Runtime Error
//100 / 190 test cases passed.
class Solution {
public:
    int tx, ty;
    
    bool backtrack(int x, int y){
        if(x > tx || y > ty){
            return false;
        }
        
        if(x == tx && y == ty){
            return true;
        }
        
        return backtrack(x+y, y) || backtrack(x, x+y);
    };
    
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        this->tx = tx;
        this->ty = ty;
        return backtrack(sx, sy);
    }
};
