//Runtime: 4 ms, faster than 37.98% of C++ online submissions for Power of Two.
//Memory Usage: 6.1 MB, less than 16.52% of C++ online submissions for Power of Two.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n == 0) return false;
        while(n % 2 == 0){
            n /= 2;
        }
        return n == 1;
    }
};

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Power of Two.
//Memory Usage: 7.9 MB, less than 97.02% of C++ online submissions for Power of Two.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        //negative number has a factor -1, 
        //so it's not a power of two
        if(n <= 0) return false;
        while(n > 0){
            //if there is a 1-bit in n,
            //then it should be the first bit
            //ex: 16 = 1000, 1 = 1, 17 = 1001
            if(n & 1 == 1 && n != 1) return false;
            n >>= 1;
        }
        return true;
    }
};

//https://leetcode.com/problems/power-of-two/discuss/63974/Using-nand(n-1)-trick
//Runtime: 8 ms, faster than 44.60% of C++ online submissions for Power of Two.
//Memory Usage: 7.9 MB, less than 98.72% of C++ online submissions for Power of Two.
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0) return false;
        //the power of 2 only has one bit-1,
        // n&(n-1) will make the last bit-1 be zero,
        // and if n&(n-1) is 0, 
        // it means n has only one bit-1, 
        // so it should be a power of 2
        return !(n&(n-1));
    }
};
