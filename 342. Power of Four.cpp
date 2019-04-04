//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Power of Four.
//Memory Usage: 7.9 MB, less than 99.30% of C++ online submissions for Power of Four.

class Solution {
public:
    bool isPowerOfFour(int num) {
        if(num <= 0) return false;
        //https://stackoverflow.com/questions/29388711/c-how-to-get-length-of-bits-of-a-variable
        return !(num & (num-1)) && (int(log2(num))%2 == 0);
    }
};

//https://leetcode.com/problems/power-of-four/discuss/80457/Java-1-line-(cheating-for-the-purpose-of-not-using-loops)
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Power of Four.
//Memory Usage: 7.9 MB, less than 99.30% of C++ online submissions for Power of Four.

class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && (num & (num-1)) == 0 && (num & 0x55555555)!=0;
    }
};
