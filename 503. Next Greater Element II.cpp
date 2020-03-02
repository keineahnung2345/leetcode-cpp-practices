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

//Approach #3 Using Stack
//time: O(n), space: O(n)
//Runtime: 88 ms, faster than 78.59% of C++ online submissions for Next Greater Element II.
//Memory Usage: 11.9 MB, less than 100.00% of C++ online submissions for Next Greater Element II.
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int N = nums.size();
        vector<int> ans(N);
        stack<int> stk;
        for(int i = 2*N-1; i >= 0; i--){
            while(!stk.empty() && nums[stk.top()] <= nums[i%N]){
                stk.pop();
            }
            ans[i%N] = stk.empty() ? -1 : nums[stk.top()];
            stk.push(i%N);
        }
        return ans;
    }
};
