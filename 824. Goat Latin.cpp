/**
A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin. 

 

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each word.
1 <= S.length <= 150.
**/

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Goat Latin.
//Memory Usage: 9.7 MB, less than 73.58% of C++ online submissions for Goat Latin.

class Solution {
public:
    string toGoatLatinToken(string token, int order, string delimeter){
        if(!(token[0]=='a' || token[0]=='e' || token[0]=='i' || token[0]=='o' || token[0]=='u' || token[0]=='A' || token[0]=='E' || token[0]=='I' || token[0]=='O' || token[0]=='U')){
            token += token[0];
            token.erase(token.begin());
        }
        string aMul(order, 'a');
        return token + "ma" + aMul + delimeter;
    }
    
    string toGoatLatin(string S) {
        string ans;
        size_t pos = 0;
        string token;
        int order = 1;
        string delimeter = " ";
        while ((pos = S.find(delimeter)) != string::npos) {
            token = S.substr(0, pos);
            ans += toGoatLatinToken(token, order, delimeter);
            order++;
            S.erase(0, pos + delimeter.size());
        }
        ans += toGoatLatinToken(S, order, "");
        return ans;
    }
};

/**
Approach #1: String [Accepted]
Intuition

We apply the steps given in the problem in a straightforward manner. The difficulty lies in the implementation.

Algorithm

For each word in the sentence split, if it is a vowel we consider the word, otherwise we consider the rotation of the word (either word[1:] + word[:1] in Python, otherwise word.substring(1) + word.substring(0, 1) in Java).

Afterwards, we add "ma", the desired number of "a"'s, and a space character.
**/

/**
Complexity Analysis

Time Complexity: O(N^2), where N is the length of S. 
This represents the complexity of rotating the word and adding extra "a" characters.

Space Complexity: O(N^2), the space added to the answer by adding extra "a" characters.
**/
