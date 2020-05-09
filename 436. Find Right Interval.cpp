//lower_bound
//Runtime: 236 ms, faster than 19.59% of C++ online submissions for Find Right Interval.
//Memory Usage: 29.9 MB, less than 20.00% of C++ online submissions for Find Right Interval.
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<int>> si(n); //(start point, index)
        for(int i = 0; i < intervals.size(); i++){
            si[i] = {intervals[i][0], i};
        }
        
        sort(si.begin(), si.end());
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; i++){
            /*
            dummy variable just used for binary search
            set dummy variable's starting point as intervals[i]'s end point, 
            just for comparison purpose
            */
            vector<int> dummy = {intervals[i][1], -1};
            //find interval whose starting point <= current end point
            auto it = lower_bound(si.begin(), si.end(), dummy,
                [](const vector<int>& v1, const vector<int>& v2){
                    return v1[0] < v2[0];
                    });
            if(it == si.end()){
                ans[i] = -1;
            }else{
                ans[i] = (*it)[1];
            }
        }
        
        return ans;
    }
};

//map::lower_bound
//https://leetcode.com/problems/find-right-interval/discuss/91819/C%2B%2B-map-solution
//Runtime: 160 ms, faster than 40.67% of C++ online submissions for Find Right Interval.
//Memory Usage: 27.8 MB, less than 20.00% of C++ online submissions for Find Right Interval.
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        map<int, int> si; //(start point, index)
        for(int i = 0; i < intervals.size(); i++){
            si[intervals[i][0]] = i;
        }
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; i++){
            auto it = si.lower_bound(intervals[i][1]);
            if(it == si.end()){
                ans[i] = -1;
            }else{
                ans[i] = it->second;
            }
        }
        
        return ans;
    }
};
