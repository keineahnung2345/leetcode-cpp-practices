//Runtime: 4 ms, faster than 92.92% of C++ online submissions for Next Permutation.
//Memory Usage: 12.2 MB, less than 47.00% of C++ online submissions for Next Permutation.
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return;
        
        for(int i = n-2; i >= 0; --i){
            if(nums[i] < nums[i+1]){
                //select the minidx s.t. nums[minidx] > nums[i] and is the smallest among nums[i+1:]
                int minidx = i+1;
                for(int j = i+1; j < n; ++j){
                    if(nums[j] > nums[i]){
                        minidx = (nums[j] < nums[minidx]) ? j : minidx;
                    }
                }
                
                //this is wrong!!
                // auto it = min_element(nums.begin()+i+1, nums.end());
                
                swap(nums[i], nums[minidx]);
                sort(nums.begin()+i+1, nums.end());
                return;
            }
        }
        
        sort(nums.begin(), nums.end());
    }
};

//Approach 2: Single Pass Approach
//Runtime: 4 ms, faster than 92.92% of C++ online submissions for Next Permutation.
//Memory Usage: 12.4 MB, less than 18.40% of C++ online submissions for Next Permutation.
//time: O(N), space: O(1)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        
        int i = n-2;
        
        while(i >= 0 && nums[i] >= nums[i+1]){
            --i;
        }
        
        if(i >= 0){
            //nums[i] < nums[i+1]
            int j = n-1;
            
            /*
            find a j > i s.t. nums[j] > nums[i] and 
            is the smallest in nums[i+1:],
            to do this, we find from the end,
            because nums[i+1:] is in descending order
            */
            while(j >= 0 && nums[j] <= nums[i]){
                --j;
            }
            
            swap(nums[i], nums[j]);
            
            //after swapping, nums[i+1:] is still in descending order
        }
        
        reverse(nums.begin()+i+1, nums.end());
    }
};
