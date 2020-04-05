//Runtime: 36 ms, faster than 33.33% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
//Memory Usage: 10.8 MB, less than 100.00% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        if(nums.size() == 0) return vector<int>();
        sort(nums.rbegin(), nums.rend());
        
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int curSum = 0;
        int i = 0;
        vector<int> ans;
        
        while(curSum <= sum/2.0){
            ans.push_back(nums[i]);
            curSum += nums[i];
            i++;
        }
        
        return ans;
    }
};

//priority queue
//Runtime: 32 ms, faster than 33.33% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
//Memory Usage: 11 MB, less than 100.00% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int curSum = 0;
        vector<int> ans;
        
        priority_queue<int, vector<int>, less<int>> pq(nums.begin(), nums.end());
        
        while(curSum <= sum/2.0){
            int cur = pq.top(); pq.pop();
            ans.push_back(cur);
            curSum += cur;
        }
        
        return ans;
    }
};
