//bit manipulation
//Runtime: 16 ms, faster than 23.66% of C++ online submissions for Single Number II.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Single Number II.
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        
        for(int i = 31; i >= 0; i--){
            int mask = 1 << i;
            int set = 0;
            
            for(int num : nums){
                if(num & mask){
                    set++;
                }
            }
            
            if(set%3 == 1){
                ans += mask;
            }
        }
        
        return ans;
    }
};
