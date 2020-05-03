//sliding windows + heap
//Runtime: 364 ms, faster than 14.29% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
//Memory Usage: 34.6 MB, less than 100.00% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int ans = 0;
        int slow = 0;
        
        // sort(nums.begin(), nums.end());
        
        // for(int i = 0; i < n; i++){
        //     cout << nums[i] << " ";
        // }
        // cout << endl;
        
        priority_queue<pair<int,int>, vector<pair<int,int>>> pqMax; //max popped first
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pqMin; //min popped first
        
        int wMaxIdx = 0, wMinIdx = 0;
        for(int fast = 0; fast < n; fast++){
            pqMax.push(make_pair(nums[fast], fast));
            pqMin.push(make_pair(nums[fast], fast));
            
            //find a valid slow, pop all invalid element from pqMin and pqMax
            // cout << "before [" << slow << ", " << fast << "]" << endl;
            // cout << "max: " << pqMax.top().first << ", " << pqMax.top().second << endl;
            // cout << "min: " << pqMin.top().first << ", " << pqMin.top().second << endl;
            while(pqMax.top().first - pqMin.top().first > limit){
                if(pqMax.top().second < pqMin.top().second){
                    //remove max value
                    //can't simply use "slow = pqMax.top().second+1;"
                    slow = max(slow, pqMax.top().second+1);
                    pqMax.pop();
                }else{
                    slow = max(slow, pqMin.top().second+1);
                    pqMin.pop();
                }
                // cout << "max: " << pqMax.top().first << ", " << pqMax.top().second << endl;
                // cout << "min: " << pqMin.top().first << ", " << pqMin.top().second << endl;
            }
            
            // if(fast - slow + 1 > ans){
                // cout << "after [" << slow << ", " << fast << "]" << endl;
            // }
            //fast - slow + 1: window size
            ans = max(ans, fast - slow + 1);
            
            //outside the window
            while(pqMax.top().second < slow){
                pqMax.pop();
            }
            while(pqMin.top().second < slow){
                pqMin.pop();
            }
        }
        
        return ans;
    }
};

//sliding window + deque, revised from 1425. Constrained Subsequence Sum.cpp
//Runtime: 136 ms, faster than 42.86% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
//Memory Usage: 35.1 MB, less than 100.00% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int ans = 0;
        int slow = 0;
        
        deque<pair<int,int>> maxQ;
        deque<pair<int,int>> minQ;
        
        int wMaxIdx = 0, wMinIdx = 0;
        for(int fast = 0; fast < n; fast++){
            while(maxQ.size() > 0 && maxQ.back().first < nums[fast]){
                maxQ.pop_back();
            }
            while(minQ.size() > 0 && minQ.back().first > nums[fast]){
                minQ.pop_back();
            }
            maxQ.push_back(make_pair(nums[fast], fast));
            minQ.push_back(make_pair(nums[fast], fast));
            
            //find a valid slow
            while(maxQ.front().first - minQ.front().first > limit){
                if(maxQ.front().second < minQ.front().second){
                    //remove max value
                    slow = max(slow, maxQ.front().second+1);
                    maxQ.pop_front();
                }else{
                    slow = max(slow, minQ.front().second+1);
                    minQ.pop_front();
                }
            }
            
            // cout << slow << ", " << fast << endl;
            ans = max(ans, fast - slow + 1);
            
            //outside the window
            while(maxQ.front().second < slow){
                maxQ.pop_front();
            }
            while(minQ.front().second < slow){
                minQ.pop_front();
            }
        }
        
        return ans;
    }
};

//sliding window + deque, cleaner
//https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/discuss/609771/JavaC%2B%2BPython-Deques-O(N)
//Runtime: 108 ms, faster than 71.43% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
//Memory Usage: 32.8 MB, less than 100.00% of C++ online submissions for Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit.
//time: O(N), space: O(N)
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int ans = 0;
        int slow = 0;
        
        deque<int> maxQ;
        deque<int> minQ;
        
        for(int fast = 0; fast < n; fast++){
            while(!maxQ.empty() && maxQ.back() < nums[fast]) maxQ.pop_back();
            while(!minQ.empty() && minQ.back() > nums[fast]) minQ.pop_back();
            /*
            we don't need to record the index, why? 
            */
            maxQ.push_back(nums[fast]);
            minQ.push_back(nums[fast]);
            
            //find a valid slow, dealing with the data structure and slow pointer at the same time
            while(maxQ.front() - minQ.front() > limit){
                // cout << slow << ", " << fast << endl;
                if(maxQ.front() == nums[slow])maxQ.pop_front();
                if(minQ.front() == nums[slow])minQ.pop_front();
                slow++;
            }
            
            // cout << "** " << slow << ", " << fast << " **" << endl;
            ans = max(ans, fast - slow + 1);
            
            // the data structure is already processed together with slow
            // //outside the window
            // while(maxQ.front().second < slow){
            //     maxQ.pop_front();
            // }
            // while(minQ.front().second < slow){
            //     minQ.pop_front();
            // }
        }
        cout << endl;
        
        return ans;
    }
};
