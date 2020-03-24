//TLE
//28 / 29 test cases passed.
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        for(int i = 0; i < nums.size()-1; i++){
            for(int j = i+1; j < nums.size(); j++){
                ans = max(ans, nums[i]^nums[j]);
            }
        }
        return ans;
    }
};
