//Runtime: 32 ms, faster than 15.56% of C++ online submissions for Largest Rectangle in Histogram.
//Memory Usage: 13.9 MB, less than 5.72% of C++ online submissions for Largest Rectangle in Histogram.
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            if(i+1 < n && heights[i] <= heights[i+1]){
                continue;
            }
            /*
            when the next element < current element or
            this is the last element
            
            because when next element >= current element, 
            then current element can be considered when calculating area
            
            so for efficiency purpose, 
            we start to calculate candidate ans if
            the next element is smaller than current element
            */
            int minH = INT_MAX;
            for(int j = i; j >= 0; j--){
                minH = min(minH, heights[j]);
                ans = max(ans, minH * (i-j+1));
            }
        }
        
        return ans;
    }
};
