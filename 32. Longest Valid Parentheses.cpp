//Brute force
//TLE
//217 / 230 test cases passed.
//time: O(N^3), space: O(N)
class Solution {
public:
    bool isValid(string s){
        stack<char> stk;
        
        for(char c : s){
            if(c == '('){
                stk.push(c);
            }else{
                if(!stk.empty() && stk.top() == '('){
                    stk.pop();
                }else{
                    return false;
                }
            }
        }
        
        return stk.empty();
    };
    
    int longestValidParentheses(string s) {
        int maxLen = 0;
        
        for(int i = 0; i < s.size(); ++i){
            for(int j = 2; i+j-1 < s.size(); ++j){
                if(isValid(s.substr(i, j))){
                    maxLen = max(maxLen, j);
                }
            }
        }
        
        return maxLen;
    }
};

//DP
//Runtime: 8 ms, faster than 88.40% of C++ online submissions for Longest Valid Parentheses.
//Memory Usage: 7.5 MB, less than 22.04% of C++ online submissions for Longest Valid Parentheses.
//time: O(N), space: O(N)
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        //dp[i]: length of longest valid substring ending at i
        vector<int> dp(n, 0);
        
        int maxLen = 0;
        
        //i starts from 1: we can't have a valid substring ending at 0
        for(int i = 1; i < n; ++i){
            if(s[i] == ')'){
                /*
                dp[i]: length of longest valid substring ending at i
                s[i] == ')': valid substring can't end at '(', so we don't care it
                */
                if(s[i-1] == '('){
                    //"pairs end at i-2" + "()"
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                }else{
                    //s[i-1] == ')'
                    if(i-1-dp[i-1] >= 0 && s[i-1-dp[i-1]] == '('){
                        //"pairs end at i-1-dp[i-1]-1"(this could be empty) + '(' + "pairs ends at i-1" + ')'
                        dp[i] = (i-1-dp[i-1]-1 >= 0 ? dp[i-1-dp[i-1]-1] : 0) + 1 + dp[i-1] + 1;
                    }
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        
        return maxLen;
    }
};

//stack, not understand
//Runtime: 8 ms, faster than 88.40% of C++ online submissions for Longest Valid Parentheses.
//Memory Usage: 7.2 MB, less than 74.62% of C++ online submissions for Longest Valid Parentheses. 
//time: O(N), space: O(N)
class Solution {
public:
    void print(stack<int>& stk){
        int* end   = &stk.top() + 1;
        int* begin = end - stk.size();
        vector<int> stack_contents(begin, end);

        //1 4 9 3
        for(int e : stack_contents){
            cout << e << " ";
        }
        cout << endl;
    }
    
    int longestValidParentheses(string s) {
        int n = s.size();
        int maxLen = 0;
        stack<int> stk;
        
        stk.push(-1);
        
        for(int i = 0; i < n; ++i){
            if(s[i] == '('){
                stk.push(i);
            }else{
                stk.pop();
                if(stk.empty()){
                    //used later, serves as ending of last substring 
                    stk.push(i);
                }else{
                    maxLen = max(maxLen, i - stk.top());
                }
            }
            // print(stk);
        }
        
        return maxLen;
    }
};

//O(1) space
//Runtime: 8 ms, faster than 88.40% of C++ online submissions for Longest Valid Parentheses.
//Memory Usage: 6.7 MB, less than 98.91% of C++ online submissions for Longest Valid Parentheses.
//time: O(N), space: O(1)
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int maxLen = 0;
        
        for(int i = 0; i < n; ++i){
            if(s[i] == '('){
                ++left;
            }else{
                ++right;
            }
            
            if(right == left){
                maxLen = max(maxLen, 2*left);
            }else if(right > left){
                //more close than open
                left = right = 0;
            }
        }
        
        //traverse in reverse order
        left = right = 0;
        for(int i = n-1; i >= 0; --i){
            if(s[i] == '('){
                ++left;
            }else{
                ++right;
            }
            if(left == right){
                maxLen = max(maxLen, 2*left);
            }else if(left > right){
                //more close than open
                left = right = 0;
            }
        }
        
        return maxLen;
    }
};
