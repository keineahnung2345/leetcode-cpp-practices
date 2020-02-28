//Runtime: 4 ms, faster than 67.62% of C++ online submissions for Plus One.
//Memory Usage: 7.6 MB, less than 100.00% of C++ online submissions for Plus One.
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int N = digits.size();
        int pos = N -1;
        while(pos >= 0 && digits[pos] == 9){
            //carry
            digits[pos] = 0;
            pos--;
        }
        
        if(pos < 0){
            digits.insert(digits.begin(), 1);
        }else{
            digits[pos]++;
        }
        
        return digits;
    }
};
