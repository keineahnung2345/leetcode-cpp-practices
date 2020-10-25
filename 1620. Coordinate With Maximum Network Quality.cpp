//brute force
//Runtime: 92 ms, faster than 48.90% of C++ online submissions for Coordinate With Maximum Network Quality.
//Memory Usage: 8.9 MB, less than 7.40% of C++ online submissions for Coordinate With Maximum Network Quality.
class Solution {
public:
    double dist(int x1, int y1, int x2, int y2){
        return sqrt((double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
    }
    
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int n = towers.size();

        if(n == 1 && towers[0][2] > 0){
            return {towers[0][0], towers[0][1]};
        }
        
        int left = INT_MAX, right = INT_MIN;
        int top = INT_MAX, bottom = INT_MIN;
        
        for(const vector<int>& tower : towers){
            left = min(left, tower[0]);
            right = max(right, tower[0]);
            top = min(top, tower[1]);
            bottom = max(bottom, tower[1]);
        }
        
        double d;
        int q;
        int maxq = 0;
        vector<int> maxcoord(2, 0);
        for(int x = left; x <= right; ++x){
            for(int y = top; y <= bottom; ++y){
                q = 0;
                for(const vector<int>& tower : towers){
                    if((d = dist(x, y, tower[0], tower[1])) > radius) continue;
                    q += tower[2]/(1+d);
                }
                if(q > maxq){
                    maxq = q;
                    maxcoord[0] = x;
                    maxcoord[1] = y;
                }
            }
        }
        
        return maxcoord;
    }
};

//priority_queue, slower
//https://leetcode.com/problems/coordinate-with-maximum-network-quality/discuss/898702/Try-all-x-y-coordinates-in-range-or-Detailed-Explanation
//Runtime: 536 ms, faster than 18.23% of C++ online submissions for Coordinate With Maximum Network Quality.
//Memory Usage: 39.8 MB, less than 7.40% of C++ online submissions for Coordinate With Maximum Network Quality.
class Solution {
public:
    double dist(int x1, int y1, int x2, int y2){
        return sqrt((double)((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
    }
    
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int n = towers.size();
        
        double d;
        int q;
        int maxq = 0;
        vector<int> maxcoord(2, 0);
        
        //(quality, x, y)
        //the larger quality, smaller x and smaller y will be popped earlier
        auto comp = [](vector<int>& a, vector<int>& b){
            return (a[0]==b[0]) ? ((a[1]==b[1]) ? (a[2] > b[2]) : (a[1] > b[1])) : (a[0] < b[0]);
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        
        for(int x = 0; x <= 50; ++x){
            for(int y = 0; y <= 50; ++y){
                q = 0;
                for(const vector<int>& tower : towers){
                    if((d = dist(x, y, tower[0], tower[1])) > radius) continue;
                    q += tower[2]/(1+d);
                }
                pq.push({q, x, y});
            }
        }
        
        // while(!pq.empty()){
        //     cout << pq.top()[0] << ", " << pq.top()[1] << ", " << pq.top()[2] << endl;
        //     pq.pop();
        // }
        
        return {pq.top()[1], pq.top()[2]};
    }
};
