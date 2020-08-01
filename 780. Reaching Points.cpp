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

//https://leetcode.com/problems/reaching-points/discuss/114856/JavaC%2B%2BPython-Modulo-from-the-End
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reaching Points.
//Memory Usage: 5.9 MB, less than 50.00% of C++ online submissions for Reaching Points.
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while(tx > sx && ty > sy){
            /*
            (x,y) -> (x,x+y) or (x+y,x)
            so the larger one in {tx, ty} must be 
            the one increased from last step,
            to restore to the previous state,
            we reduce the addend from it
            */
            if(tx > ty) tx %= ty;
            else ty %= tx;
        }
        
        return tx == sx && ty >= sy && (ty-sy)%sx == 0 ||
            ty == sy && tx >= sx && (tx-sx)%sy == 0;
    }
};
