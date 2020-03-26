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
