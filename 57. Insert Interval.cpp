//Runtime: 32 ms, faster than 70.39% of C++ online submissions for Insert Interval.
//Memory Usage: 17.1 MB, less than 42.94% of C++ online submissions for Insert Interval.
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<int> start_dummy = {-1, newInterval[0]};
        vector<int> end_dummy = {newInterval[1], -1};
        
        //the smallest interval with end >= start_dummy[1]
        auto it1 = lower_bound(intervals.begin(), intervals.end(),
          start_dummy,
          [](const vector<int>& a, const vector<int>& b){
              return a[1] < b[1];
          });
        
        if(it1 == intervals.end()){
            intervals.push_back(newInterval);
            return intervals;
        }
        // cout << (*it1)[0] << ", " << (*it1)[1] << endl;
        
        //the smallest interval with start > end_dummy[0]
        auto it2 = upper_bound(intervals.begin(), intervals.end(),
          end_dummy,
          [](const vector<int>& a, const vector<int>& b){
              return a[0] < b[0];
          });
        if(it2 == intervals.begin()){
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        
        //the largest interval with start <= end_dummy[0]
        it2 = prev(it2);
        
        // cout << (*it2)[0] << ", " << (*it2)[1] << endl;
        
        if(it1 == it2){
            *it1 = {min((*it1)[0], newInterval[0]),
                max((*it1)[1], newInterval[1])};
        }else if(it1 < it2){
            vector<int> insertInterval = {
                min((*it1)[0], newInterval[0]),
                max((*it2)[1], newInterval[1])
            };
            *it1 = insertInterval;
            //erase [it1+1, it2]
            intervals.erase(it1+1, it2+1);
        }else{
            //it2 < it1
            //newInterval should be insert btw it2 and it1
            intervals.insert(it1, newInterval);
        }
        
        return intervals;
    }
};

//https://leetcode.com/problems/insert-interval/discuss/21602/Short-and-straight-forward-Java-solution
//Runtime: 28 ms, faster than 87.60% of C++ online submissions for Insert Interval.
//Memory Usage: 16.9 MB, less than 89.34% of C++ online submissions for Insert Interval.
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int i = 0, n = intervals.size();
        
        //smaller, no intersection
        while(i < n && intervals[i][1] < newInterval[0]){
            ans.push_back(intervals[i]);
            ++i;
        }
        
        //having intersection
        int start = newInterval[0], end = newInterval[1];
        while(i < n && intervals[i][0] <= end){
            start = min(intervals[i][0], start);
            end = max(intervals[i][1], end);
            ++i;
        }
        
        ans.push_back({start, end});
        
        while(i < n){
            ans.push_back(intervals[i]);
            ++i;
        }
        
        return ans;
    }
};
