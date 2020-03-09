//Runtime: 60 ms, faster than 11.39% of C++ online submissions for Minimum Remove to Make Valid Parentheses.
//Memory Usage: 11.1 MB, less than 100.00% of C++ online submissions for Minimum Remove to Make Valid Parentheses.
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int i = 0;
        int open = 0, close = 0;
        
        //delete redundant )
        while(i < s.size()){
            // cout << i << " " << open << " " << close << endl;
            if(s[i] == '('){
                open++;
            }else if(s[i] == ')'){
                close++;
                if(close > open){
                    //if we don't add 2nd argument, it will delete to the end!
                    s.erase(i, 1);
                    close--;
                    i--;
                }
            }
            i++;
        }
        // cout << s << endl;
        
        //delete redundant (
        i = s.size()-1;
        open = 0;
        close = 0;
        while(i >= 0){
            // cout << i << " " << open << " " << close << endl;
            if(s[i] == '('){
                open++;
                if(open > close){
                    s.erase(i, 1);
                    open--;
                    //if traverse in reverse order, don't need this!
                    // i++;
                }
            }else if(s[i] == ')'){
                close++;
            }
            i--;
        }
        
        return s;
    }
};
