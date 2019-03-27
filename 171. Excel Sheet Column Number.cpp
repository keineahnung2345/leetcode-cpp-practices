/**
Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...
Example 1:

Input: "A"
Output: 1
Example 2:

Input: "AB"
Output: 28
Example 3:

Input: "ZY"
Output: 701
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Excel Sheet Column Number.
//Memory Usage: 8.1 MB, less than 53.74% of C++ online submissions for Excel Sheet Column Number.

class Solution {
public:
    int titleToNumber(string s) {
        int ans = 0;
        for(string::reverse_iterator r = s.rbegin(); r!=s.rend(); r++){
            ans += (*r - 'A' + 1) * pow(26, (r - s.rbegin()));
        }
        return ans;
    }
};
