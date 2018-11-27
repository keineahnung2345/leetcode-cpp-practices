/**
Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.

 

Example 1:

Input: "Hello"
Output: "hello"
Example 2:

Input: "here"
Output: "here"
Example 3:

Input: "LOVELY"
Output: "lovely"
**/

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    string toLowerCase(string str) {
        for(int i = 0; i < str.size(); i++){
            if(str[i]>='A' && str[i]<='Z'){
                str.replace(i,1,1,str[i]+'a'-'A'); //str.replace(int pos, int len, int n, char c)
                // str.replace(i, 1, string(1, (char)(str[i]+'a'-'A'))); //str.replace(int pos, int len, string str)
            }
        }
        return str;
    }
};
