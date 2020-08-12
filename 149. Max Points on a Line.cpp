//{slope, intercept} counter
//WA
//https://leetcode.com/submissions/detail/379863182/
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        unordered_map<double, int> slope_map, intc_map;
        // unordered_map<pair<double, double>, int> lineCounter;
        map<pair<double, double>, unordered_set<int>> lineCounter;
        // map<pair<int, int>, int> lineCounter;
        
        int n = points.size();
        if(n == 1) return 1;
        
        double slope, intc;
        int slope_idx, intc_idx;
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                // cout << "(" << i << ", " << j << "): " << endl;
                if(points[i][0] == points[j][0]){
                    slope = INT_MAX;
                    intc = points[i][0];
                }else{
                    // cout << "diffy: " << points[i][1] - points[j][1] << ", diffx: " << points[i][0] - points[j][0] << endl;
                    slope = (double)(points[i][1] - points[j][1])/(points[i][0] - points[j][0]);
                    intc = points[i][1] + (-points[i][0]) * slope;
                }
                // cout << slope << ", " << intc << endl;
                
                lineCounter[{slope, intc}].insert(i);
                lineCounter[{slope, intc}].insert(j);
                ans = max(ans, (int)lineCounter[{slope, intc}].size());
            }
        }
        
        return ans;
    }
};
