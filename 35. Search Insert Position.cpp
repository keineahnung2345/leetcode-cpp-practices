//Runtime: 8 ms, faster than 98.48% of C++ online submissions for Search Insert Position.
//Memory Usage: 8.9 MB, less than 97.84% of C++ online submissions for Search Insert Position.

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        //find the first number larger than target
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] >= target) return i;
        }
        //if target is the largest
        return nums.size();
    }
};

//binary search
//Runtime: 4 ms, faster than 99.20% of C++ online submissions for Search Insert Position.
//Memory Usage: 9.7 MB, less than 57.82% of C++ online submissions for Search Insert Position.
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n-1;
        int mid;
        
        //find lower bound
        while(l <= r){
            mid = l + (r-l)/2;
            if(nums[mid] == target){
                return mid;
            }else if(nums[mid] < target){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        
        return l;
    }
};
