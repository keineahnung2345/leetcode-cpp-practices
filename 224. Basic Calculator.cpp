//WA
class Solution {
public:
    void print_stack(stack<char>& stk){
        if(stk.empty()) return;
        char* end   = &stk.top() + 1;
        char* begin = end - stk.size();
        vector<char> stack_contents(begin, end);

        cout << "stack: " << endl;
        for(char e : stack_contents){
            cout << e << " ";
        }
        cout << endl;
    };
    
    int calculate(string s) {
        stack<char> oprs;
        stack<int> opds;
        
        char opr;
        int opd = 0;
        
        for(char c : s){
            if(c == ' ') continue;
            if(c >= '0' && c <= '9'){
                opd = opd*10 + (c-'0');
                // cout << "opd: " << opd << endl;
            }else if(c == '('){
                // cout << "push " << c << endl;
                oprs.push(c);
            }else if(c == ')'){
                //evaluate the expression starts from last '('
                bool popped = false;
                while(!oprs.empty() && oprs.top() != ')'){
                    int last_opd = opds.top(); opds.pop();
                    char last_opr = oprs.top(); oprs.pop();
                    // cout << "last: " << last_opd << " " << last_opr << endl;
                    if(last_opr == '+'){
                        opd = last_opd + opd;
                    }else{
                        opd = last_opd - opd;
                    }
                    // print_stack(oprs);
                    if(!oprs.empty() && oprs.top() == '(' ){
                        if(!popped){
                            oprs.pop();
                            popped = true;
                        }else{
                            break;
                        }
                    }
                }
                
                // cout << "push " << opd << endl;
                opds.push(opd);
                opd = 0;
            }else{
                //c == '+' or '-'
                if(opds.empty()){
                    //when we looked through "1+"
                    // cout << "push " << opd << " and " << c << endl;
                    opds.push(opd);
                    opd = 0;
                    oprs.push(c);
                }else{
                    //when we looked through "1+2+"
                    //perform operation with last operand
                    // int last_opd = opds.top(); opds.pop();
                    // char last_opr = oprs.top(); oprs.pop();
                    // cout << "last: " << last_opd << " " << last_opr << endl;
                    // if(last_opr == '+'){
                    //     opd = last_opd + opd;
                    // }else{
                    //     opd = last_opd - opd;
                    // }
                    // print_stack(oprs);
                    
                    if(opd != 0){
                        if(oprs.empty() || oprs.top() == '(' || oprs.top() == ')'){
                            // cout << "push " << opd << endl;
                            opds.push(opd);
                            opd = 0;
                        }

                        while(!oprs.empty() && oprs.top() != '(' && oprs.top() != ')'){
                            int last_opd = opds.top(); opds.pop();
                            char last_opr = oprs.top(); oprs.pop();
                            // cout << "last: " << last_opd << " " << last_opr << endl;
                            if(last_opr == '+'){
                                opd = last_opd + opd;
                            }else{
                                opd = last_opd - opd;
                            }
                            // cout << "push " << opd << endl;
                            opds.push(opd);
                            opd = 0;
                            // print_stack(oprs);
                        }
                    }
                    
                    // cout << "push " << c << endl;
                    oprs.push(c);
                }
            }
        }
        
        int ans = 0;
        
        //when we looked through "1+2+3"
        if(!oprs.empty()){ 
            int last_opd = opds.top(); opds.pop();
            char last_opr = oprs.top(); oprs.pop();
            if(last_opr == '+'){
                ans = last_opd + opd;
            }else{
                ans = last_opd - opd;
            }
            // cout << "last: " << last_opd << " " << last_opr << ", ans: " << ans << endl;
        }else if(!opds.empty()){
            ans = opds.top(); opds.pop();
        }else if(opd != 0){
            ans = opd;
            opd = 0;
        }
        
        return ans;
    }
};

//Approach 1: Stack and String Reversal
//Runtime: 40 ms, faster than 46.67% of C++ online submissions for Basic Calculator.
//Memory Usage: 9.8 MB, less than 20.48% of C++ online submissions for Basic Calculator.
//time: O(N), space: O(N)
class Solution {
public:
    void print_stack(stack<char>& stk){
        if(stk.empty()) return;
        char* end   = &stk.top() + 1;
        char* begin = end - stk.size();
        vector<char> stack_contents(begin, end);

        cout << "oprs: " << endl;
        for(char e : stack_contents){
            cout << e << " ";
        }
        cout << endl;
    };
    
    void print_stack(stack<int>& stk){
        if(stk.empty()) return;
        int* end   = &stk.top() + 1;
        int* begin = end - stk.size();
        vector<int> stack_contents(begin, end);

        cout << "opds: " << endl;
        for(int e : stack_contents){
            cout << e << " ";
        }
        cout << endl;
    };
    
    int evaluateExpr(stack<int>& opds, stack<char>& oprs){
        int res = 0;
        
        //think about the case "(10)"
        if(!opds.empty()){
            res = opds.top(); opds.pop();
        }
        
        /*
        recall that we push chars into stack in reverse order,
        so here when we pop chars from stack,
        they are in positive order
        
        so ')' is the end of sub-expression
        */
        while(!opds.empty() && !oprs.empty() && oprs.top() != ')'){
            //pop one operator and one operand at a time
            char opr = oprs.top(); oprs.pop();
            
            if(opr == '+'){
                // cout << "+ " << opds.empty() << endl;
                res += opds.top(); opds.pop();
            }else{
                // cout << "- " << opds.empty() << endl;
                res -= opds.top(); opds.pop();
            }
        }
        
        return res;
    };
    
    int calculate(string s) {
        //cover the original expression with a set of parenthesis to avoid this extra call
        s = '(' + s + ')';
        reverse(s.begin(), s.end());
        
        int opd = 0, p = 0;
        stack<int> opds;
        stack<char> oprs;
        
        for(char c : s){
            if(c == ' '){
                continue;
            }else if(c >= '0' && c <= '9'){
                //c is a digit
                opd = (c-'0')*pow(10, p) + opd;
                ++p;
            }else{
                //meet +, -, or (), we first store the operand
                if(p != 0){
                    // cout << "push " << opd << endl;
                    opds.push(opd);
                    opd = 0;
                    p = 0;
                }
                
                if(c == '('){
                    //the end of reversed sub-expression
                    // print_stack(oprs);
                    // print_stack(opds);
                    int res = evaluateExpr(opds, oprs);
                    // cout << "( " << oprs.empty() << endl;
                    oprs.pop(); //pop ')', the end of sub-expression
                    opds.push(res);
                }else{
                    // cout << "push " << c << endl;
                    oprs.push(c);
                }
            }
        }
        
        return opds.top();
    }
};

//Approach 2: Stack and No String Reversal(sign)
//Runtime: 24 ms, faster than 76.53% of C++ online submissions for Basic Calculator.
//Memory Usage: 8.1 MB, less than 54.22% of C++ online submissions for Basic Calculator.
//time: O(N), space: O(N)
class Solution {
public:
    int calculate(string s) {
        stack<int> opds;
        stack<int> signs;
        
        int opd = 0;
        int res = 0;
        int sign = 1;
        
        for(char c : s){
            if(c >= '0' && c <= '9'){
                opd = opd * 10 + (c-'0');
            }else if(c == '+'){
                // cout << res << " + " << sign << " * " << opd << endl;
                res += sign * opd;
                opd = 0;
                sign = 1;
            }else if(c == '-'){
                // cout << res << " + " << sign << " * " << opd << endl;
                // res "+" sign * opd here !!!
                res += sign * opd;
                opd = 0;
                sign = -1;
            }else if(c == '('){
                /*
                current res and sign is later used when we meet ')'
                */
                opds.push(res);
                signs.push(sign);
                // cout << "push " << res << " and " << sign << endl;
                // cout << "opd: " << opd << endl;
                
                /*
                reset operand and result, 
                as if new evaluation begins for the new sub-expression
                */
                // opd = 0; //opd is already reset when we meet '+' or '-' before the '('
                res = 0; //since res is already pushed into stack
                sign = 1; //since sign is already pushed into stack
            }else if(c == ')'){
                // cout << res << " + " << sign << " * " << opd << endl;
                res += sign * opd;
                res *= signs.top(); signs.pop();
                res += opds.top(); opds.pop();
                // cout << "res: " << res << ", sign: " << sign << endl;
                opd = 0; //already used
                /*
                after ')', we must meet '+' or '-', 
                and sign*opd is always 0, so res won't change
                
                and we known that after '+' or '-', 
                opd and sign will be reset again,
                so here we don't need to reset sign
                */
                // sign = 1; 
            }
        }
        
        // cout << res << " + " << sign << " * " << opd << endl;
        return res + sign * opd;
    }
};

