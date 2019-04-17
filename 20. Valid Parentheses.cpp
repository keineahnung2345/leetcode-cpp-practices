//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Valid Parentheses.
//Memory Usage: 8.5 MB, less than 99.87% of C++ online submissions for Valid Parentheses.
//time complexity: O(n), space complexity: O(n)

class Solution {
public:
    bool isValid(string s) {
        map<char, char> paren;
        paren['('] = ')';
        paren['{'] = '}';
        paren['['] = ']';
        
        set<char> keys = {'(', '{', '['};
        
        stack<char> stk;
        
        for(char c : s){
            if(keys.find(c) != keys.end()){//left
                stk.push(c);
            }else if(!stk.empty() && paren[stk.top()] == c){//right, match
                stk.pop();
            }else{//right, not match
                return false;
            }
        }
        
        return stk.empty();
    }
};
