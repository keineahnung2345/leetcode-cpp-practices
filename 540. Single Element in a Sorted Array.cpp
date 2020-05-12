//Runtime: 16 ms, faster than 29.23% of C++ online submissions for Single Element in a Sorted Array.
//Memory Usage: 11.2 MB, less than 7.14% of C++ online submissions for Single Element in a Sorted Array.
//time: O(N), space: O(1)
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ans = 0;
        for(int num : nums){
            ans ^= num;
        }
        return ans;
    }
};
