//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Number of 1 Bits.
//Memory Usage: 8.1 MB, less than 53.17% of C++ online submissions for Number of 1 Bits.

/**
Approach #1 (Loop and Flip) [Accepted]
**/

/**
Complexity Analysis

The run time depends on the number of bits in nn. Because nn in this piece of code is a 32-bit integer, the time complexity is O(1)O(1).

The space complexity is O(1)O(1), since no additional space is allocated.
**/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        while(n > 0){
            if(n&1 == 1){
                ans++;
                // cout << ans << endl;
            }
            n >>= 1;
        }
        return ans;
    }
};

/**
Approach #2 (Bit Manipulation Trick) [Accepted]
**/

/**
Complexity Analysis

The run time depends on the number of 11-bits in nn. In the worst case, all bits in nn are 11-bits. In case of a 32-bit integer, the run time is O(1)O(1).

The space complexity is O(1)O(1), since no additional space is allocated.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Number of 1 Bits.
//Memory Usage: 8.1 MB, less than 67.61% of C++ online submissions for Number of 1 Bits.

/**
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        //the loop will be executed for k times if n has k 1-bit
        while(n > 0){
            ans++;
            //convert the last significant bit of n to 0
            n &= (n-1);
        }
        return ans;
    }
};
**/
