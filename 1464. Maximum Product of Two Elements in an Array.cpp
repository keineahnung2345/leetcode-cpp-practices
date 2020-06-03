//sort
//Runtime: 16 ms, faster than 58.26% of C++ online submissions for Maximum Product of Two Elements in an Array.
//Memory Usage: 9.9 MB, less than 100.00% of C++ online submissions for Maximum Product of Two Elements in an Array.
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        sort(nums.rbegin(), nums.rend());
        
        return (nums[0]-1) * (nums[1]-1);
    }
};
