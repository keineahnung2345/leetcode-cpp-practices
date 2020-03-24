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

//iterate from MSB
//https://leetcode.com/problems/total-hamming-distance/discuss/96226/Java-O(n)-time-O(1)-Space
//Runtime: 88 ms, faster than 10.31% of C++ online submissions for Total Hamming Distance.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Total Hamming Distance.
//time: O(N), space: O(1)
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int N = nums.size();
        
        int ans = 0;
        
        for(int i = 31; i >= 0; i--){
            int mask = 1 << i;
            int set = 0, noset = 0;
            for(int num : nums){
                if(num & mask){
                    set++;
                }else{
                    noset++;
                }
            }
            ans += set*noset;
        }
        
        return ans;
    }
};
