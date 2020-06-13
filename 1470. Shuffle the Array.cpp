//Runtime: 8 ms, faster than 95.90% of C++ online submissions for Shuffle the Array.
//Memory Usage: 9.8 MB, less than 100.00% of C++ online submissions for Shuffle the Array.
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2*n, 0);
        for(int i = 0, j = 0; i < n; i++, j+=2){
            ans[j] = nums[i];
            ans[j+1] = nums[i+n];
        }
        return ans;
    }
};
