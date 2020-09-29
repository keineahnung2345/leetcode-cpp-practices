//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Sequential Digits.
//Memory Usage: 6.6 MB, less than 5.19% of C++ online submissions for Sequential Digits.
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        int len_low = log10(low)+1;
        int len_high = log10(high)+1;
        
        vector<int> ans;
        
        for(int len = len_low; len <= len_high; ++len){
            int head_start = (len == len_low) ? low/pow(10, len_low-1) : 1;
            
            int cur = 0;
            for(int head = head_start; head + len - 1 <= 9; ++head){
                cur = 0;
                for(int i = 0; i < len; ++i){
                    cur += pow(10, len-1-i) * (head+i);
                }
                if(cur >= low && cur <= high) ans.push_back(cur);
            }
        }
        
        return ans;
    }
};
