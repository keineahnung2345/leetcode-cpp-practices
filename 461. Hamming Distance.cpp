/**
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

Note:
0 ≤ x, y < 231.

Example:

Input: x = 1, y = 4

Output: 2

Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑

The above arrows point to positions where the corresponding bits are different.
**/

//Your runtime beats 49.92 % of cpp submissions.

class Solution {
public:
    int hammingDistance(int x, int y) {
        int xXORy = x^y;
        int distance = 0;
        while(xXORy){
            distance+=xXORy%2;
            xXORy/=2;
        }
        return distance;
    }
};

//bit manipulation
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Hamming Distance.
//Memory Usage: 5.9 MB, less than 84.29% of C++ online submissions for Hamming Distance.
class Solution {
public:
    int hammingDistance(int x, int y) {
        int diff = x^y;
        
        int ans = 0;
        
        while(diff){
            ans += (diff&1);
            diff >>= 1;
        }
        
        return ans;
    }
};
