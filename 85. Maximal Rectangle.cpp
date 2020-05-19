//https://www.cnblogs.com/grandyang/p/4322667.html
//Runtime: 96 ms, faster than 11.10% of C++ online submissions for Maximal Rectangle.
//Memory Usage: 11.7 MB, less than 27.78% of C++ online submissions for Maximal Rectangle.
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        vector<int> heights(n+1);
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            /*
            we view each row as a problem of 84.Largest Rectangle in Histogram
            */
            stack<int> stk;
            for(int j = 0; j < heights.size(); j++){
                //update heights for current row
                if(j < n){
                    heights[j] = (matrix[i][j] == '1') ? heights[j]+1 : 0;
                }
                //same as 84. Largest Rectangle in Histogram
                while(!stk.empty() && heights[j] < heights[stk.top()]){
                    int cur = stk.top(); stk.pop();
                    ans = max(ans, heights[cur] * (stk.empty() ? j : (j-1-stk.top())));
                }
                stk.push(j);
            }
        }
        
        return ans;
    }
};
