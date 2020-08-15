//WA
//15 / 18 test cases passed.
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        set<int> points;
        
        int n = intervals.size();
        
        for(int i = 0; i < n; ++i){
            points.insert(intervals[i][0]);
            points.insert(intervals[i][1]);
        }
        
        unordered_map<int, int> shrink;
        
        auto it = points.begin();
        for(int i = 0; i < points.size(); ++i, ++it){
            shrink[*it] = i;
        }
        
        for(vector<int>& interval : intervals){
            interval[0] = shrink[interval[0]];
            interval[1] = shrink[interval[1]];
        }
        
        sort(intervals.begin(), intervals.end(),
            [](vector<int>& a, vector<int>& b){
                return (a[1]-a[0] == b[1]-b[0]) ? a[0] < b[0]: a[1]-a[0] < b[1]-b[0];
            });
        
        unordered_set<int> used;
        
        int discarded = 0;
        
        for(int i = 0; i < n; ++i){
            bool overlapping = false;
            for(int p = intervals[i][0]; p < intervals[i][1]; ++p){
                if(used.find(p) != used.end()){
                    overlapping = true;
                    break;
                }
            }
            if(!overlapping){
                for(int p = intervals[i][0]; p < intervals[i][1]; ++p){
                    used.insert(p);
                }
            }else{
                ++discarded;
            }
        }
        
        return discarded;
    }
};
