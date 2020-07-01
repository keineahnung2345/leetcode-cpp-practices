//priority queue
//https://leetcode.com/problems/max-value-of-equation/discuss/709231/Python-Stack-O(N)
//Runtime: 896 ms, faster than 29.81% of C++ online submissions for Max Value of Equation.
//Memory Usage: 112.3 MB, less than 100.00% of C++ online submissions for Max Value of Equation.
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //(y-x, x)
        priority_queue<vector<int>, vector<vector<int>>> pq;
        
        int ans = INT_MIN;
        
        for(vector<int>& point : points){
            //current point serves as points[j]
            int x = point[0], y = point[1];
            
            /*
            we only need points[i] s.t. |x_i - x_j| <= k,
            and because points is already sorted by x,
            so x_i must <= x_j, the inequality can be expressed as
            x_j - x_i <= k.
            we will discard points[i] s.t. x_j - x_i > k
            */
            while(!pq.empty() && x - pq.top()[1] > k){
                pq.pop();
            }
            
            if(!pq.empty()){
                /*
                y_i + y_j + |x_i - x_j|
                = y_i + y_j + x_j - x_i
                = (y_i - x_i) + (y_j + x_j)
                
                in which y_j + x_j is solely determined
                by current point(it serves as points[j]),
                so what we want to find is the points[i]
                s.t. i < j and with max (y_i - x_i)
                */
                ans = max(ans, pq.top()[0] + (y + x));
            }
            
            pq.push({y-x, x});
        }
        
        return ans;
    }
};

//monotonic deque
//https://leetcode.com/problems/max-value-of-equation/discuss/709231/Python-Stack-O(N)
//Runtime: 700 ms, faster than 52.36% of C++ online submissions for Max Value of Equation.
//Memory Usage: 109.1 MB, less than 100.00% of C++ online submissions for Max Value of Equation.
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //(y-x, x)
        deque<vector<int>> deq;
        
        int ans = INT_MIN;
        
        for(vector<int>& point : points){
            int x = point[0], y = point[1];
            
            while(!deq.empty() && x - deq.front()[1] > k){
                deq.pop_front();
            }
            
            if(!deq.empty()){
                ans = max(ans, deq.front()[0] + (y + x));
            }
            
            /*
            keep the deque decreasing(fronter element has larger y-x)
            the element before current point must have larger y-x
            */
            while(!deq.empty() && deq.back()[0] <= y - x){
                deq.pop_back();
            }
            
            deq.push_back({y-x, x});
        }
        
        return ans;
    }
};
