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

//DP
//https://www.cnblogs.com/grandyang/p/4322667.html
//https://leetcode.com/problems/maximal-rectangle/discuss/29054/Share-my-DP-solution/175299
//Runtime: 52 ms, faster than 40.28% of C++ online submissions for Maximal Rectangle.
//Memory Usage: 11 MB, less than 61.11% of C++ online submissions for Maximal Rectangle.
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        if(n == 0) return 0;
        
        //current number of continuous '1' at column i
        vector<int> height(n, 0);
        /*
        left boundary of continuous '1' in current row
        leftmost p which all q in [p, i-1] all satisfies height[q] >= height[i]
        
        because initial values of height is 0 for all i,
        so all q in [0,i-1] has height[q] = 0 >= height[i] = 0,
        so the initial value of the left array is all 0
        */
        vector<int> left(n, 0);
        /*
        right boundary of continuous '1' in current row
        rightmost p which all q in [i+1, q] all satisfies height[q] >= height[i]
        
        because initial values of height is 0 for all i,
        so all q in [i+1,n-1] has height[q] = 0 >= height[i] = 0,
        so the initial value of the right array is all n-1
        */
        vector<int> right(n, n-1);
        int ans = 0;
        
        for(int i = 0; i < m; i++){
            //left boundary for current row
            int cur_left = 0;
            //right boundary for current row
            int cur_right = n-1;
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == '1'){
                    height[j]++;
                    /*
                    within the boundary of previous of height array and
                    within the boundary of current row
                    */
                    left[j] = max(left[j], cur_left);
                    //cur_left maintains the same when we meet continuous '1'
                }else{
                    height[j] = 0;
                    /*
                    since height[j] = 0, by definition, all q in [0, j-1] 
                    satisfies height[q] >= height[j], so left[j] should be set to 0
                    
                    set to 0 so that it won't affect 
                    the result of "left[j] = max(left[j], cur_left);"
                    */
                    left[j] = 0;
                    /*
                    will be used when we meet next '1'
                    
                    leftmost boundary of continuous '1' should be at least j+1
                    */
                    cur_left = j+1;
                }
            }
            
            for(int j = n-1; j >= 0; j--){
                if(matrix[i][j] == '1'){
                    right[j] = min(right[j], cur_right);
                    // cout << "(" << i << ", " << j << "): [" << left[j] << ", " << right[j] << "] x " << height[j] << endl;
                    ans = max(ans, (right[j]-left[j]+1) * height[j]);
                }else{
                    /*
                    set to n-1 so that it won't affect 
                    the result of "right[j] = min(right[j], cur_right);"
                    */
                    right[j] = n-1;
                    cur_right = j-1;
                }
            }
        }
        
        return ans;
    }
};
