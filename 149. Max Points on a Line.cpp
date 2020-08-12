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

//use coprime to represent slope!
//Runtime: 32 ms, faster than 73.31% of C++ online submissions for Max Points on a Line.
//Memory Usage: 9.9 MB, less than 55.26% of C++ online submissions for Max Points on a Line.
class Solution {
public:
    int n;
    map<pair<int, int>, int> lines;
    
    pair<int, int> slope_coprime(int x1, int y1, int x2, int y2){
        int dx = x1 - x2, dy = y1 - y2;
        if(dx == 0){
            //vertical line
            return {0, 0};
        }else if(dy == 0){
            //horizontal line
            return {INT_MAX, INT_MAX};
        }
        
        //the nominator must be >= 0
        if(dx < 0){
            dx *= -1;
            dy *= -1;
        }
        
        int gcd = __gcd(dx, dy);
        
        return {dx/gcd, dy/gcd};
    };
    
    void add_line(vector<vector<int>>& points, int i, int j, int &count, int& dup){
        //update the map "lines", and update "count" and "dup"
        int x1 = points[i][0];
        int y1 = points[i][1];
        int x2 = points[j][0];
        int y2 = points[j][1];
        
        if(x1 == x2 && y1 == y2){
            //points[i] and points[j] are either same point
            ++dup;
        }else{
            //or different point, then we need to calculate their line's slope
            pair<int, int> slope = slope_coprime(x1, y1, x2, y2);
            if(lines.find(slope) == lines.end()) lines[slope] = 2;
            else ++lines[slope];
            count = max(lines[slope], count);
        }
    };
    
    int max_count_on_lines(vector<vector<int>>& points, int i){
        //max count of points on a line passing through points[i]
        lines.clear();
        int count = 1;
        int dup = 0; //count of points at same position as points[i]
        
        //for a points[i], we only need to look after!!
        for(int j = i+1; j < n; ++j){
            add_line(points, i, j, count, dup);
        }
        
        return count + dup;
    };
    
    int maxPoints(vector<vector<int>>& points) {
        n = points.size();
        if(n <= 2) return n;
        
        int max_count = 1;
        
        for(int i = 0; i < n-1; ++i){
            max_count = max(max_count, max_count_on_lines(points, i));
        }
        
        return max_count;
    }
};
