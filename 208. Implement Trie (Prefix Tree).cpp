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
 
//Runtime: 92 ms, faster than 59.89% of C++ online submissions for Implement Trie (Prefix Tree).
//Memory Usage: 48 MB, less than 30.86% of C++ online submissions for Implement Trie (Prefix Tree).
class TrieNode{
private:
    vector<TrieNode*> links;
    int R = 26;
    bool isEnd = false;
    
public:    
    TrieNode() {
        links = vector<TrieNode*>(R);
    }
    
    bool containsKey(char c){
        return links[c-'a'] != NULL;
    }
    
    TrieNode* get(char c){
        return links[c-'a'];
    }
    
    void put(char c, TrieNode* node){
        links[c-'a'] = node;
    }
    
    void setEnd(){
        isEnd = true;
    }
    
    bool getEnd(){
        return isEnd;
    }
};

class Trie {
private:
    TrieNode *root;
    
    // search a prefix or whole key in trie and
    // returns the node where search ends
    TrieNode* searchPrefix(string word){
        TrieNode *node = root;
        for(char c : word){
            if(node->containsKey(c)){
                node = node->get(c);
            }else{
                return NULL;
            }
        }
        return node;
    }
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    //time: O(m), space: O(m), m is the key length.
    void insert(string word) {
        TrieNode *node = root;
        for(char c : word){
            if(!node->containsKey(c)){
                node->put(c, new TrieNode());
            }
            node = node->get(c);
        }
        node->setEnd();
    }
    
    /** Returns if the word is in the trie. */
    //time: O(m), space: O(1)
    bool search(string word) {
        TrieNode *node = searchPrefix(word);
        return node != NULL && node->getEnd();
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    //time: O(m), space: O(1)
    bool startsWith(string prefix) {
        TrieNode *node = searchPrefix(prefix);
        return node != NULL;
    }
};
