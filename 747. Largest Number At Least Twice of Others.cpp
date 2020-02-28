//Runtime: 4 ms, faster than 69.65% of C++ online submissions for Largest Number At Least Twice of Others.
//Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Largest Number At Least Twice of Others.

class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if(nums.size() == 1) return 0;
        
        vector<int> nums_copy = nums;
        
        nth_element(nums_copy.begin(), nums_copy.begin()+1, nums_copy.end(), greater<int>());
        // cout << nums_copy[0] << ", " << nums_copy[1] << endl;
        return nums_copy[0] >= nums_copy[1] * 2 ? (find(nums.begin(), nums.end(), nums_copy[0]) - nums.begin()) : -1;
    }
};
