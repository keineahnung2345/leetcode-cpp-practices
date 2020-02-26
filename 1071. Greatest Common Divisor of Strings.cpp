//Runtime: 4 ms, faster than 91.98% of C++ online submissions for Greatest Common Divisor of Strings.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Greatest Common Divisor of Strings.

class Solution {
public:
    int greatestCommonDivisor(int x, int y){
        if(x < y){
            int tmp = x;
            x = y;
            y = tmp;
        }
        
        while(y != 0){
            int org_y = y;
            y = x % y;
            x = org_y;
        }
        
        return x;
    }
    string gcdOfStrings(string str1, string str2) {
        int l1 = str1.size(), l2 = str2.size();
        int gcd = greatestCommonDivisor(l1, l2);
        string sgcd = str1.substr(0, gcd);
        // cout << sgcd << endl;
            
        // cout << "str1" << endl;
        for(int i = 0; i < l1/gcd; i++){
            // cout << i*gcd << endl;
            if(str1.substr(i*gcd, gcd) != sgcd)
                return "";
        }
          
        // cout << "str2" << endl;
        for(int i = 0; i < l2/gcd; i++){
            // cout << i*gcd << endl;
            if(str2.substr(i*gcd, gcd) != sgcd)
                return "";
        }
        
        return sgcd;
    }
};

//https://leetcode.com/problems/greatest-common-divisor-of-strings/discuss/303781/JavaPython-3-3-codes-each%3A-Recursive-iterative-and-regex-w-brief-comments-and-analysis.
//Method 3: Regular Expression
//Runtime: 16 ms, faster than 14.18% of C++ online submissions for Greatest Common Divisor of Strings.
//Memory Usage: 13.8 MB, less than 100.00% of C++ online submissions for Greatest Common Divisor of Strings.

class Solution {
public:
    int greastestCommonDivisor(int x, int y){
        return y == 0 ? x : greastestCommonDivisor(y, x%y);
    }
    
    string gcdOfStrings(string str1, string str2) {
        int l1 = str1.size(), l2 = str2.size();
        int gcd = greastestCommonDivisor(l1, l2);
        string sgcd = str1.substr(0, gcd);
        // regex pattern = regex("(" + sgcd + ")+");
        regex pattern(("(" + sgcd + ")+"));
        return  regex_match(str1, pattern) && regex_match(str2, pattern) ? sgcd: "";
    }
};
