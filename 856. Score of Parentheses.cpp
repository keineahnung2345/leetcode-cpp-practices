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

//Approach 1: Divide and Conquer
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Score of Parentheses.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Score of Parentheses.
//time: O(N^2), space: O(N)
class Solution {
public:
    int F(string S, int start, int end){
        //end is exclusive
        int ans = 0, balance = 0;
        
        for(int i = start; i < end; i++){
            balance += (S[i] == '(') ? 1 : -1;
            if(balance == 0){
                if(i - start == 1){
                    //')' 's mathcing '(' is its previous char
                    ans++;
                }else{
                    //')' matches to the '(' far before
                    ans += 2 * F(S, start+1, i);
                }
                //the start position of new '('
                start = i+1;
            }
        }
        
        return ans;
    };
    
    int scoreOfParentheses(string S) {
        return F(S, 0, S.size());
    }
};
