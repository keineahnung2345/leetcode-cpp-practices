//Stack
/*
Hint 1: Use a stack to keep opening brackets. If you face single closing ')' add 1 to the answer and consider it as '))'.
Hint 2: If you have '))' with empty stack, add 1 to the answer, If after finishing you have x opening remaining in the stack, add 2x to the answer.
*/
//Runtime: 108 ms, faster than 100.00% of C++ online submissions for Minimum Insertions to Balance a Parentheses String.
//Memory Usage: 12.9 MB, less than 50.00% of C++ online submissions for Minimum Insertions to Balance a Parentheses String.
class Solution {
public:
    int minInsertions(string s) {
        stack<char> stk;
        
        int close = 0;
        int ans = 0;
        
        for(char c : s){
            if(c == ')'){
                ++close;
                if(close >= 2){
                    if(!stk.empty()){
                        stk.pop();
                    }else{
                        ++ans;
                    }
                    close -= 2;
                }
            }else{
                //c == '('
                if(close > 0){
                    if(!stk.empty() && stk.top() == '('){
                        ans += (2-close);
                        stk.pop();
                    }else{
                        //add '(' and 2-close ')'
                        ans += 1 + (2-close);
                    }
                    close = 0;
                }
                stk.push('(');
            }
            // cout << "open: " << stk.size() << ", close: " << close << ", ans: " << ans << endl;
        }
        
        while(close > 0 && !stk.empty()){
            if(close == 1){
                close = 0;
                //add a ')'
                ++ans;
            }else{
                close -= 2;
            }
            stk.pop();
            // cout << "open: " << stk.size() << ", close: " << close << ", ans: " << ans << endl;
        }
        
        if(stk.empty()){
            //make it even
            if(close&1){
                ++close;
                ++ans;
            }
            ans += close>>1;
        }else{
            /*
            if there are k unmatched '(' in stack,
            we will need k*2 ')'
            */
            ans += stk.size() * 2;
        }
        
        return ans;
    }
};

//One pass
//https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/discuss/780199/JavaC%2B%2BPython-Straight-Forward-One-Pass
//Runtime: 84 ms, faster than 100.00% of C++ online submissions for Minimum Insertions to Balance a Parentheses String.
//Memory Usage: 12.6 MB, less than 50.00% of C++ online submissions for Minimum Insertions to Balance a Parentheses String.
//time: O(N), space: O(1)
class Solution {
public:
    int minInsertions(string s) {
        int added = 0, right_to_add = 0;
        
        for(char& c : s){
            if(c == '('){
                if(right_to_add&1){
                    //actually add one ')'
                    ++added;
                    //so the ')' needed to be added is decreased by one
                    --right_to_add;
                }
                //meet one '(', so we need two more ')'
                right_to_add += 2;
            }else{
                //meet one ')', so need one less ')'
                --right_to_add;
                if(right_to_add < 0){
                    //add one '('
                    ++added;
                    /*
                    because we have added one '(',
                    we need two more ')'
                    */
                    right_to_add += 2;
                }
            }
        }
        
        return added + right_to_add;
    }
};
