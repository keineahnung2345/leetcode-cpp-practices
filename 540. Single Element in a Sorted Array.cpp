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

//binary saerch
//Runtime: 12 ms, faster than 47.40% of C++ online submissions for Single Element in a Sorted Array.
//Memory Usage: 11.1 MB, less than 7.14% of C++ online submissions for Single Element in a Sorted Array.
class Solution {
public:
    bool afterSingle(vector<int>& nums, int mid){
        int n = nums.size();
        
        // if(mid % 2 == 0){
        if(!(mid&1)){ //speed up from 16ms to 12ms
            //nums[mid] should equal to nums[mid+1]
            //if mid is even, mid must < n(n is always odd)
            if(mid+1 < n && nums[mid] == nums[mid+1]){
                //single element is on its right
                return false;
            }else{
                //single element is on its left
                return true;
            }
        }else{
            //nums[mid] should equal to nums[mid-1]
            //if mid is odd, mid must > 0
            if(/*mid > 0 && */nums[mid] == nums[mid-1]){
                //single element is on its right
                return false;
            }else{
                //single element is on its left
                return true;
            }
        }
    };
    
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n-1;
        int mid;
        
        while(left <= right){
            mid = left + (right - left)/2;
            // cout << left << ", " << mid << ", " << right << endl;
            
            if(afterSingle(nums, mid)){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        
        return nums[left];
    }
};
