//Solution 2.1: Shuffle the Wordlist
//https://leetcode.com/problems/guess-the-word/discuss/133862/Random-Guess-and-Minimax-Guess-with-Comparison
//WA
//1 / 6 test cases passed.
//time: O(N), space: O(N)
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    int match(string& a, string& b){
        int diff = 0;
        
        for(int i = 0; i < a.size(); ++i){
            if(a[i] != b[i]) ++diff;
        }
        
        return diff;
    };
    
    void findSecretWord(vector<string>& wordlist, Master& master) {
        random_shuffle(wordlist.begin(), wordlist.end());
        
        for(int i = 0; i < 10 && !wordlist.empty(); ++i){
            int diff = master.guess(wordlist[0]);
            //only retain the words who has "diff" different char with the guessed word
            vector<string> tmp;
            copy_if(wordlist.begin(), wordlist.end(), 
                    back_inserter(tmp), 
                    [&diff, &wordlist, this](string& w){
                        return match(wordlist[0], w) == diff;} 
                   );
            swap(wordlist, tmp);
        }
    }
};

//Solution 2.2: Guess a Random Word
//https://leetcode.com/problems/guess-the-word/discuss/133862/Random-Guess-and-Minimax-Guess-with-Comparison
//WA
//0 / 6 test cases passed.
//time: O(N), space: O(N)
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    int match(string& a, string& b){
        int diff = 0;
        
        for(int i = 0; i < a.size(); ++i){
            if(a[i] != b[i]) ++diff;
        }
        
        return diff;
    };
    
    void findSecretWord(vector<string>& wordlist, Master& master) {
        random_shuffle(wordlist.begin(), wordlist.end());
        
        for(int i = 0; i < 10 && !wordlist.empty(); ++i){
            int diff = master.guess(wordlist[rand()%wordlist.size()]);
            //only retain the words who has "diff" different char with the guessed word
            vector<string> tmp;
            copy_if(wordlist.begin(), wordlist.end(), 
                    back_inserter(tmp), 
                    [&diff, &wordlist, this](string& w){
                        return match(wordlist[0], w) == diff;} 
                   );
            swap(wordlist, tmp);
        }
    }
};
