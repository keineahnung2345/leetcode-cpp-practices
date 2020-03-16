//Runtime: 4 ms, faster than 95.59% of C++ online submissions for Trapping Rain Water.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Trapping Rain Water.
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = 0;
        int ans = 0;
        int N = height.size();
        
        while(right < N){
            int valley = height[left];
            
            //left wall should have height > 0
            while(left < N && height[left] == 0){
                left++;
            }
            //cannot find left wall
            if(left == N) break;

            //right wall should be larger than valley
            for(right = left+1; right < N && height[right] <= valley; right++){
                valley = min(valley, height[right]);
            }
            //cannot find right wall
            if(right == N) break;
            // cout << "left: " << left << ", right: " << right << endl;
            
            //we've found a valid right wall,
            //now we want to discover higher right wall
            //we only need to find a higher right wall when right wall is lower than left wall
            int head = right+1;
            if(height[left] > height[right]){
                int last = right;
                while(head < N && height[head] < height[left]){
                    if(height[head] > height[last]){
                        last = head;
                    }
                    head++;
                }
                if(head < N && height[head] >= height[left]){
                    //found a right wall >= left wall
                    right = head;
                }else{
                    //found the highest right wall > original right wall
                    right = last;
                }
            }
            
            //calculate current trapping water amount
            int lh = height[left], rh = height[right];
            for(int i = left+1; i < min(right, N); i++){
                // cout << i << ", height: " << height[i] << endl;
                //we should take max(0, x) here!
                ans += max(0, min(lh, rh) - height[i]);
            }
            // cout << left << " " << right << " " << valley << " " << ans << endl;

            left = right;
        }
        
        return ans;
    }
};

//Approach 1: Brute force
//Runtime: 312 ms, faster than 5.10% of C++ online submissions for Trapping Rain Water.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Trapping Rain Water.
//time: O(n^2), space: O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        
        for(int i = 0; i < height.size(); i++){
            int maxLeft = 0, maxRight = 0;
            for(int j = i; j >= 0 ; j--){
                maxLeft = max(maxLeft, height[j]);
            }
            for(int j = i; j < height.size() ; j++){
                maxRight = max(maxRight, height[j]);
            }
            ans += min(maxLeft, maxRight) - height[i];
            // cout << maxLeft << " " << maxRight << " " << ans << endl;
        }
        
        return ans;
    }
};

//Approach 2: Dynamic Programming
//Runtime: 4 ms, faster than 95.59% of C++ online submissions for Trapping Rain Water.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Trapping Rain Water.
//time: O(n), space: O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int N = height.size();
        if(N == 0) return 0;
        int ans = 0;
        
        vector<int> leftMax(N), rightMax(N);
        leftMax[0] = height[0];
        for(int i = 1; i < N; i++){
            leftMax[i] = max(leftMax[i-1], height[i]);
        }
        
        rightMax[N-1] = height[N-1];
        for(int i = N-2; i >= 0; i--){
            rightMax[i] = max(rightMax[i+1], height[i]);
        }
        
        for(int i = 1; i < N-1; i++){
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        
        return ans;
    }
};

//Approach 3: Using stacks
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Trapping Rain Water.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Trapping Rain Water.
//time: O(n), space: O(n)
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, cur = 0;
        stack<int> stk;
        for(int cur = 0; cur < height.size(); cur++){
            // cout << cur << endl;
            // if(!stk.empty()){
            //     cout << "stack: ";
            //     vector<int> tmp(&stk.top()+1-stk.size(), &stk.top()+1);
            //     for(int i = 0; i < tmp.size(); i++){
            //         cout << tmp[i] << " ";
            //     }
            //     cout << endl;
            // }
            while(!stk.empty() && height[cur] > height[stk.top()]){
                int top = stk.top(); stk.pop();
                // cout << "pop: " << top << endl;
                if(stk.empty()){
                    break;
                }
                //top is bounded by previous bar in the stack and current bar   
                int dist = cur - stk.top() - 1;
                //the left and right walls are : stk.top(), cur
                int bounded_height = min(height[stk.top()], height[cur]) - height[top];
                ans += dist * bounded_height;
                // cout << "[" << stk.top() << ", " << cur << "] " << ans << endl;
            }
            //the current bar is bounded by previous bar in the stack
            stk.push(cur);
        }
        return ans;
    }
};

//Approach 4: Using 2 pointers
//Runtime: 4 ms, faster than 95.59% of C++ online submissions for Trapping Rain Water.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Trapping Rain Water.
//time: O(n), space: O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int N = height.size();
        if(N == 0) return 0;
        int left = 0, right = N-1;
        int leftMax = 0, rightMax = 0;
        int ans = 0;
        while(left < right){
            if(height[left] > leftMax){
                leftMax = height[left];
            }
            if(height[right] > rightMax){
                rightMax = height[right];
            }
            if(leftMax < rightMax){
                //use leftMax to substract because leftMax is min(leftMax, rightMax)
                ans += max(0, leftMax - height[left]);
                // cout << "[" << left << ", " << right << "] " << leftMax << " " << rightMax << " " << ans << endl;
                left++;
            }else{
                ans += max(0, rightMax - height[right]);
                // cout << "[" << left << ", " << right << "] " << leftMax << " " << rightMax << " " << ans << endl;
                right--;
            }
        }
        return ans;
    }
};
