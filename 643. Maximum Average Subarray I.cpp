/**
sliding window
**/

//Runtime: 176 ms, faster than 79.63% of C++ online submissions for Maximum Average Subarray I.
//Memory Usage: 16.8 MB, less than 100.00% of C++ online submissions for Maximum Average Subarray I.

/**
time: O(n)
space: O(1)
**/

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double maxsum;
        double cursum = 0;
        
        for(int i = 0; i < k; i++) cursum += nums[i];
        
        maxsum = cursum;
        
        for(int i = 1; i <= nums.size() - k; i++){
            cursum = cursum - nums[i-1] + nums[i+k-1];
            maxsum = max(maxsum, cursum);
        }
        
        return maxsum/k;
    }
};
