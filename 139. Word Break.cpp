//DP
//Runtime: 28 ms, faster than 48.19% of C++ online submissions for Word Break.
//Memory Usage: 10.8 MB, less than 61.87% of C++ online submissions for Word Break.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        //padding, assume empty string is a valid dictionary word
        dp[n] = true;
        
        for(int i = n-1; i >= 0; --i){
            dp[i] = find(wordDict.begin(), wordDict.end(), s.substr(i)) != wordDict.end();
            
            // split s into s[i:j-1] and s[j:]
            for(int j = n; j >= i+1; --j){
                //s[j:] is composed by valid dictionary words
                //and s[i:j-1] is a valid dictionary word
                dp[i] = dp[j] && find(wordDict.begin(), wordDict.end(), s.substr(i, j-i)) != wordDict.end();
                if(dp[i]) break;
            }
        }
        
        return dp[0];
    }
};

//trie
//Runtime: 24 ms, faster than 56.77% of C++ online submissions for Word Break.
//Memory Usage: 13.7 MB, less than 26.97% of C++ online submissions for Word Break.
class TrieNode {
public:
    vector<TrieNode*> children;
    bool end;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
        end = false;
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    void add(string& word){
        TrieNode* cur = root;
        for(char c : word){
            if(!cur->children[c-'a']){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
        cur->end = true;
    }
    
    bool find(string word){
        TrieNode* cur = root;
        for(char c : word){
            if(!cur->children[c-'a']){
                return false;
            }
            cur = cur->children[c-'a'];
        }
        return cur->end;
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        //padding, assume empty string is a valid dictionary word
        dp[n] = true;
        
        Trie* trie = new Trie();
        
        for(string& word : wordDict){
            trie->add(word);
        }
        
        for(int i = n-1; i >= 0; --i){
            dp[i] = trie->find(s.substr(i));
            
            // split s into s[i:j-1] and s[j:]
            for(int j = n; j >= i+1; --j){
                //s[j:] is composed by valid dictionary words
                //and s[i:j-1] is a valid dictionary word
                dp[i] = dp[j] && trie->find(s.substr(i, j-i));
                if(dp[i]) break;
            }
        }
        
        return dp[0];
    }
};
