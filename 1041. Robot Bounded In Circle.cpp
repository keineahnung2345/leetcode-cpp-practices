//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Robot Bounded In Circle.
//Memory Usage: 6.3 MB, less than 19.49% of C++ online submissions for Robot Bounded In Circle.
class Solution {
public:
    bool isRobotBounded(string instructions) {
        vector<int> pos = {0, 0};
        vector<vector<int>> dirs = {{0,1}, {-1,0}, {0,-1}, {1,0}};
        int dirId = 0;
        
        for(int i = 0; i < 4; ++i){
            for(char c : instructions){
                switch(c){
                    case 'G':
                        pos[0] += dirs[dirId][0];
                        pos[1] += dirs[dirId][1];
                        break;
                    case 'L':
                        dirId = (dirId+1)%4;
                        break;
                    case 'R':
                        dirId = (dirId+4-1)%4;
                        break;
                }
            }
            if(pos[0] == 0 && pos[1] == 0){
                return true;
            }
        }
        
        return false;
    }
};

//https://leetcode.com/problems/robot-bounded-in-circle/discuss/290856/JavaC%2B%2BPython-Let-Chopper-Help-Explain
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Robot Bounded In Circle.
//Memory Usage: 6.2 MB, less than 51.92% of C++ online submissions for Robot Bounded In Circle.
class Solution {
public:
    bool isRobotBounded(string instructions) {
        vector<int> pos = {0, 0};
        vector<vector<int>> dirs = {{0,1}, {-1,0}, {0,-1}, {1,0}};
        int dirId = 0;
        
        for(char c : instructions){
            switch(c){
                case 'G':
                    pos[0] += dirs[dirId][0];
                    pos[1] += dirs[dirId][1];
                    break;
                case 'L':
                    dirId = (dirId+1)%4;
                    break;
                case 'R':
                    dirId = (dirId+4-1)%4;
                    break;
            }
        }
        
        /*if after a sequence of instruction, 
        the robot doesn't face north,
        then it will go to original point after four sequences of instruction
        */
        return (pos[0] == 0 && pos[1] == 0) || (dirId != 0);
    }
};
