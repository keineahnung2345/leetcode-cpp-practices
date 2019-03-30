/**
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Backspace String Compare.
//Memory Usage: 8.6 MB, less than 98.93% of C++ online submissions for Backspace String Compare.

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        stack<char> stkS, stkT;
        
        for(char c : S){
            if(c == '#' && !stkS.empty()) stkS.pop();
            else if(c != '#') stkS.push(c);
            //ignore '#' when stack is empty
        }
        
        for(char c : T){
            if(c == '#' && !stkT.empty()) stkT.pop();
            else if(c != '#') stkT.push(c);
        }
        
        if(stkS.size() != stkT.size()) return false;
        
        while(!stkS.empty() && !stkT.empty()){
            char cS = stkS.top(), cT = stkT.top();
            if(cS != cT) return false;
            stkS.pop();
            stkT.pop();
        }
        
        if(!stkS.empty() || !stkT.empty()) return false;
        return true;
    }
};
