//Binary search
//Runtime: 12 ms, faster than 71.51% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
//Memory Usage: 12.5 MB, less than 26.21% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
class Solution {
public:
    int dfs(vector<int>& nums, int pivot, int l, int r){
        if(l > r) return -1;

        int mid = (l+r) >> 1;
        // cout << mid << endl;

        /*
        found the inflection point:
        the position where right element < left element
        */
        if(mid+1 < nums.size() && nums[mid+1] < nums[mid]) return nums[mid+1];
        if(mid-1 >= 0 && nums[mid] < nums[mid-1]) return nums[mid];

        if(nums[mid] < pivot){
            return dfs(nums, pivot, l, mid-1);
        }else if(nums[mid] > pivot){
            return dfs(nums, pivot, mid+1, r);
        }else{
            //nums[mid] == pivot
            //need to search in both directions
            int res1 = dfs(nums, pivot, mid+1, r);
            int res2 = dfs(nums, pivot, l, mid-1);
            if(res1 == -1 && res2 == -1){
                return -1;
            }else if(res1 != -1){
                // if(res1 != res2 && res2 != -1){
                //     cout << "get 2 different result: " << res1 << " and " << res2 << endl;
                // }
                return res1;
            }else{
                return res2;
            }
        }
    };
    
    int findMin(vector<int>& nums) {
        int n = nums.size();
        
        if(n == 1) return nums[0];
        if(n == 2 && nums[0] == nums[1]) return nums[0];
        
        /*
        choose nums[0] as pivot, 
        so we don't need to put nums[0] in the search range
        */
        int l = 0, r = n-1;
        
        //array is sorted, not rotated
        if(nums[l] < nums[r]) return nums[l];
        
        int res = dfs(nums, nums[0], 0, n-1);
        
        return (res == -1) ? nums[0] : res;
    }
};

//Binary search, find left boundary
//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/discuss/48808/My-pretty-simple-code-to-solve-it
//Runtime: 12 ms, faster than 71.51% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
//Memory Usage: 12.3 MB, less than 74.40% of C++ online submissions for Find Minimum in Rotated Sorted Array II.
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        /*
        choose nums[n-1] as pivot, 
        so the search range is [0, n-2]
        */
        int l = 0, r = n-1-1;
        int mid;
        
        //find left boundary
        while(l <= r){
            mid = (l+r) >> 1;
            // cout << "look at [" << l << ", " << r << "] - " << mid << ", pivot: " << nums[r+1] << endl;
            
            if(nums[mid] < nums[r+1]){
                /*
                nums[mid:r+1] is increasing,
                but we want to find inflection point,
                so next we look at the left part: nums[l:mid]
                (nums[mid] is implicitly considered since it's our next pivot)
                */
                r = mid-1;
            }else if(nums[mid] > nums[r+1]){
                /*
                for the range nums[mid:r+1],
                the head is larger than the tail,
                the inflection point must be in this range,
                so next we look at the right part: nums[mid+1:r+1]
                */
                l = mid+1;
            }else{
                //nums[mid] == pivot
                /*
                since we need to find left boundary,
                it's safe to shrink right boundary
                */
                
                //https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/discuss/48808/My-pretty-simple-code-to-solve-it/48840
                if (r-1 >= 0 && nums[r-1] > nums[r]) {
                    l = r;
                    break;
                }
                --r;
            }
        }
        // cout << "look at [" << l << ", " << r << "]" << endl;
        // cout << "==============" << endl;
        
        return nums[l];
    }
};
