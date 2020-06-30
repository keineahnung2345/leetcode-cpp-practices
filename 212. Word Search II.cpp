//trie, dfs
//build trie from board, and then search with words(slow)
//TLE
//32 / 36 test cases passed.
class TrieNode{
public:
    vector<TrieNode*> children;
    
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
    
    void add(string word){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
    }
    
    bool find(string word){
        TrieNode* cur = root;
        for(char c : word){
            // cout << c << " ";
            cur = cur->children[c-'a'];
            if(cur == nullptr){
                return false;
            }
        }
        // cout << endl;
        
        return true;
    }
};

class Solution {
public:
    Trie* trie;
    vector<vector<int>> dirs;
    
    
    void dfs(vector<vector<char>>& board, int m, int n, vector<vector<bool>>& visited, int ci, int cj, string& str, int maxLen){
        if(str.size() < maxLen){
            // we won't build str whose size > maxLen
            // cout << ci << ", " << cj << ", " << str.size() << endl;
            //continue to build str
            for(vector<int>& dir : dirs){
                int ni = ci + dir[0];
                int nj = cj + dir[1];
                
                if(ni >= 0 && ni < m && nj >= 0 && nj < n && !visited[ni][nj]){
                    visited[ni][nj] = true;
                    str += board[ni][nj];
                    dfs(board, m, n, visited, ni, nj, str, maxLen);
                    visited[ni][nj] = false;
                    str.pop_back();
                }
            }
        }
            
        // cout << str << endl;
        trie->add(str);
    };
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size();
        if(m == 0) return vector<string>();
        int n = board[0].size();
        
        int maxLen = 0;
        for(string& word : words){
            maxLen = max(maxLen, (int)word.size());
        }
        // cout << "maxLen: " << maxLen << endl;
        
        trie = new Trie();
        
        dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        
        string str;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                /*
                process (ci, cj) before calling dfs, 
                is there a better way?
                */
                str = string(1, board[i][j]);
                for(int tmp = 0; tmp < m; ++tmp){
                    fill(visited[tmp].begin(), visited[tmp].end(), false);
                }
                visited[i][j] = true;
                dfs(board, m, n, visited, i, j, str, maxLen);
            }
        }
        
        vector<string> ans;
        
        for(string& word : words){
            if(trie->find(word)){
                ans.push_back(word);
            }
        }
        
        return ans;
    }
};

//trie, dfs
//build trie from words, and then search with board
//https://leetcode.com/problems/word-search-ii/discuss/59780/Java-15ms-Easiest-Solution-(100.00)
//Runtime: 76 ms, faster than 81.82% of C++ online submissions for Word Search II.
//Memory Usage: 38.4 MB, less than 42.23% of C++ online submissions for Word Search II.
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
    
    void add(string word){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
        /*
        store the word at leaf,
        so we don't need to reconstruct it
        */
        cur->word = word;
    }
    
    bool find(string word){
        TrieNode* cur = root;
        for(char c : word){
            cur = cur->children[c-'a'];
            if(cur == nullptr){
                return false;
            }
        }
        
        return true;
    }
};

class Solution {
public:
    Trie* trie;
    
    void dfs(vector<vector<char>>& board, int m, int n, int ci, int cj, TrieNode* node, vector<string>& ans){
        //current building string "str" is replaced by "node"
        //visited is replaced by '#'
        char c = board[ci][cj];
        //visited
        if(c == '#') return;
        //cannot find int trie
        if(node->children[c-'a'] == nullptr) return;
        
        node = node->children[c-'a'];
        if(node->word != ""){
            ans.push_back(node->word);
            //de-duplicate
            //so that it won't be found again
            node->word = "";
        }
        
        //mark as visited
        board[ci][cj] = '#';
        
        if(ci > 0)   dfs(board, m, n, ci-1, cj,   node, ans);
        if(ci+1 < m) dfs(board, m, n, ci+1, cj,   node, ans);
        if(cj > 0)   dfs(board, m, n, ci,   cj-1, node, ans);
        if(cj+1 < n) dfs(board, m, n, ci,   cj+1, node, ans);
                
        board[ci][cj] = c;
    };
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size();
        if(m == 0) return vector<string>();
        int n = board[0].size();
        
        trie = new Trie();
        
        for(string& word : words){
            trie->add(word);
        }
        
        vector<string> ans;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                dfs(board, m, n, i, j, trie->root, ans);
            }
        }
        
        return ans;
    }
};
