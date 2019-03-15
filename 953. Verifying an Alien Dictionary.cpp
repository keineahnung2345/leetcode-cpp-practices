/**
In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographicaly in this alien language.

 

Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).
 

Note:

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are english lowercase letters.
**/

/**
Complexity Analysis
Time Complexity: O(C), where C is the total content of words.
Space Complexity: O(1). 
**/

//Runtime: 8 ms, faster than 99.47% of C++ online submissions for Verifying an Alien Dictionary.
//Memory Usage: 9.8 MB, less than 45.54% of C++ online submissions for Verifying an Alien Dictionary.
class Solution {
public:
    int c2i(char c, string& order){
        return find(order.begin(), order.end(), c) - order.begin();
    }
    bool isAlienSorted(vector<string>& words, string order) {
        for(int i = 0; i < words.size() - 1; i++){
            int l = min(words[i].size(), words[i+1].size());
            bool formerSame = true;
            for(int j = 0; j < l; j++){
                if(c2i(words[i][j], order) < c2i(words[i+1][j], order)){
                    formerSame = false;
                    break;
                }else if(c2i(words[i][j], order) > c2i(words[i+1][j], order)){
                    return false;
                }
            }
            if(formerSame && words[i].size() > words[i+1].size()){
                return false;
            }
        }
        return true;
    }
};
