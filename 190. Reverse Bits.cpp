//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Reverse Bits.
//Memory Usage: 7.9 MB, less than 85.71% of C++ online submissions for Reverse Bits.

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // cout << numeric_limits<uint32_t>::max() << endl;
        // // return numeric_limits<uint32_t>::max() - n;
        // return numeric_limits<uint32_t>::max();
        uint32_t x = 0;
        int d = 0;
        while(n > 0){
            // cout << d << " " << n << endl;
            x += (n%2) << (31 - d);
            n >>= 1;
            d++;
        }
        return x;
    }
};
