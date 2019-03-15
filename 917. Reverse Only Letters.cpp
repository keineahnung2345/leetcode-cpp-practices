/**
Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place, and all letters reverse their positions.

 

Example 1:

Input: "ab-cd"
Output: "dc-ba"
Example 2:

Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"
Example 3:

Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"
 

Note:

S.length <= 100
33 <= S[i].ASCIIcode <= 122 
S doesn't contain \ or "
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Reverse Only Letters.
//Memory Usage: 9 MB, less than 40.00% of C++ online submissions for Reverse Only Letters.
class Solution {
public:
    string reverseOnlyLetters(string S) {
        string ans(S.size(),  'a');
        
        //fill with non-alpha characters
        for(int i = 0; i < S.size(); i++){
            if(!isalpha(S[i])){
                ans[i] = S[i];
            }
        }
        
        int j = S.size()-1;
        for(int i = 0; i < S.size(); i++){
            if(!isalpha(S[i])){
                continue;
            }
            //the vector is initialized with 'a'!
            //use while rather than if!
            //skip all filled position
            while(!isalpha(ans[j])){
                j--;
            }
            ans[j--] = S[i];
        }
        
        return ans;
    }
};

/**
Approach 1: Stack of Letters
Intuition and Algorithm
Collect the letters of S separately into a stack, 
so that popping the stack reverses the letters. 
(Alternatively, we could have collected the letters into an array and reversed the array.)
Then, when writing the characters of S, any time we need a letter, we use the one we have prepared instead.
**/

/**
Complexity Analysis
Time Complexity: O(N), where N is the length of S.
Space Complexity: O(N). 
**/

/**
class Solution {
public:
    string reverseOnlyLetters(string S) {
        string ans;
        stack<char> letters;
        
        for(char c : S){
            if(isalpha(c)){
                letters.push(c);
            }
        }
        
        for(char c : S){
            if(!isalpha(c)){
                ans += c;
            }else{
                ans += letters.top();
                letters.pop();
            }
        }
        
        return ans;
    }
};
**/
