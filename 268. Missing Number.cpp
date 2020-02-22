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

//https://leetcode.com/problems/missing-number/discuss/69777/C%2B%2B-solution-using-bit-manipulation
//Runtime: 24 ms, faster than 80.72% of C++ online submissions for Missing Number.
//Memory Usage: 9.9 MB, less than 70.59% of C++ online submissions for Missing Number.
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int result = 0;
        //exclusive-or from (a) [0 to n] and (b) [all number in "nums"]
        //same numbers in (a) and (b) will counteract each other
        //so it will remain 0 ^ the missing number = the missing nuber
        for(int i = 0; i < nums.size(); i++){
            result ^= nums[i];
            result ^= i;
        }
        result ^= nums.size();
        return result;
    }
};
