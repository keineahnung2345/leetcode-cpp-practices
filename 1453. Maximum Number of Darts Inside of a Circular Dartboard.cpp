//https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/discuss/636332/cpp-O(N3)-solution-with-pictures.
//https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/discuss/636345/Simple-Python-O(n3)-Solution-with-picture
//Runtime: 184 ms, faster than 14.29% of C++ online submissions for Maximum Number of Darts Inside of a Circular Dartboard.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Maximum Number of Darts Inside of a Circular Dartboard.
//time: O(N^3)
class Solution {
public:
    const double eps = 1e-6;
    
    double getDist(vector<double>& p1, vector<double>& p2){
        return sqrt(pow(p1[0]-p2[0], 2.0) + pow(p1[1]-p2[1], 2.0));
    };
    
    vector<vector<double>> findCircles(vector<double>& p1, vector<double>& p2, int r){
        vector<vector<double>> centers; //center of circles
        
        double dist = getDist(p1, p2);
        
        vector<double> mid = {(p1[0]+p2[0])/2.0, (p1[1]+p2[1])/2.0};
        
        // cout << "dist: " << dist << endl;
        // cout << "(" << mid[0] << ", " << mid[1] << ")" << endl;
        
        //can not find a circle that cover the two points
        if(dist > 2*r+eps){ //compare with diameter, not radius!
            //pass
        }else if(abs(dist-2.0*r) < eps){
            centers.push_back(mid);
        }else{
            double bisection = sqrt(pow(r, 2.0) - pow(dist/2.0, 2.0));
            //dx and dy should not be taken abs()!!
            double dx = p1[0]-p2[0];
            double dy = p1[1]-p2[1];
            
            /*
            c1x = mid[0] + bisection*sin(theta)
            dist*sin(theta) = dy
            so c1x = mid[0] + bisection*dy/dist
            
            c1y = mid[1] + bisection*cos(theta)
            dist*cos(theta) = abs(dx) = -dx
            so c1y = mid[1] - bisection*dx/dist
            */
            //dx and dy could be negative!!
            double c1x = mid[0] + dy*bisection/dist;
            double c1y = mid[1] - dx*bisection/dist;
            centers.push_back({c1x, c1y});
            
            double c2x = mid[0] - dy*bisection/dist;
            double c2y = mid[1] + dx*bisection/dist;
            centers.push_back({c2x, c2y});
        }
        
        return centers;
    };
    
    int getNumPointsInside(vector<vector<double>>& points, vector<double>& center, int r){
        int count = 0;
        for(vector<double>& point : points){
            if(getDist(point, center) <= r+eps){
                count++;
            }
        }
        return count;
    };
    
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        vector<vector<double>> centers;
        int ans = 0;
        
        vector<vector<double>> dpoints;
        for (auto&& p : points) dpoints.emplace_back(std::begin(p), std::end(p));
        
        //iterate through each pair of points
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                centers = findCircles(dpoints[i], dpoints[j], r);
                // cout << i << " " << j << ": " << centers.size() << endl;
                for(int k = 0; k < centers.size(); k++){
                    ans = max(ans, getNumPointsInside(dpoints, centers[k], r));
                }
            }
        }
        
        //we can always find a circle to include one point
        //points.size() >= 1
        return max(ans, 1);
    }
};

//angular sweep
//https://www.geeksforgeeks.org/angular-sweep-maximum-points-can-enclosed-circle-given-radius/
//Runtime: 52 ms, faster than 89.34% of C++ online submissions for Maximum Number of Darts Inside of a Circular Dartboard.
//Memory Usage: 16.2 MB, less than 100.00% of C++ online submissions for Maximum Number of Darts Inside of a Circular Dartboard.
//time: O(N^2logN), space: O(N^2)
class Solution {
public:
    vector<vector<double>> dist;
    
    double getDist(vector<int>& p1, vector<int>& p2){
        return sqrt(pow(p1[0]-p2[0], 2.0)+pow(p1[1]-p2[1], 2.0));
    };
    
    int getPointsInside(vector<vector<int>>& points, int i, int r){
        int n = points.size();
        vector<pair<double, bool>> angles;
        
        for(int j = 0; j < n; j++){
            if(j == i || dist[i][j] > 2*r) continue;
            double B = acos(dist[i][j]/(2.0*r));
            double A = atan2(points[j][1]-points[i][1], 
                            points[j][0]-points[i][0]);
            double alpha = A-B;
            double beta = A+B;
            //reversed definition with geeksforgeeks
            //because we want alpha(which is entry point) be visited earlier than exit point!
            angles.emplace_back(alpha, false);
            angles.emplace_back(beta, true);
            // cout << j << ", A: " << A << ", B: " << B << " alpha: " << alpha << ", beta: " << beta << endl;
        }
        
        // cout << "angles.size() : " << angles.size() << endl;
        
        sort(angles.begin(), angles.end());
        
        // for(auto p : angles){
        //     cout << p.first << ", " << p.second << endl;
        // }
        
        int count = 1, res = 1;
        
        for(auto it = angles.begin(); it != angles.end(); it++){
            if(!it->second){
                count++;
            }else{
                count--;
            }
            // cout << "enter: " << (it->second) << ", " << it->first << ", count: " << count << endl;
            res = max(res, count);
        }
        
        // cout << i << ": " << res << endl;
        
        return res;
    };
    
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        dist = vector<vector<double>>(n, vector<double>(n, 0.0));
        
        for(int i = 0; i < n-1; i++){
            for(int j = i+1; j < n; j++){
                dist[i][j] = dist[j][i] = getDist(points[i], points[j]);
                // cout << i << ", " << j << " : " << dist[i][j] << endl;
            }
        }
        
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            ans = max(ans, getPointsInside(points, i, r));
        }
        
        return ans;
    }
};
