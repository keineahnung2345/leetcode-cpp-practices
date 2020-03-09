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

//Stack
//https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/discuss/419402/JavaC%2B%2B-Stack
//Runtime: 64 ms, faster than 9.24% of C++ online submissions for Minimum Remove to Make Valid Parentheses.
//Memory Usage: 12.6 MB, less than 100.00% of C++ online submissions for Minimum Remove to Make Valid Parentheses.
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> stk;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                //convert to 1-based so that we can use '-' as mark for 
                stk.push(i+1);
            }else if(s[i] == ')'){
                //stk's top is '('
                if(stk.size() > 0 && stk.top() > 0) stk.pop();
                else stk.push(-(i+1));
            }
        }
        
        //now stk contains redundant char's indices
        while(!stk.empty()){
            int i = stk.top(); stk.pop();
            s.erase(abs(i)-1, 1);
        }
        
        return s;
    }
};
