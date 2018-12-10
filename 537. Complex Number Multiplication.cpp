/**
Given two strings representing two complex numbers.

You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
Note:

The input strings will not have extra blank.
The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. And the output should be also in this form.
**/

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        int ar = stoi(a.substr(0, a.find("+")));
        int ai = stoi(a.substr(a.find("+")+1, a.size()));
        int br = stoi(b.substr(0, b.find("+")));
        int bi = stoi(b.substr(b.find("+")+1, b.size()));
        
        // cout << ar << " " << ai << " " << br << " " << bi << endl;
        
        int r = ar*br + ai*bi*-1;
        int i = ar*bi + ai*br;
        return to_string(r)+"+"+to_string(i)+"i";
    }
};

/**
Complexity Analysis

Time complexity : O(1). Here splitting takes constant time as length of the string is very small (<20).

Space complexity : O(1). Constant extra space is used.
**/
