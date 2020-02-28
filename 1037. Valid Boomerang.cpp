//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Valid Boomerang.
//Memory Usage: 7.4 MB, less than 100.00% of C++ online submissions for Valid Boomerang.

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        //same point?
        vector<int> a = points[0], b = points[1], c = points[2];
        if((a[0] == b[0] && a[1] == b[1]) || (a[0] == c[0] && a[1] == c[1]) || (b[0] == c[0] && b[1] == c[1]))
            return false;
        
        //on same vertical line?
        if(a[0] == b[0] || a[0] == c[0]){
            if((a[0] == b[0]) && (a[0] == c[0])){
                return false;
            }
            return true;
        }
        
        //same slope?
        double slope = (a[1] - b[1])/(double)(a[0] - b[0]);
        if(a[0] == c[0]) return false;
        if((a[1]-c[1])/(double)(a[0]-c[0]) == slope){
            return false;
        }
        return true;
    }
};
