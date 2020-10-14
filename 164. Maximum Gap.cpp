//sorting
//Runtime: 8 ms, faster than 98.12% of C++ online submissions for Maximum Gap.
//Memory Usage: 8.9 MB, less than 10.99% of C++ online submissions for Maximum Gap.
//time: O(NlogN)
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        
        for(int i = 1; i < n; ++i){
            ans = max(ans, nums[i] - nums[i-1]);
        }
        
        return ans;
    }
};
