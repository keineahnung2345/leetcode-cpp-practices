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
