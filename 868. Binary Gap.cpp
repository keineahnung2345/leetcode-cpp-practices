/**
Given a positive integer N, find and return the longest distance between two consecutive 1's in the binary representation of N.
If there aren't two consecutive 1's, return 0.

Example 1:

Input: 22
Output: 2
Explanation: 
22 in binary is 0b10110.
In the binary representation of 22, there are three ones, and two consecutive pairs of 1's.
The first consecutive pair of 1's have distance 2.
The second consecutive pair of 1's have distance 1.
The answer is the largest of these two distances, which is 2.
Example 2:

Input: 5
Output: 2
Explanation: 
5 in binary is 0b101.
Example 3:

Input: 6
Output: 1
Explanation: 
6 in binary is 0b110.
Example 4:

Input: 8
Output: 0
Explanation: 
8 in binary is 0b1000.
There aren't any consecutive pairs of 1's in the binary representation of 8, so we return 0.
**/

/**
Complexity Analysis

Time Complexity: O(logN). Note that logN is the number of digits in the binary representation of N.

Space Complexity: O(logN), the space used by A. 
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Binary Gap.
//Memory Usage: 9.8 MB, less than 11.29% of C++ online submissions for Binary Gap.
class Solution {
public:
    int binaryGap(int N) {
        vector<int> onePos;
        int digit = 0;
        int ans = 0;
        
        while(N!=0){
            if(N%2==1){
                onePos.push_back(digit);
            }
            N >>= 1; 
            digit++;
        }
        
        if(onePos.size()<2){
            return 0;
        }
        
        for(int i = 1; i < onePos.size(); i++){
            ans = max(onePos[i] - onePos[i-1], ans);
        }
        
        return ans;
    }
};

/**
Approach 2: One Pass
Intuition

In Approach 1, we created an array A of indices i for which N had the ith bit set.

Since we only care about consecutive values of this array A, we don't need to store the whole array. We only need to remember the last value seen.

Algorithm

We'll store last, the last value added to the virtual array A. If N has the ith bit set, a candidate answer is i - last, and then the new last value added to A would be last = i.
**/

/**
Complexity Analysis

Time Complexity: O(logN). Note that logN is the number of digits in the binary representation of N.

Space Complexity: O(1). 
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Binary Gap.
//Memory Usage: 9.7 MB, less than 48.39% of C++ online submissions for Binary Gap.

/**
class Solution {
public:
    int binaryGap(int N) {
        int digit = 0;
        int ans = 0;
        int last = -1;
        
        while(N!=0){
            if(N%2==1){
                if(last>=0){
                    ans = max(digit - last, ans);
                }
                last = digit;
            }
            N >>= 1; 
            digit++;
        }
        
        return ans;
    }
};
**/


