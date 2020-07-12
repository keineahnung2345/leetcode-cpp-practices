//Runtime: 324 ms, faster than 33.33% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
//Memory Usage: 35.4 MB, less than 100.00% of C++ online submissions for Minimum Difference Between Largest and Smallest Value in Three Moves.
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        
        // cout << "n: " << n << endl;
        
        if(n <= 3) return 0;
        
        sort(nums.begin(), nums.end());
        
        int minDiff = INT_MAX;
        
        for(int i = 0; i <= 3; ++i){
            minDiff = min(minDiff, nums[n-1-i] - nums[3-i]);
        }
        
        // return min(nums[n-4] - nums[0], nums[n-1] - nums[3]);
        return minDiff;
    }
};
