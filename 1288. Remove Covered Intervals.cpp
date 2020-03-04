//Runtime: 24 ms, faster than 76.60% of C++ online submissions for Remove Covered Intervals.
//Memory Usage: 10.5 MB, less than 100.00% of C++ online submissions for Remove Covered Intervals.
class Solution {
public:
    bool isCovered(int a, int b, int c, int d){
        //check whether [a,b) is covered by [c,d)
        return c <= a && b <= d;
    };
    
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int covered = 0;
        int N = intervals.size();
        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i != j && isCovered(intervals[i][0], intervals[i][1], intervals[j][0], intervals[j][1])) covered++;
            }
        }

        return N-covered;
    }
};

//sort, one pass
//https://leetcode.com/problems/remove-covered-intervals/discuss/451277/JavaC%2B%2BPython-Sort-Solution-Test-Cases-are-Trash
//time: O(NlogN), space: O(N)
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int res = 0, left = -1, right = -1;
        sort(intervals.begin(), intervals.end());
        for(vector<int>& v : intervals){
            //v[0] same as left: remove last interval
            //v[0] bigger, v[1] same as right: remove current interval
            if(v[0] > left && v[1] > right){
                //later interval can only has left and right boundary >= current left and right boundary
                //so update "left"
                left = v[0];
                //current interval is not covered, so add it
                res++;
            }
            //v[0] same as left: remove last interval and make right bigger
            //v[0] bigger, v[1] same as right: right is not changed
            right = max(right, v[1]);
        }
        return res;
    }
};
