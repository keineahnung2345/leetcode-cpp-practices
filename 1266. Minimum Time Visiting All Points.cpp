//Runtime: 4 ms, faster than 99.42% of C++ online submissions for Minimum Time Visiting All Points.
//Memory Usage: 10.1 MB, less than 100.00% of C++ online submissions for Minimum Time Visiting All Points.

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        if(points.size() < 2) return 0;
        int steps = 0;
        int xdiff, ydiff, diagSteps, straightSteps;
        for(int i = 1; i < points.size(); i++){
            xdiff = points[i][0] - points[i-1][0];
            ydiff = points[i][1] - points[i-1][1];
            //Method 1
            // diagSteps = min(abs(xdiff), abs(ydiff));
            // straightSteps = max(abs(xdiff), abs(ydiff)) - diagSteps;
            // steps += (diagSteps + straightSteps);
            //Method 2, optimized from Method 1
            steps += max(abs(xdiff), abs(ydiff));
        }
        return steps;
    }
};
