//O(N) naive
//Runtime: 8 ms, faster than 76.83% of C++ online submissions for Find Peak Element.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Find Peak Element.
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        // n >= 1
        // if(n == 1) return 0;
        // if(n == 2) return (nums[0] > nums[1]) ? 0 : 1;
        
        for(int i = 0; i < n; ++i){
            //to handle the boundary
            if(nums[i] > max(i == 0 ? LLONG_MIN : nums[i-1], 
                             i == n-1 ? LLONG_MIN : nums[i+1])) return i;
        }
        
        return -1;
    }
};

//cleaner O(N)
//Approach 1: Linear Scan
//Runtime: 8 ms, faster than 76.83% of C++ online submissions for Find Peak Element.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Find Peak Element.
//time: O(N), space: O(1)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        
        for(int i = 0; i+1 < n; ++i){
            /*
            when we are at i, nums[i] must > nums[i-1],
            otherwise it will return at previous step
            */
            if(nums[i] > nums[i+1]) return i;
        }
        
        //note this edge case!!
        return n-1;
    }
};

//Approach 3: Iterative Binary Search
//Runtime: 8 ms, faster than 76.83% of C++ online submissions for Find Peak Element.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Find Peak Element.
//time: O(logN), space: O(1)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        
        //use binary search to find local maximum
        
        int l = 0, r = n-1;
        
        while(l <= r){
            //stop when the search space contains only one element
            if(l == r) return l;
            
            int mid = l + ((r-l)>>1);
            
            // cout << l << ", " << mid << ", " << r << endl;
            
            if(nums[mid] > nums[mid+1]){
                //it's on falling slope
                //find on the left
                r = mid;
            }else{
                //it's on rising slope
                //find on the right
                l = mid+1;
            }
        }
        
        return -1;
    }
};

//official
//Approach 3: Iterative Binary Search
//Runtime: 4 ms, faster than 98.84% of C++ online submissions for Find Peak Element.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Find Peak Element.
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        
        int l = 0, r = n-1;
        
        while(l < r){
            int mid = l + ((r-l)>>1);
            
            // cout << l << ", " << mid << ", " << r << endl;
            
            if(nums[mid] > nums[mid+1]){
                r = mid;
            }else{
                l = mid+1;
            }
        }
        
        //now l is equal to r
        //return r; //works
        return l; //works
    }
};

//Approach 2: Recursive Binary Search
//Runtime: 4 ms, faster than 98.84% of C++ online submissions for Find Peak Element.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Find Peak Element.
//time: O(logN)
//space: O(1)
class Solution {
public:
    int search(vector<int>& nums, int l, int r){
        if(l == r) return l;
        
        int mid = l + ((r-l)>>1);
        
        if(nums[mid] > nums[mid+1]){
            return search(nums, l, mid);
        }
        
        return search(nums, mid+1, r);
    }
    
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        
        return search(nums, 0, n-1);
    }
};
