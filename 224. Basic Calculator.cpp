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
