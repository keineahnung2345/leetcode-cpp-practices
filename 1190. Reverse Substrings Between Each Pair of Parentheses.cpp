//Stack, Brute Force
//https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/discuss/383670/JavaC%2B%2BPython-Why-not-O(N)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reverse Substrings Between Each Pair of Parentheses.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Reverse Substrings Between Each Pair of Parentheses.
//time: O(N^2), space: O(N)
class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> openIdxs;
        string ans = "";
        
        for(int i = 0; i < s.size(); i++){
            switch(s[i]){
                case '(':{
                    openIdxs.push(ans.size());
                    break;
                }case ')':{
                    int openIdx = openIdxs.top(); openIdxs.pop();
                    reverse(ans.begin() + openIdx, ans.end());
                    break;
                }default:{
                    ans += s[i];
                    break;
                }
            }
        }
        
        return ans;
    }
};
