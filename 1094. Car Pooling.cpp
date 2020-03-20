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

//https://leetcode.com/problems/car-pooling/discuss/317611/C%2B%2BJava-O(n)-Thousand-and-One-Stops
//Runtime: 12 ms, faster than 62.92% of C++ online submissions for Car Pooling.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Car Pooling.
//time: O(#trips), space: O(#stops)
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<int> stops(1001, 0);
        for(auto trip : trips){
            //how many people get in the car at this stop
            stops[trip[1]] += trip[0];
            stops[trip[2]] -= trip[0];
        }
        
        for(int i = 0; i < stops.size(); i++){
            capacity -= stops[i];
            if(capacity < 0) return false;
        }
        
        return true;
    }
};
