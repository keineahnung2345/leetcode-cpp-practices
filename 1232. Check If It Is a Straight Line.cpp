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

//cross prodcut
//Runtime: 20 ms, faster than 14.27% of C++ online submissions for Check If It Is a Straight Line.
//Memory Usage: 10.2 MB, less than 100.00% of C++ online submissions for Check If It Is a Straight Line.
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        
        if(n == 2) return true;
        
        //the vector from coordinates[0] to coordinates[1]
        vector<int> v1 = {coordinates[1][0] - coordinates[0][0], coordinates[1][1] - coordinates[0][1]};
        vector<int> v2;
        
        for(int i = 2; i < n; i++){
            v2 = {coordinates[i][0] - coordinates[0][0], coordinates[i][1] - coordinates[0][1]};
            //cross product
            //this is equivalent to comparing their slope: v2[1]/v2[0] == v1[1]/v1[0]
            if(v1[0]*v2[1] - v1[1]*v2[0] != 0) return false;
        }
        
        return true;
    }
};
