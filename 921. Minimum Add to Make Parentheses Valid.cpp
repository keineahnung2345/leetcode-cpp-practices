/**
Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')', and in any positions ) so that the resulting parentheses string is valid.

Formally, a parentheses string is valid if and only if:

It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.

 

Example 1:

Input: "())"
Output: 1
Example 2:

Input: "((("
Output: 3
Example 3:

Input: "()"
Output: 0
Example 4:

Input: "()))(("
Output: 4
 

Note:

S.length <= 1000
S only consists of '(' and ')' characters.
**/

/**
Intuition and Algorithm

Keep track of the balance of the string: the number of '(''s minus the number of ')''s. A string is valid if its balance is 0, plus every prefix has non-negative balance.

The above idea is common with matching brackets problems, but could be difficult to find if you haven't seen it before.

Now, consider the balance of every prefix of S. If it is ever negative (say, -1), we must add a '(' bracket. Also, if the balance of S is positive (say, +B), we must add B ')' brackets at the end.

//class Solution {
    public int minAddToMakeValid(String S) {
        int ans = 0, bal = 0;
        for (int i = 0; i < S.length(); ++i) {
            bal += S.charAt(i) == '(' ? 1 : -1;
            // It is guaranteed bal >= -1
            if (bal == -1) {
                ans++;
                bal++;
            }
        }

        return ans + bal;
    }
}

// meet (): bal: 1->0, ans: 0->0
// meet ((: bal: 1->2, ans: 0->0
// meet )): bal: 0 -> 0, ans: 1->2
// "bal" means remaining "(", "ans" means how many ')' added

Complexity Analysis

Time Complexity: O(N), where N is the length of S.

Space Complexity: O(1). 
**/

//Your runtime beats 100.00 % of cpp submissions.
class Solution {
public:
    int minAddToMakeValid(string S) {
        // remove "()" and count remaining '(' or ')'s
        int remain = S.size();
        
        int found = 0;
        // while((found=S.find("()")) != NULL){//This will give wrong answer!!
        while((found=S.find("()")) != string::npos){//Must use string::npos!!
            remain-=2;
            S.erase(found, 2); //need to delete found () !
        }
        return remain;
    }
};
