//backtracking
//126 / 126 test cases passed, but took too long.
class Solution {
public:
    bool valid(const string& expr){
        stack<char> stk;
        //open count - close count
        int balance = 0;
        
        for(char c : expr){
            if(c == '('){
                stk.push(c);
                ++balance;
            }else if(c == ')'){
                if(balance <= 0){
                    //invalid when current close >= open
                    return false;
                }
                
                if(!stk.empty() && stk.top() == '('){
					stk.pop();
                }else{
                    stk.push(c);
                }
                --balance;
            }else{
                //skip char that's not parenthesis
            }
        }
        
        return stk.empty();
    };
    
    void backtrack(string& s, string& expr, set<string>& exprs, int& minRem, int start, int open, int close, int rem){
        if(start == s.size()){
            if(valid(expr)){
                //update minRem and exprs
                if(rem < minRem){
                    exprs.clear();
                    minRem = rem;
                }
                
                if(rem == minRem){
                    exprs.insert(expr);
                }
            }
        }else if(s[start] != '(' && s[start] != ')'){
            //for char which is not a parenthesis, directly add it
            expr += s[start];
            backtrack(s, expr, exprs, minRem, start+1, open, close, rem);
            expr.pop_back();
        }else{
            /*
            for s[start] == ')', we should do the pruning here,
            not at the first layer!
            o.w. it will fail ")("
            */
            if(s[start] == '(' || 
               (s[start] == ')' && (close < open))){
                //keep s[start]
                expr += s[start];
                backtrack(s, expr, exprs, minRem, start+1, open+(s[start] == '('), close+(s[start]==')'), rem);
                expr.pop_back();
            }
            
            //remove s[start]
            backtrack(s, expr, exprs, minRem, start+1, open, close, rem+1);
        }
    };
    
    vector<string> removeInvalidParentheses(string s) {
        string expr = "";
        set<string> exprs;
        int minRem = INT_MAX;
        backtrack(s, expr, exprs, minRem, 0, 0, 0, 0);
        return vector<string>(exprs.begin(), exprs.end());
    }
};

//Approach 1: Backtracking
//to check if expr is valid, we only need to check if "open == close"!
//Runtime: 144 ms, faster than 39.89% of C++ online submissions for Remove Invalid Parentheses.
//Memory Usage: 7.8 MB, less than 82.24% of C++ online submissions for Remove Invalid Parentheses.
class Solution {
public:
    void backtrack(string& s, string& expr, set<string>& exprs, int& minRem, int start, int open, int close, int rem){
        if(start == s.size()){
	    // if(valid(expr)){
            if(open == close){
                //update minRem and exprs
                if(rem < minRem){
                    exprs.clear();
                    minRem = rem;
                }
                
                if(rem == minRem){
                    exprs.insert(expr);
                }
            }
        }else if(s[start] != '(' && s[start] != ')'){
            //for char which is not a parenthesis, directly add it
            expr += s[start];
            backtrack(s, expr, exprs, minRem, start+1, open, close, rem);
            expr.pop_back();
        }else{
            /*
            for s[start] == ')', we should do the pruning here,
            not at the first layer!
            o.w. it will fail ")("
            */
            if(s[start] == '(' || 
               (s[start] == ')' && (close < open))){
                //keep s[start]
                expr += s[start];
                backtrack(s, expr, exprs, minRem, start+1, open+(s[start] == '('), close+(s[start]==')'), rem);
                expr.pop_back();
            }
            
            //remove s[start]
            backtrack(s, expr, exprs, minRem, start+1, open, close, rem+1);
        }
    };
    
    vector<string> removeInvalidParentheses(string s) {
        string expr = "";
        set<string> exprs;
        int minRem = INT_MAX;
        backtrack(s, expr, exprs, minRem, 0, 0, 0, 0);
        return vector<string>(exprs.begin(), exprs.end());
    }
};
