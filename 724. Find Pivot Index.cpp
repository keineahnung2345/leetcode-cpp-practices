/**
Approach #1: Prefix Sum [Accepted]
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the length of nums.

Space Complexity: O(1)O(1), the space used by leftsum and S.
**/

//Runtime: 28 ms, faster than 98.42% of C++ online submissions for Find Pivot Index.
//Memory Usage: 9.8 MB, less than 100.00% of C++ online submissions for Find Pivot Index.

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int allsum = accumulate(nums.begin(), nums.end(), 0);
        int cumsum = 0;
        
        for(int i = 0; i < nums.size(); i++){
            if(cumsum*2 == (allsum-nums[i])){
                return i;
            }
            cumsum += nums[i];
        }
        
        return -1;
    }
};
