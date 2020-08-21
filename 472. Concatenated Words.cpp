//Trie + BFS
//TLE
//43 / 44 test cases passed.
class TrieNode{
public:
    vector<TrieNode*> children;
    string word;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    void add(string& word){
        TrieNode* cur = root;
        
        for(char& c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            
            cur = cur->children[c-'a'];
        }
        
        cur->word = word;
    }
    
    /*
    find all prefixes of "word",
    note that the word itself is also considered as a prefix
    */
    void findPrefixes(string& word, queue<pair<string, int>>& prefixes){
        TrieNode* cur = root;
        
        for(char& c : word){
            cur = cur->children[c-'a'];
            
            if(cur == nullptr){
                break;
            }
            
            if(!cur->word.empty()){ //a.k.a isEnd
                prefixes.push({cur->word, word.size() - cur->word.size()});
            }
        }
    }
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        Trie* trie = new Trie();
        
        for(int i = 0; i < words.size(); ++i){
            trie->add(words[i]);
        }
        
        vector<string> ans;
        
        for(string& word : words){
            // cout << "word: " << word << endl;
            //(word, remain)
            queue<pair<string, int>> prefixes;
            
            //fill prefixes
            trie->findPrefixes(word, prefixes);
            
            while(!prefixes.empty()){
                pair<string, int> p = prefixes.front(); prefixes.pop();
                // cout << p.first << ", " << p.second << endl;
                if(p.second == 0 && p.first != word){
                    //p.second == 0: the remaining unmatched substring's size
                    //p.first != word: avoid the case that we find the string itself
                    ans.push_back(word);
                    break;
                }else{
                    //"remain"'s size is p.second
                    string remain = word.substr(word.size()-p.second);
                    trie->findPrefixes(remain, prefixes);
                }
            }
        }
        
        return ans;
    }
};

//Trie + DFS
//Runtime: 1412 ms, faster than 10.95% of C++ online submissions for Concatenated Words.
//Memory Usage: 654.2 MB, less than 5.39% of C++ online submissions for Concatenated Words.
class TrieNode{
public:
    vector<TrieNode*> children;
    string word;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    void add(string& word){
        TrieNode* cur = root;
        
        for(char& c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            
            cur = cur->children[c-'a'];
        }
        
        cur->word = word;
    }
    
    /*
    find all prefixes of "word",
    note that the word itself is also considered as a prefix
    */
    void findPrefixes(string& word, stack<pair<string, int>>& prefixes){
        TrieNode* cur = root;
        
        for(char& c : word){
            cur = cur->children[c-'a'];
            
            if(cur == nullptr){
                break;
            }
            
            if(!cur->word.empty()){ //a.k.a isEnd
                prefixes.push({cur->word, word.size() - cur->word.size()});
            }
        }
    }
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        Trie* trie = new Trie();
        
        for(int i = 0; i < words.size(); ++i){
            trie->add(words[i]);
        }
        
        vector<string> ans;
        
        for(string& word : words){
            // cout << "word: " << word << endl;
            //(word, remain)
            stack<pair<string, int>> prefixes;
            
            //fill prefixes
            trie->findPrefixes(word, prefixes);
            
            while(!prefixes.empty()){
                pair<string, int> p = prefixes.top(); prefixes.pop();
                // cout << p.first << ", " << p.second << endl;
                if(p.second == 0 && p.first != word){
                    //p.second == 0: the remaining unmatched substring's size
                    //p.first != word: avoid the case that we find the string itself
                    ans.push_back(word);
                    break;
                }else{
                    //"remain"'s size is p.second
                    string remain = word.substr(word.size()-p.second);
                    trie->findPrefixes(remain, prefixes);
                }
            }
        }
        
        return ans;
    }
};

//Trie + DFS, optimized
//https://leetcode.com/problems/concatenated-words/discuss/95644/102ms-java-Trie-%2B-DFS-solution.-With-explanation-easy-to-understand.
//Runtime: 488 ms, faster than 78.18% of C++ online submissions for Concatenated Words.
//Memory Usage: 290.5 MB, less than 36.74% of C++ online submissions for Concatenated Words.
class TrieNode{
public:
    vector<TrieNode*> children;
    string word;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    void add(string& word){
        TrieNode* cur = root;
        
        for(char& c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            
            cur = cur->children[c-'a'];
        }
        
        cur->word = word;
    }
    
    /*
    find all prefixes of "word",
    note that the word itself is also considered as a prefix
    */
    bool test(string& word, int start, int& count){
        TrieNode* cur = root;
        
        for(int i = start; i < word.size(); ++i){
            char c = word[i];
            cur = cur->children[c-'a'];
            
            if(cur == nullptr){
                break;
            }
            
            if(!cur->word.empty()){ //a.k.a isEnd
                ++count;
                if(i == word.size()-1){
                    //constructed by more than 1 words
                    return count > 1;
                }
                if(test(word, i+1, count)){
                    return true;
                }
                --count;
            }
        }
        
        return false;
    }
};

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        Trie* trie = new Trie();
        
        for(int i = 0; i < words.size(); ++i){
            trie->add(words[i]);
        }
        
        vector<string> ans;
        
        for(string& word : words){
            // cout << "word: " << word << endl;
            if(word.empty()) continue;
            int count = 0;
            if(trie->test(word, 0, count)){
                ans.push_back(word);
            }
        }
        
        return ans;
    }
};

//DP, Word Break I
//https://leetcode.com/problems/concatenated-words/discuss/95652/Java-DP-Solution
//TLE
//6 / 44 test cases passed.
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        if(wordDict.empty())
            return false;
        
        int n = s.size();
        
        //key: end index, 1-based
        vector<bool> dp(n+1, false);
        //empty string
        dp[0] = true;
        
        for(int end = 1; end <= n; ++end){
            for(int start = 0; start < end; ++start){
                //dp[start]: s[0...start-1]
                if(dp[start] && find(wordDict.begin(), wordDict.end(), s.substr(start, end-start)) != wordDict.end()){
                    //s[0...end-1] can be split into s[0...start-1] and s[start...end-1]
                    dp[end] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
    
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        int n = words.size();
        
        vector<string> ans;
        
        sort(words.begin(), words.end(), [](const string& w1, const string& w2){
            return w1.size() < w2.size();
        });
        
        unordered_set<string> preWords;
        for(string& word : words){
            if(wordBreak(word, preWords)){
                ans.push_back(word);
            }
            preWords.insert(word);
        }
        
        return ans;
    }
};
