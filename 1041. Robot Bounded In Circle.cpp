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
