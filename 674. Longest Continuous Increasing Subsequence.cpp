//Runtime: 16 ms, faster than 98.15% of C++ online submissions for Longest Continuous Increasing Subsequence.
//Memory Usage: 9.3 MB, less than 98.08% of C++ online submissions for Longest Continuous Increasing Subsequence.

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        
        int l = 1;
        int ans = INT_MIN;
        
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] - nums[i-1] <= 0){
                ans = max(ans, l);
                l = 1;
            }else{
                l++;
            }
            // cout << l << endl;
        }
        ans = max(ans, l);
        // cout << endl;
        
        return ans;
    }
};

/**
Approach #1: Sliding Window [Accepted]
**/

/**
Complexity Analysis

Time Complexity: O(N)O(N), where NN is the length of nums. We perform one loop through nums.

Space Complexity: O(1)O(1), the space used by anchor and ans.
**/

/**
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int ans = 0, anchor = 0;
        for(int i = 0; i < nums.size(); i++){
            //restart when series be non-increasing
            if(i > 0 && nums[i] <= nums[i-1]) anchor = i;
            ans = max(ans, i - anchor + 1);
        }
        return ans;
    }
};
**/
