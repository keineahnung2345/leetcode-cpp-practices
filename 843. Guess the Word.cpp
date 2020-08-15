//Solution 2.1: Shuffle the Wordlist
//https://leetcode.com/problems/guess-the-word/discuss/133862/Random-Guess-and-Minimax-Guess-with-Comparison
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Guess the Word.
//Memory Usage: 6.2 MB, less than 98.02% of C++ online submissions for Guess the Word.
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
        int matches = 0;
        
        for(int i = 0; i < a.size(); ++i){
            if(a[i] == b[i]) ++matches;
        }
        
        return matches;
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
//5 / 6 test cases passed.
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
        int matches = 0;
        
        for(int i = 0; i < a.size(); ++i){
            if(a[i] == b[i]) ++matches;
        }
        
        return matches;
    };
    
    void findSecretWord(vector<string>& wordlist, Master& master) {
        random_shuffle(wordlist.begin(), wordlist.end());
        
        for(int i = 0; i < 10 && !wordlist.empty(); ++i){
            string guessword = wordlist[rand()%wordlist.size()];
            int diff = master.guess(guessword);
            //only retain the words who has "diff" different char with the guessed word
            vector<string> tmp;
            copy_if(wordlist.begin(), wordlist.end(), 
                    back_inserter(tmp), 
                    [&diff, &guessword, this](string& w){
                        return match(guessword, w) == diff;} 
                   );
            swap(wordlist, tmp);
        }
    }
};

//Solution 3: Minimax
//https://leetcode.com/problems/guess-the-word/discuss/133862/Random-Guess-and-Minimax-Guess-with-Comparison
//Runtime: 12 ms, faster than 27.33% of C++ online submissions for Guess the Word.
//Memory Usage: 6.7 MB, less than 29.88% of C++ online submissions for Guess the Word.
//time: O(N^2), space: O(N)
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
        int matches = 0;
        
        for(int i = 0; i < a.size(); ++i){
            if(a[i] == b[i]) ++matches;
        }
        
        return matches;
    };
    
    void findSecretWord(vector<string>& wordlist, Master& master) {
        for(int i = 0; i < 10 && !wordlist.empty(); ++i){
            //(word, count of words who has 0 match with the key)
            unordered_map<string, int> counter;
        
            for(string& a : wordlist){
                for(string& b : wordlist){
                    if(match(a, b) == 0) ++counter[a];
                }
            }
            
            // cout << "counter built: " << counter.size() << endl;
            
            //guess the word having minimum 0-matching words
            //
            string guessword = *min_element(wordlist.begin(), wordlist.end(),
                [&counter](const string& a, const string& b){
                    return counter[a] < counter[b];
                });
            
            //about 80% of prob the diff will be 0
            int diff = master.guess(guessword);
            
            // cout << "guess: " << guessword << ", " << diff << endl;
            
            /*
            since guessword has least 0-matching words,
            so we can retain least words in next iteration
            */
            vector<string> tmp;
            copy_if(wordlist.begin(), wordlist.end(), 
                    back_inserter(tmp), 
                    [&diff, &guessword, this](string& w){
                        return match(guessword, w) == diff;} 
                   );
            swap(wordlist, tmp);
            
            // cout << "wordlist: " << wordlist.size() << endl;
        }
    }
};
