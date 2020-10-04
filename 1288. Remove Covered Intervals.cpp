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
//time: O(NlogN), space: O(1)
//Runtime: 24 ms, faster than 76.60% of C++ online submissions for Remove Covered Intervals.
//Memory Usage: 11.1 MB, less than 100.00% of C++ online submissions for Remove Covered Intervals.
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

//revise from https://leetcode.com/problems/remove-covered-intervals/discuss/451277/JavaC%2B%2BPython-Sort-Solution-Test-Cases-are-Trash
//easier to understand
//Runtime: 52 ms, faster than 66.90% of C++ online submissions for Remove Covered Intervals.
//Memory Usage: 11.5 MB, less than 57.75% of C++ online submissions for Remove Covered Intervals.
//time: O(NlogN), space: O(1)
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int res = 0, left = -1, right = -1;
        sort(intervals.begin(), intervals.end());
        for(vector<int>& v : intervals){
            //v[0] can only >= left
            if(v[0] == left){
                //v[1] can only >= right
                if(v[1] == right){
                    //the two intervals are exactly the same
                    //discard current interval
                }else{
                    //v[1] > right
                    //last interval is covered by current interval
                    right = v[1];
                }
            }else{
                //v[0] > left
                if(v[1] <= right){
                    //current interval is covered by last interval
                }else{
                    //v[1] > right
                    //the two intervals cannot cover each other
                    left = v[0];
                    right = v[1];
                    ++res;
                }
            }
        }
        return res;
    }
};

//sort left ascending, right descending
//Runtime: 44 ms, faster than 89.91% of C++ online submissions for Remove Covered Intervals.
//Memory Usage: 11.6 MB, less than 50.00% of C++ online submissions for Remove Covered Intervals.
//time: O(NlogN), space: O(1)
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        //sort left ascending, right descending
        sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b){
                return (a[0] == b[0]) ? a[1] > b[1] : a[0] < b[0];
                });
        
        int res = 0, right = -1;
        
        for(const vector<int>& v : intervals){
            if(v[1] > right){
                //in this case v[1] > right and v[0] > left
                ++res;
                right = v[1];
            }
            /*
            ignore these cases:
            1. v[0]==left && v[1]<=right:
            these intervals are covered by last interval
            2. v[0]>left && v[1]<=right:
            these intervals are covered by last interval
            */
        }
        
        return res;
    }
};
