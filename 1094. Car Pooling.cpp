//Runtime: 36 ms, faster than 8.45% of C++ online submissions for Car Pooling.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Car Pooling.
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        //(coordinate, whether is start, people count)
        vector<vector<int>> points;
        
        for(vector<int>& trip : trips){
            int c = trip[0], s = trip[1], e = trip[2];
            points.push_back({s, 1, c});
            points.push_back({e, 0, c});
        }
        
        sort(points.begin(), points.end());
        
        for(vector<int>& point : points){
            int p = point[0];
            bool isStart = (bool)(point[1]);
            int c = point[2];
            
            if(isStart){
                //start point
                if(capacity < c){
                    return false;
                }
                capacity -= c;
            }else{
                //end point
                capacity += c;
            }
        }
        
        return true;
    }
};
