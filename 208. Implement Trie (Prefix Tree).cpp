//Runtime: 548 ms, faster than 5.04% of C++ online submissions for Implement Trie (Prefix Tree).
//Memory Usage: 23.9 MB, less than 100.00% of C++ online submissions for Implement Trie (Prefix Tree).

class Trie {
public:
    set<string> words;
    /** Initialize your data structure here. */
    Trie() {
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        words.insert(word);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return words.find(word)!=words.end();
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        for(set<string>::iterator it = words.begin(); it!=words.end(); it++){
            if((*it).rfind(prefix, 0) == 0) return true;
        }
        return false;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
 
