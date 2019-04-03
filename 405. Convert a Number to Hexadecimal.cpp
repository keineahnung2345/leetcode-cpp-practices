//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Convert a Number to Hexadecimal.
//Memory Usage: 8.1 MB, less than 100.00% of C++ online submissions for Convert a Number to Hexadecimal.

class Solution {
public:
    string toHex(int num) {
        if(num == 0) return "0";
        
        string ans;
        vector digits = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        
        unsigned int unum;
        
        if(num < 0) unum = UINT_MAX + 1 + (unsigned int)num;
        else unum = num;
        
        while(unum > 0){
            ans = digits[unum%16] + ans;
            unum/=16;
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/convert-a-number-to-hexadecimal/discuss/89253/Simple-Java-solution-with-comment
//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Convert a Number to Hexadecimal.
//Memory Usage: 8 MB, less than 100.00% of C++ online submissions for Convert a Number to Hexadecimal.

/**
class Solution {
public:
    string toHex(int num) {
        vector<char> d = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        string ans = "";
        unsigned int unum = num;
        
        while(unum != 0){
            ans = d[unum & 15] + ans;
            unum >>= 4;
        }
        return ans.empty() ? "0" : ans;
    }
};
**/
