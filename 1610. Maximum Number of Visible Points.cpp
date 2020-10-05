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
