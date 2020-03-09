//Runtime: 16 ms, faster than 64.11% of C++ online submissions for How Many Numbers Are Smaller Than the Current Number.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for How Many Numbers Are Smaller Than the Current Number.

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int N = nums.size();
        vector<int> sorted = nums;
        vector<int> ans(N);
        
        sort(sorted.begin(), sorted.end());
        for(int i = 0; i < nums.size(); i++){
            int ix = find(sorted.begin(), sorted.end(), nums[i]) - sorted.begin();
            
            ans[i] = ix;
        }
        return ans;
    }
};
