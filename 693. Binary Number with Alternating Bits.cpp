/**
Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Binary Number with Alternating Bits.
//Memory Usage: 9.5 MB, less than 7.32% of C++ online submissions for Binary Number with Alternating Bits.

/**
Approach #1: Convert to String [Accepted]
Intuition and Algorithm

Let's convert the given number into a string of binary digits. 
Then, we should simply check that no two adjacent digits are the same.
**/

/**
Complexity Analysis

Time Complexity: O(1). 
For arbitrary inputs, we do O(w) work, where w is the number of bits in n. 
However, w≤32.

Space complexity: O(1), or alternatively O(w).
**/

class Solution {
public:
    bool hasAlternatingBits(int n) {
        int l = ceil(log2(n));
        bitset<40> b(n);
        int last = b[0];
        for(int i = 1; i < l; i++){
            if(b[i]==last){
                return false;
            }else{
                last = b[i];
            }
        }
        return true;
    }
};

/**
Approach #2: Divide By Two [Accepted]
Intuition and Algorithm

We can get the last bit and the rest of the bits via n % 2 and n // 2 operations. 
Let's remember cur, the last bit of n. 
If the last bit ever equals the last bit of the remaining, 
then two adjacent bits have the same value, and the answer is False. 
Otherwise, the answer is True.

Also note that instead of n % 2 and n // 2, we could have used operators n & 1 and n >>= 1 instead.
**/

/**
Complexity Analysis

Time Complexity: O(1). 
For arbitrary inputs, we do O(w) work, where w is the number of bits in n. 
However, w≤32.

Space complexity: O(1).
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Binary Number with Alternating Bits.
//Memory Usage: 9.3 MB, less than 15.85% of C++ online submissions for Binary Number with Alternating Bits.

/**
class Solution {
public:
    bool hasAlternatingBits(int n) {
        int cur = n%2;
        n/=2;
        while(n > 0){
            if(cur==n%2) return false;
            cur = n%2;
            n/=2;
        }
        return true;
    }
};
**/
