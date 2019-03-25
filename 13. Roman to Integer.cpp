/**
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
**/

//Runtime: 80 ms, faster than 8.14% of C++ online submissions for Roman to Integer.
//Memory Usage: 36.6 MB, less than 5.10% of C++ online submissions for Roman to Integer.
class Solution {
public:
    map<string, int> twoMap;
    map<char, int> oneMap;
    
    bool look2(string s, int& ans, int& i){
        if(twoMap.find(s)!=twoMap.end()){
            ans += twoMap[s];
            i += 2;
            return true;
        }
        return false;
    }
    
    bool look1(char c, int& ans, int& i){
        if(oneMap.find(c)!=oneMap.end()){
            ans += oneMap[c];
            i += 1;
            return true;
        }
        return false;
    }
    
    int romanToInt(string s) {
        int ans = 0;
        int i = 0;

        twoMap["IV"] = 4;
        twoMap["IX"] = 9;
        twoMap["XL"] = 40;
        twoMap["XC"] = 90;
        twoMap["CD"] = 400;
        twoMap["CM"] = 900;

        oneMap['I'] = 1;
        oneMap['V'] = 5;
        oneMap['X'] = 10;
        oneMap['L'] = 50;
        oneMap['C'] = 100;
        oneMap['D'] = 500;
        oneMap['M'] = 1000;
        
        while(i < s.size()){
            if(i+1 < s.size()){
                string subs = s.substr(i, 2);
                bool b = look2(subs, ans, i);
                if(!b){
                    look1(s[i], ans, i);
                }
            }else{
                look1(s[i], ans, i);
            }
        }
        return ans;
    }
};

