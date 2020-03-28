//TLE
//42 / 58 test cases passed.
class Solution {
public:
    bool ans;
    
    bool valid(string s){
        int balance = 0;
        for(char c : s){
            switch(c){
                case '(':
                    balance++;
                    break;
                case ')':
                    balance--;
            }
            //in any prefix, we cannot have more ) than (
            if(balance < 0) break;
        }
        return balance == 0;
    };
    
    void solve(string s, int i){
        if(i == s.size()){
            ans |= valid(s);
        }else if(s[i] == '*'){
            //interpret '*' as '(' or ')'
            for(char c : "()"){
                s[i] = c;
                solve(s, i+1);
                if(ans) return;
            }
        }else{
            solve(s, i+1);
        }
    };
    
    bool checkValidString(string s) {
        ans = false;
        solve(s, 0);
        return ans;
    }
};
