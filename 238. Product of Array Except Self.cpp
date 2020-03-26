//WA
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int product = accumulate(nums.begin(), nums.end(), 1, multiplies<int>());
        int N = nums.size();
        vector<int> output(N, 0);
        
        for(int i = 0; i < N; i++){
            output[i] = product/nums[i];
        }
        
        return output;
    }
};

//Approach 1: Left and Right product lists
//Runtime: 44 ms, faster than 31.25% of C++ online submissions for Product of Array Except Self.
//Memory Usage: 10.7 MB, less than 100.00% of C++ online submissions for Product of Array Except Self.
//time: O(N), space: O(N)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = nums.size();
        vector<int> L(N, 1), R(N, 1), output(N, 1);
        
        for(int i = 1; i < N; i++){
            L[i] = L[i-1] * nums[i-1];
        }
        
        for(int i = N-2; i >= 0; i--){
            R[i] = R[i+1] * nums[i+1];
        }
        
        for(int i = 0; i < N; i++){
            output[i] = L[i] * R[i];
        }
        
        return output;
    }
};
