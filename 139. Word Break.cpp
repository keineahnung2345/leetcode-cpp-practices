//DP
//Runtime: 28 ms, faster than 48.19% of C++ online submissions for Word Break.
//Memory Usage: 10.8 MB, less than 61.87% of C++ online submissions for Word Break.
//time: O(N^3), substr takes O(N)
//space: O(N)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        //padding, assume empty string is a valid dictionary word
        dp[n] = true;
        
        for(int i = n-1; i >= 0; --i){
            dp[i] = find(wordDict.begin(), wordDict.end(), s.substr(i)) != wordDict.end();
            
            /*
            split s[i:] into s[i:j-1] and s[j:],
            and see if the split is valid
            */
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

//DP optimized from above
//Runtime: 12 ms, faster than 79.03% of C++ online submissions for Word Break.
//Memory Usage: 9.6 MB, less than 68.61% of C++ online submissions for Word Break.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        
        vector<bool> dp(n+1, false);
        dp[n] = true;
        
        for(int i = n-1; i >= 0; --i){
            for(int j = i+1; j <= n; ++j){
                // cout << i << ", " << j << ", " << s.substr(i, j-i) << endl;
                if(dp[j] && find(wordDict.begin(), wordDict.end(), s.substr(i, j-i)) != wordDict.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[0];
    }
};

//DP
//https://leetcode.com/problems/concatenated-words/discuss/348972/Java-Common-template-Word-Break-I-Word-Break-II-Concatenated-Words
//Runtime: 28 ms, faster than 49.06% of C++ online submissions for Word Break.
//Memory Usage: 12.9 MB, less than 52.89% of C++ online submissions for Word Break.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
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
        dp[n] = true;
        
        Trie* trie = new Trie();
        
        for(string& word : wordDict){
            trie->add(word);
        }
        
        for(int i = n-1; i >= 0; --i){
            dp[i] = trie->find(s.substr(i));
            
            for(int j = n; j >= i+1; --j){
                dp[i] = dp[j] && trie->find(s.substr(i, j-i));
                if(dp[i]) break;
            }
        }
        
        return dp[0];
    }
};
