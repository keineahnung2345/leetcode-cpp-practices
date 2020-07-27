//Congruence formula
/*
num = d0*1 + d1*10 + d2*100 + ... + dk*10^k
= d0*1 + d1*(1+9) + d2*(1+99) + ... dk*(1+9..9)
= d0 + d1 + ... dk + (d1*9 + d2*99 + dk*9..9)

num % 9 = (d0+...dk) % 9
*/
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Add Digits.
//Memory Usage: 5.8 MB, less than 97.98% of C++ online submissions for Add Digits.
//time: O(1), space: O(1)
class Solution {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        if(num % 9 == 0) return 9;
        return num % 9;
    }
};

//combine the last two cases
class Solution {
public:
    int addDigits(int num) {
        if(num == 0) return 0;
        return (num-1)%9+1;
    }
};
