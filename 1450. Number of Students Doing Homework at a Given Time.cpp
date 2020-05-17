//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Students Doing Homework at a Given Time.
//Memory Usage: 10.9 MB, less than 100.00% of C++ online submissions for Number of Students Doing Homework at a Given Time.
class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int n = startTime.size();
        
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(startTime[i] <= queryTime && queryTime <= endTime[i]){
                ans++;
            }
        }
        
        return ans;
    }
};
