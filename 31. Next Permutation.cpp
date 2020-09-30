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
