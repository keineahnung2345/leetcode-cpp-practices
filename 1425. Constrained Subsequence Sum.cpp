//heap, sliding window, dp
//Runtime: 396 ms, faster than 33.09% of C++ online submissions for Constrained Subsequence Sum.
//Memory Usage: 50 MB, less than 100.00% of C++ online submissions for Constrained Subsequence Sum.
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        deque<int> window;
        //(dp[index], index)
        priority_queue<pair<int, int>, vector<pair<int, int>>> windowHeap;
        int ans = INT_MIN;
        
        for(int i = 0; i < n; i++){
            //window contains the dp value from dp[i-k] to dp[i-1]
            // dp[i] = nums[i] + (window.size() > 0 ? *max_element(window.begin(), window.end()) : 0);
            int windowMax = 0;
            if(window.size() > 0){
                pair<int, int> p = windowHeap.top();
                while(p.second < i-k){
                    //it's outside the window
                    windowHeap.pop();
                    p = windowHeap.top();
                }
                windowMax = p.first;
            }
            dp[i] = nums[i] + windowMax;
            
            ans = max(ans, dp[i]);
            
            //update sliding window
            if(window.size() == k){
                window.pop_front();
            }
            
            if(dp[i] >= 0){
                window.push_back(dp[i]);
                windowHeap.push(make_pair(dp[i], i));
            }
            
        }
        
        //max dp value from dp[n-1] to dp[n-k]
        // return *max_element(window.begin(), window.end());
        // return dp.back();
        // return *max_element(dp.begin(), dp.end());
        return ans;
    }
};
