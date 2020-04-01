//Runtime: 72 ms, faster than 98.67% of C++ online submissions for Bulb Switcher III.
//Memory Usage: 11.6 MB, less than 100.00% of C++ online submissions for Bulb Switcher III.
class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int curMax = 0;
        int ans = 0;
        
        for(int i = 0; i < light.size(); i++){
            curMax = max(curMax, light[i]);
            if(curMax == i+1) ans ++;
        }
        
        return ans;
    }
};
