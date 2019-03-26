/**
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
**/

//Runtime: 40 ms, faster than 6.44% of C++ online submissions for Valid Anagram.
//Memory Usage: 9.6 MB, less than 5.16% of C++ online submissions for Valid Anagram.

class Solution {
public:
    bool isAnagram(string s, string t) {
        map<char, int> count;
        
        for(char c : s){
            if(count.find(c) == count.end()){
                count[c] = 1;
            }else{
                count[c] += 1;
            }
        }
        
        for(char c : t){
            map<char, int>::iterator it = count.find(c);
            if(it == count.end()){
                return false;
            }else if(count[c] > 1){
                count[c] -= 1;
            }else{
                count.erase(it);
            }
        }
        
        if(count.empty()) return true;
        return false;
    }
};
