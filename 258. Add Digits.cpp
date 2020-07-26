//Congruence formula
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Add Digits.
//Memory Usage: 5.8 MB, less than 97.98% of C++ online submissions for Add Digits.
class Solution {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        if(num % 9 == 0) return 9;
        return num % 9;
    }
};
