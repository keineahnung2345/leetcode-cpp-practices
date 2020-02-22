//Runtime: 1080 ms, faster than 6.59% of C++ online submissions for Missing Number.
//Memory Usage: 10.3 MB, less than 9.80% of C++ online submissions for Missing Number.

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        vector<int> full(nums.size()+1);
        iota(full.begin(), full.end(), 0);
        
        for(int num : nums){
            full.erase(remove(full.begin(), full.end(), num), full.end());
        }
        
        return full[0];
    }
};
