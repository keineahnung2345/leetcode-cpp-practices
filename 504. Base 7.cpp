/**
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Base 7.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Base 7.

class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";
        
        bool neg = (num < 0);
        int digit = 0;
        int ans = 0;
        
        if(neg) num*=(-1);
        
        while(num > 0){
            // cout << (num%7) * pow(10, digit) << " ";
            ans += (num%7) * pow(10, digit);
            num/=7;
            digit++;
        }
        // cout << endl;
        
        if(neg) return "-" + to_string(ans);
        return to_string(ans);
    }
};
