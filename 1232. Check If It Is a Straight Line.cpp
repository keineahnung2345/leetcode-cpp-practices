//Runtime: 8 ms, faster than 91.80% of C++ online submissions for Check If It Is a Straight Line.
//Memory Usage: 10.5 MB, less than 100.00% of C++ online submissions for Check If It Is a Straight Line.
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        //remember to convert to "double"!
        double slope = (double)(coordinates[1][1] - coordinates[0][1]) / 
                (coordinates[1][0] - coordinates[0][0]);
        // cout << slope << endl;
        for(int i = 2; i < coordinates.size(); i++){
            vector<int> a = coordinates[i], b = coordinates[i-1];
            // cout << (double)(a[1] - b[1]) / (a[0] - b[0]) << endl;
            if(slope != (double)(a[1] - b[1]) / (a[0] - b[0])){
                return false;
            }
        }
        cout << endl;
        
        return true;
    }
};
