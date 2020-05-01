//sliding window, dp, heap
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

//sliding window, dp, decreasing deque
//https://leetcode.com/problems/constrained-subsequence-sum/discuss/597751/JavaC%2B%2BPython-O(N)-Decreasing-Deque
//Runtime: 240 ms, faster than 51.00% of C++ online submissions for Constrained Subsequence Sum.
//Memory Usage: 41.1 MB, less than 100.00% of C++ online submissions for Constrained Subsequence Sum.
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> window;
        vector<int> dp(n, 0);
        int ans = INT_MIN;
        
        for(int i = 0; i < n; i++){
            /*
            deque stores the dp value from dp[i-1] to dp[i-k],
            in decreasing order
            */
            dp[i] = nums[i] + ((window.size() > 0) ? window.front() : 0);
            cout << dp[i] << " ";
            ans = max(ans, dp[i]);
            
            /*
            we only use the deque to extract max dp value,
            so if current dp value are largest,
            the stored dp values are useless
            
            every elements in the deque < dp[i] will be discarded,
            so dp[i] will be the smallest value in the deque,
            and we may push dp[i] to the back of the deque,
            so we can say that the deque is decreasing
            */
            while(window.size() > 0 && dp[i] > window.back()){
                window.pop_back();
            }
            
            /*
            we can discard negative dp value,
            for example, suppose we are calculating dp[3],
            but dp[0], dp[1], and dp[2] are negative,
            then we set dp[3] as nums[3],
            that means we discard all former values,
            and set the start of the window at index 3
            */
            if(dp[i] > 0){
                window.push_back(dp[i]);
            }
            
            /*
            prepare for next iteration,
            discard dp value out of window
            
            it seems the size of window is not important, 
            we just want to make sure that 
            when we are calculating new dp[i], 
            window.front() is one of dp[i-1]...dp[i-k],
            */
            if(window.size() > 0 && i-k >= 0 && window.front() == dp[i-k]){
                window.pop_front();
            }
        }
        
        return ans;
    }
};
