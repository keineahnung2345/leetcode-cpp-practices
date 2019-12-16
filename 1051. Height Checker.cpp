//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Height Checker.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Height Checker.

class Solution {
public:
    int heightChecker(vector<int>& heights) {
        vector<int> sorted_heights = heights;
        int num = 0;
        
        sort(sorted_heights.begin(), sorted_heights.end());
        for(int i = 0; i < heights.size(); i++){
            if(heights[i] != sorted_heights[i]) num++;
        }
        
        return num;
    }
};
