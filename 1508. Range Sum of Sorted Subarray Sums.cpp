//brute force
//Runtime: 640 ms, faster than 14.29% of C++ online submissions for Range Sum of Sorted Subarray Sums.
//Memory Usage: 19.1 MB, less than 100.00% of C++ online submissions for Range Sum of Sorted Subarray Sums.
class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        int MOD = 1e9+7;
        
        vector<int> subsums;
        
        for(int i = 0; i < n; ++i){
            int cursum = nums[i];
            subsums.push_back(cursum);
            for(int j = i+1; j < n; ++j){
                cursum += nums[j];
                subsums.push_back(cursum);
            }
        }
        
        sort(subsums.begin(), subsums.end());
        
        return accumulate(subsums.begin()+(left-1), subsums.begin()+right, 0, [&MOD](int& a, int& b){return (a+b) % MOD;});
    }
};

//priority_queue
//https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/discuss/730511/C%2B%2B-priority_queue-solution
//Runtime: 8 ms, faster than 100.00% of C++ online submissions for Range Sum of Sorted Subarray Sums.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Range Sum of Sorted Subarray Sums.
class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        //the smaller the earlier to be popped
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        int MOD = 1e9+7;
        
        for(int i = 0; i < n; ++i){
            //p.second: the index of next element to be appended to subarray
            pq.push({nums[i], i+1});
        }
        
        int ans = 0;
        
        for(int i = 1; i <= right; ++i){
            //stop when we see "right" smallest subarrays' sums
            
            pair<int, int> p = pq.top(); pq.pop();
            
            if(i >= left){
                //we want the [left, right]th subarray's sum(1-based)
                ans = (ans + p.first) % MOD;
            }
            
            if(p.second < n){
                pq.push({p.first+nums[p.second++], p.second});
            }
        }
        
        return ans;
    }
};
