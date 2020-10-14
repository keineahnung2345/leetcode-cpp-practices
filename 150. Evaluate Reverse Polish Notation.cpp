//Runtime: 16 ms, faster than 95.61% of C++ online submissions for Evaluate Reverse Polish Notation.
//Memory Usage: 12.2 MB, less than 13.10% of C++ online submissions for Evaluate Reverse Polish Notation.
class Solution {
public:
    bool is_number(const std::string& s){
        if(s.empty()) return false;
        if(s.size() > 1 && s[0] == '-' && s.find_first_not_of("0123456789", 1) == std::string::npos) return true;
        return s.find_first_not_of("0123456789") == std::string::npos;
    };
    
    int evalRPN(vector<string>& tokens) {
        stack<int> oprs;
        
        for(const string& token : tokens){
            if(is_number(token)){
                oprs.push(stoi(token));
            }else{
                int b = oprs.top(); oprs.pop();
                int a = oprs.top(); oprs.pop();
                
                int res;
                switch(token[0]){
                    case '+':
                        res = a+b;
                        break;
                    case '-':
                        res = a-b;
                        break;
                    case '*':
                        res = a*b;
                        break;
                    case '/':
                        res = a/b;
                        break;
                }
                
                oprs.push(res);
                
                // cout << a << token << b << " = " << res << endl;
            }
        }
        
        return oprs.top();
    }
};
