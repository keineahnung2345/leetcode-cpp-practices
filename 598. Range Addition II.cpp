//Runtime: 12 ms, faster than 60.71% of C++ online submissions for Range Addition II.
//Memory Usage: 11.6 MB, less than 50.00% of C++ online submissions for Range Addition II.
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int rsize = m, csize = n;
        
        for(vector<int>& op : ops){
            rsize = min(rsize, op[0]);
            csize = min(csize, op[1]);
        }
        
        return rsize * csize;
    }
};
