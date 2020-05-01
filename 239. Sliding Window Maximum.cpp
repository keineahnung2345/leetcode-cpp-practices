//Runtime: 56 ms, faster than 79.54% of C++ online submissions for Sliding Window Maximum.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for Sliding Window Maximum.
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int curMax = INT_MAX, curMaxPos = -1;
        vector<int> ans;
        for(int i = 0; i+k-1 < nums.size(); i++){
            //[i, i+k-1] : sliding window's range
            if(nums[i+k-1] >= curMax){
                /*
                set curMax's initial value as INT_MAX, 
                so that in first iteration it will go to 
                the "else if(i > curMaxPos)" part
                */
                curMax = nums[i+k-1];
                curMaxPos = i+k-1;
            }else if(i > curMaxPos){
                /*
                set curMaxPos's intial value as -1,
                so that in first iteration it will come here
                */
                auto it = max_element(nums.begin()+i, nums.begin()+i+k);
                curMax = *it;
                curMaxPos = it - nums.begin();
            }
            ans.push_back(curMax);
        }
        
        return ans;
    }
};

//deque
//Runtime: 36 ms, faster than 99.52% of C++ online submissions for Sliding Window Maximum.
//Memory Usage: 16.7 MB, less than 21.31% of C++ online submissions for Sliding Window Maximum.
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        deque<pair<int, int>> window; //decreasing
        
        //prepare window: [0, k-2]
        //used when calculate first element of ans
        for(int i = 0; i < k-1; i++){
            while(window.size() > 0 && window.back().first < nums[i]){
                window.pop_back();
            }
            window.push_back(make_pair(nums[i], i));
        }
        
        for(int i = k-1; i < nums.size(); i++){
            //window range: i-k+1, ... , i
            
            //keep it decreasing
            while((window.size() > 0) && (nums[i] > window.back().first)){
                window.pop_back();
            }
            window.push_back(make_pair(nums[i], i));
            
            //discard the element outside window range
            if(window.front().second == i-k){
                window.pop_front();
            }
            
            ans.push_back(window.front().first);
        }
        
        return ans;
    }
};

//deque, clean
//https://leetcode.com/problems/sliding-window-maximum/discuss/65884/Java-O(n)-solution-using-deque-with-explanation
//Runtime: 36 ms, faster than 99.52% of C++ online submissions for Sliding Window Maximum.
//Memory Usage: 16.4 MB, less than 21.31% of C++ online submissions for Sliding Window Maximum.
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n-k+1);
        deque<pair<int, int>> window; //decreasing
        
        for(int i = 0; i < nums.size(); i++){
            //window range: i-k+1, ... , i
            
            //keep it decreasing
            while((window.size() > 0) && (nums[i] > window.back().first)){
                window.pop_back();
            }
            window.push_back(make_pair(nums[i], i));
            
            //discard the element outside window range
            if(window.front().second == i-k){
                window.pop_front();
            }
            
            //start to construct ans vector when we first see k elements
            if(i >= k-1) ans[i-(k-1)] = window.front().first;
        }
        
        return ans;
    }
};
