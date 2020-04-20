//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Minimum Value to Get Positive Step by Step Sum.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Minimum Value to Get Positive Step by Step Sum.
class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int cumMin = INT_MAX;
        int cumSum = 0;
        
        for(int num : nums){
            cumSum += num;
            cumMin = min(cumMin, cumSum);
        }
        
        if(cumMin > 0) return 1;
        return -cumMin + 1;
    }
};
