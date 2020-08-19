//Trie
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
