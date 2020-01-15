/*
Runtime: 4 ms, faster than 98.29% of C++ online submissions for Find Numbers with Even Number of Digits.
Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Find Numbers with Even Number of Digits.
*/
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int digit = 0, ans = 0;
        
        for(int num : nums){
            digit = 0;
            
            while(num){
                num /= 10;
                digit++;
            }
            
            if(digit % 2 == 0){
                ans++;
            }
        }
        
        return ans;
    }
};
