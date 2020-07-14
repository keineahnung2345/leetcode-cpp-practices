//Brute force
//TLE
//217 / 230 test cases passed.
class Solution {
public:
    bool isValid(string s){
        stack<char> stk;
        
        for(char c : s){
            if(c == '('){
                stk.push(c);
            }else{
                if(!stk.empty() && stk.top() == '('){
                    stk.pop();
                }else{
                    return false;
                }
            }
        }
        
        return stk.empty();
    };
    
    int longestValidParentheses(string s) {
        int maxLen = 0;
        
        for(int i = 0; i < s.size(); ++i){
            for(int j = 2; i+j-1 < s.size(); ++j){
                if(isValid(s.substr(i, j))){
                    maxLen = max(maxLen, j);
                }
            }
        }
        
        return maxLen;
    }
};
