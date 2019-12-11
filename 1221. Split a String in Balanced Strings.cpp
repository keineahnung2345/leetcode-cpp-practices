//Runtime: 4 ms, faster than 58.89% of C++ online submissions for Split a String in Balanced Strings.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Split a String in Balanced Strings.

class Solution {
public:
    int balancedStringSplit(string s) {
        int rcount = 0, lcount = 0;
        int sbcount = 0;
        for(char c : s){
            if(c == 'R'){
                rcount++;
            }else{
                lcount++;
            }
            if(rcount == lcount){
                sbcount++;
            }
        }
        return sbcount;
    }
};
