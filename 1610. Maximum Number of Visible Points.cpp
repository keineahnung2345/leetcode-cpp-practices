//two pointer
//WA
//16 / 120 test cases passed.
//[[956,232],[438,752],[595,297],[508,143],[111,594],[645,824],[758,434],[447,423],[825,356],[807,377]]
//38
//[74,581]
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<double> angles;
        
        int must_visible = 0;
        
        for(const vector<int>& point : points){
            int xdiff = point[0] - location[0];
            int ydiff = point[1] - location[1];
            
            double a = -1;
            
            if(xdiff == 0){
                if(ydiff == 0){
                    ++must_visible;
                }else if(ydiff > 0){
                    a = 90;
                }else if(ydiff < 0){
                    a = 270;
                }
            }else if(ydiff == 0){
                a = (xdiff > 0) ? 0 : 180;
            }else{
                a = atan(ydiff/xdiff);
                a = a*180.0/M_PI;
                
                if(ydiff < 0){
                    a += 180;
                }
            }
            
            // cout << xdiff << ", " << ydiff << ", " << a << endl;
            
            if(a != -1) angles.push_back(a);
        }
        
        // cout << "angles: " << endl;
        // for(const double& d : angles){
        //     cout << d << " ";
        // }
        // cout << endl;
        
        sort(angles.begin(), angles.end());
        
        vector<double> angles_p360 = angles;
        for(int i = 0; i < angles_p360.size(); ++i){
            angles_p360[i] += 360;
        }
        for(int i = 0; i < angles_p360.size(); ++i){
            angles.push_back(angles_p360[i]);
        }
        
        int max_visible_by_rotate = 0;
        for(int i = 0, j = 0; i < angles.size(); ++i){
            while(j < angles.size() && 
                  (angles[j] - angles[i] - angle - 1e-1
                   /*numeric_limits<double>::epsilon() * max({abs(angles[j]), abs(angles[i]), abs((double)angle)})*/ <= 0)){
                ++j;
            }
            max_visible_by_rotate = max(max_visible_by_rotate, j-i);
        }
        
        // cout << "must_visible: " << must_visible << endl;
        // cout << "max_visible_by_rotate: " << max_visible_by_rotate << endl;
        
        return must_visible + max_visible_by_rotate;
    }
};

//two pointer, atan's range is [-M_PI/2, M_PI/2]!!
//https://leetcode.com/problems/maximum-number-of-visible-points/discuss/877735/C%2B%2B-Clean-with-Explanation
//Runtime: 800 ms, faster than 50.00% of C++ online submissions for Maximum Number of Visible Points.
//Memory Usage: 135.4 MB, less than 50.00% of C++ online submissions for Maximum Number of Visible Points.
class Solution {
public:
    double getAngle1(double xdiff, double ydiff){
        //a in [-M_PI/2, M_PI/2]
        double a = atan(ydiff/xdiff);
        
        //[-M_PI/2, M_PI/2] -> [0, 2*M_PI]
        if(xdiff < 0 && ydiff > 0){
            //2nd quadrant
            a += M_PI;
        }else if(xdiff < 0 && ydiff < 0){
            //3rd quadrant
            a += M_PI;
        }else if(xdiff > 0 && ydiff < 0){
            //4th quadrant
            a += M_PI*2;
        }
        a = a/M_PI*180.0;
        
        return a;
    }
    
    double getAngle2(double xdiff, double ydiff){
        // atan2: [-M_PI, M_PI]
        double a = atan2(ydiff, xdiff);
        // [-M_PI, M_PI] -> [0, M_PI*2]
        if(a < 0) a += M_PI*2;
        a = a/M_PI*180.0;
        
        return a;
    }
    
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<double> angles;
        
        int must_visible = 0;
        
        for(const vector<int>& point : points){
            int xdiff = point[0] - location[0];
            int ydiff = point[1] - location[1];
            
            double a = -1;
            
            if(xdiff == 0 && ydiff == 0){
                ++must_visible;
            }else if(xdiff == 0){
                a = (ydiff > 0) ? 90 : 270;
            }else{
                a = getAngle2(xdiff, ydiff);
                // cout << getAngle1(xdiff, ydiff) << ", " << getAngle2(xdiff, ydiff) << endl;
            }
            
            if(a != -1) angles.push_back(a);
        }
        
        // cout << "angles: " << endl;
        // for(const double& d : angles){
        //     cout << d << " ";
        // }
        // cout << endl;
        
        sort(angles.begin(), angles.end());
        
        vector<double> angles_p360 = angles;
        for(int i = 0; i < angles_p360.size(); ++i){
            angles_p360[i] += 360;
        }
        for(int i = 0; i < angles_p360.size(); ++i){
            angles.push_back(angles_p360[i]);
        }
        
        int max_visible_by_rotate = 0;
        
        //actually 1e-9 is not needed here
        for(int i = 0, j = 0; i < angles.size(); ++i){
            while(j < angles.size() && angles[j] - angles[i] <= angle + 1e-9){
                ++j;
            }
            max_visible_by_rotate = max(max_visible_by_rotate, j-i);
        }
        
        //why add 1e-9 on RHS????
        // for(int i = 0, j = 0; j < angles.size(); ++j){
        //     while(i < angles.size() && angles[j] - angles[i] >= angle + 1e-9){
        //         ++i;
        //     }
        //     max_visible_by_rotate = max(max_visible_by_rotate, j-i+1);
        // }
        
        // cout << "must_visible: " << must_visible << endl;
        // cout << "max_visible_by_rotate: " << max_visible_by_rotate << endl;
        
        return must_visible + max_visible_by_rotate;
    }
};
