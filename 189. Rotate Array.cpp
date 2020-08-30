//Naive solution
//Runtime: 4 ms, faster than 99.57% of C++ online submissions for Rotate Array.
//Memory Usage: 10.1 MB, less than 22.54% of C++ online submissions for Rotate Array.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            ans[(i+k)%n] = nums[i];
        }
        
        for(int i = 0; i < n; ++i){
            nums[i] = ans[i];
        }
    }
};
