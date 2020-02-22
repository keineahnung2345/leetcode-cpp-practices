//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Construct the Rectangle.
//Memory Usage: 8.2 MB, less than 50.00% of C++ online submissions for Construct the Rectangle.

class Solution {
public:
    vector<int> constructRectangle(int area) {
        for(int i = sqrt(area); i >= 0; i--){
            if(area % i == 0){
                return vector<int>{area/i, i};
            }
        }
        return vector<int>{};
    }
};
