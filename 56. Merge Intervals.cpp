//TLE
//168 / 169 test cases passed.
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return intervals;
        
        sort(intervals.begin(), intervals.end());
        
        int i = 1;
        while(i < intervals.size()){
            // cout << i << " ";
            //last end >= current start
            if(intervals[i-1][1] >= intervals[i][0]){
                //merge them
                intervals[i-1][1] = max(intervals[i-1][1], intervals[i][1]);
                intervals.erase(intervals.begin()+i);
            }else{
                i++;
            }
        }
        
        return intervals;
    }
};
