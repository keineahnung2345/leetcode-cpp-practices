//O(N^2)
//TLE
//15 / 16 test cases passed.
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(nums[i] > nums[j]){
                    ++ans[i];
                }
            }
        }
        
        return ans;
    }
};
