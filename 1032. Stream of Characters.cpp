//Runtime: 1760 ms, faster than 6.41% of C++ online submissions for Stream of Characters.
//Memory Usage: 105.9 MB, less than 58.81% of C++ online submissions for Stream of Characters.
class TrieNode{
public:
    vector<TrieNode*> children;
    bool isEnd;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
        isEnd = false;
    }
};

class StreamChecker {
public:
    TrieNode* root;
    int max_word_len;
    vector<TrieNode*> nodes;
    
    void add(string& word){
        TrieNode* cur = root;
        
        for(char& c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
        
        cur->isEnd = true;
    }
    
    StreamChecker(vector<string>& words) {
        root = new TrieNode();
        max_word_len = 0;
        
        for(string& word : words){
            add(word);
            max_word_len = max(max_word_len, (int)word.size());
        }
    }
    
    bool query(char letter) {
        bool found = false;
        
        nodes.push_back(root);
        // cout << "nodes: " << nodes.size() << endl;
        for(int i = nodes.size()-1; i >= 0; --i){
            // cout << "i: " << i << " ";
            if(nodes[i]->children[letter-'a'] == nullptr){
                nodes.erase(nodes.begin()+i);
            }else{
                nodes[i] = nodes[i]->children[letter-'a'];
                if(nodes[i]->isEnd){
                    found = true;
                }
            }
        }
        
        return found;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
 
