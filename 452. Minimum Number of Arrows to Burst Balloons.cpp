//Runtime: 308 ms, faster than 17.60% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
//Memory Usage: 24.6 MB, less than 100.00% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 0) return 0;
        
        sort(points.begin(), points.end());
        
        int start = points[0][0], end = points[0][1];
        int ans = 1; //we need at least one arrow
        
        for(vector<int>& point : points){
            // cout << point[0] << " " << point[1] << endl;
            //Note it's "<=" !
            if(point[0] <= end){
                //they have intersection
                start = point[0];
                //need to update end!
                end = min(end, point[1]);
            }else{
                ans++;
                start = point[0];
                end = point[1];
            }
        }
        
        return ans;
    }
};

//sort by ending point
//https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/discuss/93703/Share-my-explained-Greedy-solution
//Runtime: 200 ms, faster than 22.81% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
//Memory Usage: 24.8 MB, less than 100.00% of C++ online submissions for Minimum Number of Arrows to Burst Balloons.
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 0) return 0;
        
        //sort by ending point
        sort(points.begin(), points.end(), 
            [](vector<int>& a, vector<int>& b){
                return a[1] < b[1];
            });
        
        //shot to the end of first balloon
        int arrowPos = points[0][1];
        int arrowCnt = 1;
        
        for(vector<int>& point : points){
            if(point[0] <= arrowPos){
                //we can use the last arrow to shot this balloon
                continue;
            }
            //we cannot use previous arrow, we need a new one
            arrowCnt++;
            arrowPos = point[1];
        }
        
        return arrowCnt;
    }
};
