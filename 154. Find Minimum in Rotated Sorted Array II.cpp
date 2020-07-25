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
