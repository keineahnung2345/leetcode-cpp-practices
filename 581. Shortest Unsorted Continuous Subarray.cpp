//Runtime: 80 ms, faster than 58.67% of C++ online submissions for Shortest Unsorted Continuous Subarray.
//Memory Usage: 27.6 MB, less than 7.63% of C++ online submissions for Shortest Unsorted Continuous Subarray.
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        
        int start = -1, end = -1;
        for(int i = 0; i < n; ++i){
			if(nums[i] != sorted[i]){
                start = i;
                break;
            }
        }
        if(start == -1) return 0;
        
        for(int i = n-1; i >= 0; --i){
			if(nums[i] != sorted[i]){
                end = i;
                break;
            }
        }
        return end - start + 1;
    }
};
