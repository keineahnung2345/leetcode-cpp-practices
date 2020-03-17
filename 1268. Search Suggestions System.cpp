//Runtime: 136 ms, faster than 42.73% of C++ online submissions for Search Suggestions System.
//Memory Usage: 96.6 MB, less than 100.00% of C++ online submissions for Search Suggestions System.

class TrieNode{
public:
    vector<TrieNode*> children;
    string word;
    TrieNode(){
        children = vector<TrieNode*>(26, NULL);
        word = "";
    }
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    }
    
    void put(string& word){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->children[c-'a'] == NULL){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
        cur->word = word;
    }
    
    vector<string> search3Prefix(string& prefix){
        TrieNode* cur = root;
        for(char c : prefix){
            if(cur->children[c-'a'] == NULL){
                return vector<string>();
            }
            cur = cur->children[c-'a'];
        }
        //find all product with the prefix
        //dfs
        vector<string> res;
        stack<TrieNode*> stk;
        stk.push(cur);
        while(!stk.empty()){
            TrieNode* cur = stk.top(); stk.pop();
            
            if(cur->word != ""){
                res.push_back(cur->word);
                if(res.size() == 3) break;
            }
            
            for(int i = 25; i >= 0; i--){
                if(cur->children[i] != NULL){
                    stk.push(cur->children[i]);
                }
            }
        }
        
        return res;
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie* trie = new Trie();
        for(string& product : products){
            trie->put(product);
        }
        
        int N = searchWord.size();
        vector<vector<string>> ans(N, vector<string>());
        
        TrieNode* cur = trie->root;
        for(int i = 0; i < N; i++){
            char c = searchWord[i];
            // cout << i << " " << c << endl;
            if(cur->children[c-'a'] != NULL){
                string prefix = searchWord.substr(0, i+1);
                // cout << "prefix: " << prefix << endl;
                ans[i] = trie->search3Prefix(prefix);
                
                cur = cur->children[c-'a'];
            }else{
                //cannot find c
                break;
            }
        }
        
        return ans;
    }
};
