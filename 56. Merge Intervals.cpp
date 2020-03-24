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

//the above method removes merged intervals, this method add unmerged intervals into ans
//Runtime: 32 ms, faster than 29.99% of C++ online submissions for Merge Intervals.
//Memory Usage: 10 MB, less than 100.00% of C++ online submissions for Merge Intervals.
//time: O(NlogN), space: O(1) if it's in-place sorting or O(N)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return intervals;
        
        sort(intervals.begin(), intervals.end());
        
        vector<vector<int>> ans;
        
        for(vector<int>& interval : intervals){
            if(ans.empty() || ans[ans.size()-1][1] < interval[0]){
                ans.push_back(interval);
            }else{
                ans[ans.size()-1][1] = max(ans[ans.size()-1][1], interval[1]);
            }
        }
        
        return ans;
    }
};
