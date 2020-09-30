//binary search
//Runtime: 16 ms, faster than 90.01% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
//Memory Usage: 14.1 MB, less than 10.23% of C++ online submissions for Find First and Last Position of Element in Sorted Array.
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        
        if(n == 0) return {-1, -1};
        
        int left = 0, right = n-1;
        
        //find left boundary
        while(left <= right){
            int mid = (left+right) >> 1;
            // cout << left << ", " << mid << ", " << right << endl;
            
            if(nums[mid] < target){
                left = mid+1;
            }else{
                right = mid-1;
            }
        }
        
        if(left >= n || nums[left] != target){
            return {-1, -1};
        }
        
        vector<int> ans = {left};
        
        //find right boundary
        left = 0;
        right = n-1;
        while(left <= right){
            int mid = (left+right) >> 1;
            // cout << left << ", " << mid << ", " << right << endl;
            
            if(nums[mid] > target){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        
        ans.push_back(right);
        
        return ans;
    }
};
