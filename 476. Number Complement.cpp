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

//https://leetcode.com/problems/number-complement/discuss/96017/3-line-C%2B%2B
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number Complement.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Number Complement./
class Solution {
public:
    int findComplement(int num) {
        /*
        suppose num is 5, which is 0....0101,
        we know that the first '1' of binary representation of 5 appears at 2nd digit
        we want to generate a mask s.t. 
        0...0111, (31-3rd digit is 0, and 2nd,1st,0th digit is 1)
        and then just do xor to get the complement
        */
        //1...1(32 bits)
        unsigned int mask = ~0;
        //we want mask and num's intersection be 0
        while(mask & num){
            mask <<= 1;
        }
        //now we use ~mask
        return ~mask ^ num;
    }
};
