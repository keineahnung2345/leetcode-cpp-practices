//Runtime: 8 ms, faster than 95.64% of C++ online submissions for Search in Rotated Sorted Array II.
//Memory Usage: 14.1 MB, less than 31.59% of C++ online submissions for Search in Rotated Sorted Array II.
//time: O(N), space: O(1)
class Solution {
public:
    int findMinIdx(vector<int>& nums){
        /*
        it seems it's hard to find min_idx in
        [2,2,2,0,2,2] using binary search
        so here we use O(n) method to find min_idx
        */
        
        auto min_it = min_element(nums.begin(), nums.end());
        
        int min_idx = min_it - nums.begin();
        
        if(min_idx == 0 && nums[0] == nums.back()){
            int i = nums.size()-1;
            while(i >= 0 && nums[0] == nums[i]){
                --i;
            }
            min_idx = i+1;
        }else{
            int i = min_idx-1;
            while(i >= 0 && nums[i] == nums[min_idx]){
                --i;
            }
            min_idx = i+1;
        }
        
        return min_idx;
    };
    
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 0) return false;
        int minIdx = findMinIdx(nums);
        if(nums[minIdx] == target) return true;
        
        // cout << "minIdx: " << minIdx << endl;
        
        //this is the important part!!
        int l, r;
        if(nums[n-1] >= target){
            //we can find target in left part
            l = minIdx + 1;
            r = n-1;
        }else{
            //we can find target in left part
            l = 0;
            r = minIdx-1;
        }
        
        while(l <= r){
            int mid = l + (r-l)/2;
            
            // cout << l << " " << mid << " " << r << endl;
            
            if(nums[mid] == target){
                return true;
            }else if(nums[mid] > target){
                r = mid-1;
            }else{
                l = mid+1;
            }
        }
        
        return false;
    }
};

//Approach 1: Binary Search
//Runtime: 8 ms, faster than 95.64% of C++ online submissions for Search in Rotated Sorted Array II.
//Memory Usage: 14.2 MB, less than 12.12% of C++ online submissions for Search in Rotated Sorted Array II.
//time: O(N), space: O(1)
class Solution {
public:
    bool isBinarySearchHelpful(vector<int>& nums, int l, int ele){
        //if ele < nums[l], then ele is in second part
        //if ele > nums[l], then ele is in first part
        //if ele == nums[l], then it could exist in both parts
        // we should use the dynamically changed "l" rather than 0!!
        // l = 0;
        return nums[l] != ele;
    }
    
    bool isInFirst(vector<int>& nums, int l, int ele){
        // we should use the dynamically changed "l" rather than 0!!
        // l = 0;
        return ele >= nums[l];
    }
    
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        
        int l = 0, r = n-1;
        
        while(l <= r){
            int mid = l + (r-l)/2;
            
            // cout << l << ", " << mid << ", " << r << endl;
            
            int pivot = nums[mid];
            
            if(pivot == target){
                return true;
            }
            
            if(!isBinarySearchHelpful(nums, l, pivot)){
                ++l;
                continue;
            }
            
            bool pivotIsInFirst = isInFirst(nums, l, pivot);
            bool targetIsInFirst = isInFirst(nums, l, target);
            
            if(pivotIsInFirst ^ targetIsInFirst){
                //nums[mid] and target are in different array
                if(pivotIsInFirst){
                    //pivot in first, target in second, so search in right part
                    // cout << "p1t2" << endl;
                    l = mid+1;
                }else{
                    // cout << "p2t1" << endl;
                    r = mid-1;
                }
            }else{
                if(target > pivot){
                    // cout << "pt same, t > p" << endl;
                    l = mid+1;
                }else{
                    // cout << "pt same, t < p" << endl;
                    r = mid-1;
                }
            }
        }
        
        return false;
    }
};
