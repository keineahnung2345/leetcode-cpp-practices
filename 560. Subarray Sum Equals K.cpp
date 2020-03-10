//Runtime: 904 ms, faster than 5.05% of C++ online submissions for Subarray Sum Equals K.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Subarray Sum Equals K.
//time: O(n^2), space: O(n)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int ans = 0;
        int n = nums.size();
        
        //convert "nums" to prefix sum
        for(int i = 1; i < n; i++){
            nums[i] += nums[i-1];
        }
        
        for(int low = 0; low < n; low++){
            for(int high = low; high < n; high++){
                int cursum = nums[high] - ((low > 0) ? nums[low-1] : 0);
                if(cursum == k) ans++;
            }
        }
        
        return ans;
    }
};
