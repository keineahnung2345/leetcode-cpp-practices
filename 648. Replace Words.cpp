//Approach #1: Prefix Hash
//Runtime: 388 ms, faster than 10.41% of C++ online submissions for Replace Words.
//Memory Usage: 275.6 MB, less than 14.29% of C++ online submissions for Replace Words.
//time: O(sigma(wi^2)), wi is the length of ith word
//space: O(N), N is the length of sentence
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        set<string> dictset;
        string ans = "";
        istringstream is(sentence);
        string token;
        
        //convert dict from string to set
        for(string& word : dict){
            dictset.insert(word);
        }
        
        //iterate through sentence
        while(is >> token){
            //create "prefix" from current token
            string prefix = "";
            for(int i = 1; i <= token.size(); i++){
                prefix = token.substr(0, i);
                //find prefix in dictset
                if(dictset.find(prefix) != dictset.end()){
                    break;
                }
            }
            //add space between tokens
            if(ans.size() > 0){
                ans += " ";
            }
            // cout << token << " " << prefix << endl;
            ans += prefix;
        };
        
        return ans;
    }
};

class TrieNode {
public:
    vector<TrieNode*> children;
    string word;
    TrieNode(){
        children = vector<TrieNode*>(26, NULL);
        word = "";
    }
};

//Runtime: 68 ms, faster than 60.86% of C++ online submissions for Replace Words.
//Memory Usage: 55.8 MB, less than 28.57% of C++ online submissions for Replace Words.
//time: O(N), length of sentence 
//space: O(N), size of trie
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        TrieNode* root = new TrieNode();
        //build trie, mark a node as end by setting the attribute "word"
        for(string& word : dict){
            TrieNode* cur = root;
            for(char c : word){
                if(cur->children[c-'a'] == NULL){
                    cur->children[c-'a'] = new TrieNode();
                }
                cur = cur->children[c-'a'];
            }
            cur->word = word;
        }
        
        string ans;
        istringstream is(sentence);
        string token;
        
        while(is >> token){
            //find current "token" in the trie
            TrieNode* cur = root;
            for(char c : token){
                //stop search while coming to leaf or finding a "word" that matches it
                if(cur->children[c-'a'] == NULL || cur->word != ""){
                    break;
                }
                cur = cur->children[c-'a'];
            }
            if(ans.size() > 0){
                ans += " ";
            }
            ans += (cur->word != "") ? cur->word : token;
        }
        
        return ans;
    }
};
