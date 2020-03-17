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

//https://leetcode.com/problems/search-suggestions-system/discuss/436674/C%2B%2BJavaPython-Sort-and-Binary-Search-the-Prefix
//sort and binary search the prefix
//Runtime: 48 ms, faster than 80.56% of C++ online submissions for Search Suggestions System.
//Memory Usage: 37.3 MB, less than 100.00% of C++ online submissions for Search Suggestions System.
//sort: time: O(nlogn), space: O(logn)
//each query: time: O(logn), space: O(query word's size)
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        auto it = products.begin();
        sort(it, products.end());
        
        // for(string& product: products){
        //     cout << product << " ";
        // }
        // cout << endl;
        
        vector<vector<string>> res;
        string cur = "";
        for (char c : searchWord) {
            cur += c;
            vector<string> suggested;
            //the position of first element >= cur
            it = lower_bound(it, products.end(), cur);
            // cout << cur << " " << it - products.begin() << endl;
            for (int i = 0; i < 3 && it + i != products.end(); i++) {
                string& s = *(it + i);
                // cout << s << " " << s.find(cur) << " | ";
                if (s.find(cur) != 0){
                    //s.find(cur) returns the position of substring
                    //if not found(18446744073709551615) or not at the start, 
                    //then stop searching
                    break;
                }
                suggested.push_back(s);
            }
            // cout << endl;
            res.push_back(suggested);
        }
        return res;
    }
};
