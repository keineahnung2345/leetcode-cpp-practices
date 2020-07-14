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
