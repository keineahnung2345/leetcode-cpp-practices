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

/**
Approach #1: Build String [Accepted]
**/
/**
Complexity Analysis

Time Complexity: O(M + N)O(M+N), where M, NM,N are the lengths of S and T respectively.

Space Complexity: O(M + N)O(M+N).
**/

/**
Approach #2: Two Pointer [Accepted]
Intuition

When writing a character, it may or may not be part of the final string depending on how many backspace keystrokes occur in the future.

If instead we iterate through the string in reverse, then we will know how many backspace characters we have seen, and therefore whether the result includes our character.

Algorithm

Iterate through the string in reverse. If we see a backspace character, the next non-backspace character is skipped. If a character isn't skipped, it is part of the final answer.

See the comments in the code for more details.
**/
/*8
Complexity Analysis

Time Complexity: O(M + N)O(M+N), where M, NM,N are the lengths of S and T respectively.

Space Complexity: O(1)O(1).**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Backspace String Compare.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Backspace String Compare.
/**
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int curS = S.size()-1, curT = T.size()-1;
        int skipS = 0, skipT = 0;
        
        //if two string ends concurrently, we return true
        while(curS >= 0 || curT >= 0){
            while(curS >= 0){
                if(S[curS] == '#'){skipS++; curS--;}
                else if(skipS > 0) {skipS--; curS--;}
                //find the char not skipped
                else break;
            }
            while(curT >= 0){
                if(T[curT] == '#'){skipT++; curT--;}
                else if(skipT > 0) {skipT--; curT--;}
                else break;
            }
            if(curS >= 0 && curT >= 0 && S[curS] != T[curT]) return false;
            //one string ends earlier than the other
            if((curS >= 0) != (curT >= 0)) return false;
            curS--; curT--;
        }
        return true;
    }
};
**/
