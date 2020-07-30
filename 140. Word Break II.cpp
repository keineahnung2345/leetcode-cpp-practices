//DP
//TLE
//31 / 36 test cases passed.
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        if(n == 0) return vector<string>();
        
        vector<vector<string>> segs(n);
        
        for(int i = n-1; i >= 0; --i){
            //check if s[i:] is itself a valid dict word
            if(find(wordDict.begin(), wordDict.end(), s.substr(i)) != wordDict.end()){
                segs[i].push_back(s.substr(i));
            }
            //split s[i] into two parts
            /*
            s[i:] : s[i:j-1] + s[j:]
            s[i:j-1] is a valid dictionary word
            s[j:] is composed by valid dictionary words
            */
            for(int j = n-1; j >= i+1; --j){
                // cout << "j: " << j << ", segs[j].size(): " << segs[j].size() << endl;
                // cout << "finding word: " << s.substr(i, j-i) << endl;
                if(!segs[j].empty() && 
                         find(wordDict.begin(), wordDict.end(), s.substr(i, j-i)) != wordDict.end()){
                    for(string& prev_seg : segs[j]){
                        // cout << s.substr(i, j-i) << " + " << prev_seg << endl;
                        segs[i].push_back(s.substr(i, j-i) + " " + prev_seg);
                    }
                }
            }
        }
        
        // for(int i = 0; i < n; ++i){
        //     cout << "substr: " << s.substr(i) << endl;
        //     for(string& seg : segs[i]){
        //         cout << seg << endl;
        //     }
        // }
        
        return segs[0];
    }
};

//DP + trie
//TLE
//31 / 36 test cases passed.
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
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        if(n == 0) return vector<string>();
        
        Trie* trie = new Trie();
        
        for(string& word : wordDict){
            trie->add(word);
        }
        
        vector<vector<string>> segs(n);
        
        for(int i = n-1; i >= 0; --i){
            //check if s[i:] is itself a valid dict word
            if(trie->find(s.substr(i))){
                segs[i].push_back(s.substr(i));
            }
            //split s[i] into two parts
            /*
            s[i:] : s[i:j-1] + s[j:]
            s[i:j-1] is a valid dictionary word
            s[j:] is composed by valid dictionary words
            */
            for(int j = n-1; j >= i+1; --j){
                // cout << "j: " << j << ", segs[j].size(): " << segs[j].size() << endl;
                // cout << "finding word: " << s.substr(i, j-i) << endl;
                if(!segs[j].empty() && trie->find(s.substr(i, j-i))){
                    for(string& prev_seg : segs[j]){
                        // cout << s.substr(i, j-i) << " + " << prev_seg << endl;
                        segs[i].push_back(s.substr(i, j-i) + " " + prev_seg);
                    }
                }
            }
        }
        
        // for(int i = 0; i < n; ++i){
        //     cout << "substr: " << s.substr(i) << endl;
        //     for(string& seg : segs[i]){
        //         cout << seg << endl;
        //     }
        // }
        
        return segs[0];
    }
};
