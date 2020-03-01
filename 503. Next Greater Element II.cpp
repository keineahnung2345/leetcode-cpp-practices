//time: O(N^2), space: O(N)
//Runtime: 260 ms, faster than 8.26% of C++ online submissions for Next Greater Element II.
//Memory Usage: 11.1 MB, less than 100.00% of C++ online submissions for Next Greater Element II.

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();
        vector<int> ans(N, -1);
        
        for(int i = 0; i < N; i++){
            for(int j = i+1; j < i+N; j++){
                if(nums[j%N] > nums[i]){
                    ans[i] = nums[j%N];
                    break;
                }
            }
        }
        
        return ans;
    }
};
