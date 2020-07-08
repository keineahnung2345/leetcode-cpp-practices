//https://www.cnblogs.com/grandyang/p/4322653.html
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

//monotonic stack
//https://www.cnblogs.com/grandyang/p/4322653.html
//Runtime: 24 ms, faster than 40.27% of C++ online submissions for Largest Rectangle in Histogram.
//Memory Usage: 14.1 MB, less than 5.72% of C++ online submissions for Largest Rectangle in Histogram.
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //increasing stack, start to calculate area when we meet smaller element
        stack<int> stk;
        int ans = 0;
        //to ensure the last element will be used to calculate area
        heights.push_back(0);
        
        for(int i = 0; i < heights.size(); i++){
            //start to calculate area when we find a smaller element
            //continue the process until i's height >= stk.top()'s
            while(!stk.empty() && heights[i] < heights[stk.top()]){
                int cur = stk.top(); stk.pop();
                /*
                i-1: the right boundary of rectangle
                we meet i, which is lower than stk.top(),
                it is only used to trigger calculating area,
                and our rectangle does not include column i
                
                stk.top()+1: the left boundary of rectangle
                NOTE: cur and stk.top() are different!!
                stk.top() if the index of rectangle which is even lower than cur
                our rectangle can only extend to stk.top()+1
                because stk.top()'s height is lower than heights[cur]
                
                heights[cur]: lowest element's height
                */
                // cout << heights[cur] << " * " << (stk.empty() ? i : (i -1 - stk.top())) << ", " << stk.size() << " elements in stack." << endl;
                // if(!stk.empty()){
                //     vector<int> tmp(&stk.top()+1-stk.size(), &stk.top() + 1);
                //     cout << "stack elements: ";
                //     for(int e : tmp){
                //         cout << e << " ";
                //     }
                //     cout << endl;
                // }
                ans = max(ans, heights[cur] * (stk.empty() ? i : (i- 1 - stk.top())));
            }
            //when stk.empty() || heights[i] >= heights[stk.top()]
            stk.push(i);
        }
        
        return ans;
    }
};

//DP
//https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/28902/5ms-O(n)-Java-solution-explained-(beats-96)
//Runtime: 24 ms, faster than 40.27% of C++ online submissions for Largest Rectangle in Histogram.
//Memory Usage: 14.2 MB, less than 5.72% of C++ online submissions for Largest Rectangle in Histogram.
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        
        vector<int> leftLower(n);
        vector<int> rightLower(n);
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            int p = i-1;
            /*
            if i-1's height >= i's height,
            we need to go backward.
            since heights[p] >= heights[i] and
            all q in [leftLower[p]+1, p-1] >= heights[p],
            so we skip these q and choose leftLower[p] as our next trial
            */
            while(p >= 0 && heights[p] >= heights[i]){
                p = leftLower[p];
            }
            leftLower[i] = p;
        }
        
        for(int i = n-1; i >= 0; i--){
            int p = i+1;
            
            while(p < n && heights[p] >= heights[i]){
                p = rightLower[p];
            }
            rightLower[i] = p;
        }
        
        for(int i = 0; i < n; i++){
            ans = max(ans, (rightLower[i]-leftLower[i]-1) * heights[i]);
        }
        
        return ans;
    }
};
