//geometric mean
//https://leetcode.com/problems/best-position-for-a-service-centre/discuss/731577/C%2B%2B-with-picture-zoom-in
//Runtime: 396 ms, faster than 25.00% of C++ online submissions for Best Position for a Service Centre.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Best Position for a Service Centre.
class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        double left, bottom, right, top;
        left = bottom = numeric_limits<double>::max();
        right = top = numeric_limits<double>::lowest();

        for(vector<int>& pt : positions){
            left = min(left, (double)pt[0]);
            right = max(right, (double)pt[0]);
            bottom = min(bottom, (double)pt[1]);
            top = max(top, (double)pt[1]);
        }

        double minDist = numeric_limits<double>::max();
        double minX, minY;
        for(double delta = 1.0; delta >= 1e-5; delta/=10){
            for(double x = left; x <= right; x += delta){
                for(double y = bottom; y <= top; y += delta){
                    double dist = 0.0;
                    for(vector<int>& pt : positions){
                        dist += sqrt(pow((double)pt[0]-x, 2) + pow((double)pt[1]-y, 2));
                    }
                    if(dist < minDist){
                        minDist = dist;
                        minX = x;
                        minY = y;
                    }
                }
            }
            // WA: 48 / 56 test cases passed.
            // left = minX - delta*0.5;
            // right = minX + delta*0.5;
            // bottom = minY - delta*0.5;
            // top = minY + delta*0.5;
            left = minX - delta;
            right = minX + delta;
            bottom = minY - delta;
            top = minY + delta;
        }

        return minDist;
    }
};
