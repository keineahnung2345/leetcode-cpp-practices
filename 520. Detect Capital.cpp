/**
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
Note: The input will be a non-empty word consisting of uppercase and lowercase latin letters.
**/

//Runtime: 8 ms, faster than 99.61% of C++ online submissions for Detect Capital.
//Memory Usage: 11.2 MB, less than 92.50% of C++ online submissions for Detect Capital.

class Solution {
public:
    bool detectCapitalUse(string word) {
        if(isupper(word[0])){
            if(word.size()<2) return true;
            if(isupper(word[1])){
                for(int i = 1; i < word.size(); i++){
                    if(islower(word[i])) return false;
                }
            }else{
                for(int i = 1; i < word.size(); i++){
                    if(isupper(word[i])) return false;
                }
            }
        }else{
            for(int i = 1; i < word.size(); i++){
                if(isupper(word[i])) return false;
            }
        }
        return true;
    }
};
