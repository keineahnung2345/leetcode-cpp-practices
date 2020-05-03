/**
Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
**/

//Runtime: 32 ms, faster than 49.26% of C++ online submissions for Ransom Note.
//Memory Usage: 10.8 MB, less than 98.90% of C++ online submissions for Ransom Note.
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> count(26);
        
        /*
        need to visit all chars in magazine first,
        then to visit chars in ransomNote,
        because we may use chars in magazine in any order
        */
        for(char c : magazine){
            count[c-'a'] += 1;
        }
        
        for(char c : ransomNote){
            count[c-'a'] -= 1;
            if(count[c-'a'] < 0) return false;
        }
        
        return true;
    }
};
