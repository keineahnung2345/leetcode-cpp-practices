//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Score of Parentheses.
//Memory Usage: 6 MB, less than 100.00% of C++ online submissions for Score of Parentheses. 
class Solution {
public:
    int scoreOfParentheses(string S) {
        stack<int> stk;
        for(char c : S){
            // cout << c << " " << stk.size() << endl;
            switch(c){
                case '(':
                    //use -1 to represent '('
                    stk.push(-1);
                    break;
                case ')':
                    //stk.size() must > 0
                    if(stk.top() == -1){
                        stk.pop();
                        stk.push(1);
                    }else{
                        int tmp = 0;
                        while(stk.top() != -1){
                            tmp += stk.top(); stk.pop();
                        }
                        stk.pop(); //'('
                        stk.push(tmp * 2);
                    }
                    break;
            }
        }
        
        int ans = 0;
        while(!stk.empty()){
            ans += stk.top(); stk.pop();
        }
        return ans;
    }
};
