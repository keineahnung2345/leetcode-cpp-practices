//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number Complement.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Number Complement.
class Solution {
public:
    int findComplement(int num) {
        if(num == 1) return 0;
        int p = floor(log2(num)) + 1;
        
        return (long)(1 << p) -1 - num;
    }
};
