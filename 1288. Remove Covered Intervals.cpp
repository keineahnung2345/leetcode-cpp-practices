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
