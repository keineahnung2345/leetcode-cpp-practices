//TLE
//38 / 47 test cases passed.
class Solution {
public:
    int count_set_bit(int x){
        int bits = 0;
        while(x != 0){
            bits += x&1;
            x >>= 1;
        }
        return bits;
    }
    
    int totalHammingDistance(vector<int>& nums) {
        int N = nums.size();
        
        int ans = 0;
        
        for(int i = 0; i < N-1; i++){
            for(int j = i+1; j < N; j++){
                int xorResult = nums[i]^nums[j];
                ans += count_set_bit(xorResult);
            }
        }
        
        return ans;
    }
};
