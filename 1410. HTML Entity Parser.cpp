//Once accepted answer
/*
151 / 154 test cases passed.
Input: "&amp;amp;"
Output: "&"
Expected: "&amp;"
*/
//Runtime: 1204 ms
//Memory Usage: 16.4 MB
class Solution {
public:
    string entityParser(string text) {
        map<string, string> entityMap = {
            {"&quot;" , "\""},
            {"&apos;",  "'"}, 
            {"&amp;" , "&"}, 
            {"&gt;" , ">"}, 
            {"&lt;" , "<"}, 
            {"&frasl;" , "/"}
            };
        
        for(auto it = entityMap.begin(); it != entityMap.end(); it++){
            size_t pos = 0;

            while((pos = text.find(it->first, pos)) != string::npos){
                text.replace(pos, (it->first).length(), it->second);
            }
        }
        
        return text;
    }
};

//Two pointer
//https://leetcode.com/problems/html-entity-parser/discuss/575416/C%2B%2B-two-pointers-O(n)-or-O(1)
//Runtime: 196 ms, faster than 93.55% of C++ online submissions for HTML Entity Parser.
//Memory Usage: 16.3 MB, less than 100.00% of C++ online submissions for HTML Entity Parser.
class Solution {
public:
    string entityParser(string text) {
        map<string, char> entityMap = {
            {"&quot;" , '\"'},
            {"&apos;",  '\''}, 
            {"&amp;" , '&'}, 
            {"&gt;" , '>'}, 
            {"&lt;" , '<'}, 
            {"&frasl;" , '/'}
            };
        
        int slow = 0;
        map<string, char>::iterator it;
        
        //it ends when we examine the whole string using "fast"
        for (int fast = 0, lastAnd = 0; fast < text.size(); ++fast, ++slow) {
            text[slow] = text[fast];
            
            if (text[slow] == '&')
                lastAnd = slow; //will be used when we meet ';'
            
            if (text[slow] == ';') {
                // cout << text << " " << lastAnd << " " << slow << endl;
                if((it = entityMap.find(text.substr(lastAnd, slow - lastAnd + 1))) != entityMap.end()){
                    //suppose we meet "&gt;", now we will write '>' in the position of '&'
                    slow = lastAnd;
                    //modify the "text" in-place
                    text[slow] = it->second;
                    
                }
                /*an '&' can be used only once, 
                here we move lastAnd forward to 
                avoid the last '&' be used next time
                Example: "&amp;amp;"
                */
                lastAnd = slow + 1;
            }
        }
        
        //now "slow" is the index just after last write
        text.resize(slow);
        return text;
    }
};

//Two pointer + Trie
//https://leetcode.com/problems/html-entity-parser/discuss/575416/C%2B%2B-two-pointers-O(n)-or-O(1)
//Runtime: 180 ms, faster than 95.80% of C++ online submissions for HTML Entity Parser.
//Memory Usage: 18 MB, less than 100.00% of C++ online submissions for HTML Entity Parser.
//time: O(N)
class TrieNode{
public:
    vector<TrieNode*> children;
    char mappedSymbol;
    
    TrieNode(){
        children = vector<TrieNode*>(26, nullptr);
        mappedSymbol = '\0';
    }
};

class Trie{
public:
    TrieNode* root;
    
    Trie(){
        root = new TrieNode();
    };
    
    void add(string word, char symbol){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->children[c-'a'] == nullptr){
                cur->children[c-'a'] = new TrieNode();
            }
            cur = cur->children[c-'a'];
        }
        //the trie contains the info mapping by itself
        cur->mappedSymbol = symbol;
    };
    
    char search(string word){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->children[c-'a'] == nullptr)
                return '\0';
            cur = cur->children[c-'a'];
        }
        return cur->mappedSymbol;
    };
};

class Solution {
public:
    string entityParser(string text) {
        map<string, char> entityMap = {
            {"&quot;" , '\"'},
            {"&apos;",  '\''}, 
            {"&amp;" , '&'}, 
            {"&gt;" , '>'}, 
            {"&lt;" , '<'}, 
            {"&frasl;" , '/'}
            };
        
        int slow = 0;
        map<string, char>::iterator it;
        Trie* trie = new Trie();
        
        for(it = entityMap.begin(); it != entityMap.end(); it++){
            //remove key's head's & and tail's ;
            // cout << it->first.substr(1, it->first.size()-2) << endl;
            trie->add(it->first.substr(1, it->first.size()-2), it->second);
        }
        
        for (int fast = 0, lastAnd = 0; fast < text.size(); ++fast, ++slow) {
            text[slow] = text[fast];
            
            if (text[slow] == '&')
                lastAnd = slow;
            
            if (text[slow] == ';') {
                // cout << text << " " << lastAnd << " " << slow << endl;
                char c;
                if((c = trie->search(text.substr(lastAnd+1, slow-1-lastAnd))) != '\0'){
                    // cout << text.substr(lastAnd+1, slow-1-lastAnd) << ", " << c << endl;
                    slow = lastAnd;
                    text[slow] = c;
                    
                }
                lastAnd = slow + 1;
            }
        }
        
        text.resize(slow);
        return text;
    }
};
