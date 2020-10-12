//stack
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Maximum Nesting Depth of the Parentheses.
//Memory Usage: 6.4 MB, less than 50.00% of C++ online submissions for Maximum Nesting Depth of the Parentheses.
class Solution {
public:
    int maxDepth(string s) {
        stack<char> stk;
        int ans = 0;
        
        for(char c : s){
            if(c == '('){
                stk.push('(');
                ans = max(ans, (int)stk.size());
            }else if(c == ')'){
                if(!stk.empty() && stk.top() == '('){
                    stk.pop();
                }else{
                    return -1;
                }
            }
        }
        
        return ans;
    }
};

//not using stack
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Maximum Nesting Depth of the Parentheses.
//Memory Usage: 6.4 MB, less than 50.00% of C++ online submissions for Maximum Nesting Depth of the Parentheses.
class Solution {
public:
    int maxDepth(string s) {
        int unmatched = 0;
        int ans = 0;
        
        for(char c : s){
            if(c == '('){
                ++unmatched;
                ans = max(ans, unmatched);
            }else if(c == ')'){
                if(unmatched > 0){
                    --unmatched;
                }else{
                    return -1;
                }
            }
        }
        
        return ans;
    }
};
