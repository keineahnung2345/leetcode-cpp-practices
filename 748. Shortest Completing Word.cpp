/**
Find the minimum length word from a given dictionary words, which has all the letters from the string licensePlate. Such a word is said to complete the given string licensePlate

Here, for letters we ignore case. For example, "P" on the licensePlate still matches "p" on the word.

It is guaranteed an answer exists. If there are multiple answers, return the one that occurs first in the array.

The license plate might have the same letter occurring multiple times. For example, given a licensePlate of "PP", the word "pair" does not complete the licensePlate, but the word "supper" does.

Example 1:
Input: licensePlate = "1s3 PSt", words = ["step", "steps", "stripe", "stepple"]
Output: "steps"
Explanation: The smallest length word that contains the letters "S", "P", "S", and "T".
Note that the answer is not "step", because the letter "s" must occur in the word twice.
Also note that we ignored case for the purposes of comparing whether a letter exists in the word.
Example 2:
Input: licensePlate = "1s3 456", words = ["looks", "pest", "stew", "show"]
Output: "pest"
Explanation: There are 3 smallest length words that contains the letters "s".
We return the one that occurred first.
Note:
licensePlate will be a string with length in range [1, 7].
licensePlate will contain digits, spaces, or letters (uppercase or lowercase).
words will have a length in the range [10, 1000].
Every words[i] will consist of lowercase letters, and have length in range [1, 15].
**/

//Runtime: 40 ms, faster than 40.41% of C++ online submissions for Shortest Completing Word.
//Memory Usage: 17.1 MB, less than 21.88% of C++ online submissions for Shortest Completing Word.

class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        map<char, int> charCount;
        
        for(char c : licensePlate){
            if(!isalpha(c)) continue;
            c = tolower(c);
            if(charCount.find(c)==charCount.end()){
                charCount[c]=1; 
            }else{
                charCount[c]+=1;
            }
        }
        
        // for(map<char, int>::iterator it = charCount.begin(); it!=charCount.end(); it++){
        //     cout << it->first << " " << it->second << endl;
        // }
        
        string ans = "";
        for(string word : words){
            map<char, int> tmp = charCount;
            for(char c : word){
                if(tmp.find(c)!=tmp.end()){
                    tmp[c]--;
                    if(tmp[c]==0) tmp.erase(c);
                }
            }
            // cout << word << " " << tmp.size() << endl;
            if(tmp.size()==0){
                if(ans==""){
                    ans = word;
                }else if(word.size() < ans.size()){
                    ans = word;
                }
            }
        }
        
        return ans;
    }
};
