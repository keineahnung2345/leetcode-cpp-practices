/*
WA
success:
["w","wo","wor","worl","world"]
["a", "banana", "app", "appl", "ap", "apply", "apple"]
["m","mo","moc","moch","mocha","l","la","lat","latt","latte","c","ca","cat"]
["yo","ew","fc","zrc","yodn","fcm","qm","qmo","fcmz","z","ewq","yod","ewqz","y"]
["ogz","eyj","e","ey","hmn","v","hm","ogznkb","ogzn","hmnm","eyjuo","vuq","ogznk","og","eyjuoi","d"]

fail:
["rac","rs","ra","on","r","otif","o","onpdu","rsf","rs","ot","oti","racy","onpd"]
*/
class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
        string acc = words[0].size() == 1 ? words[0] : "-";
        vector<string> candidates;
        for(int i = 1; i < words.size(); i++){
            //the accumulation process doesn't start or it ends
            if(acc == "-" || words[i].size() <= acc.size()){
                if(acc != "-") candidates.push_back(acc);
                acc = words[i].size() == 1 ? words[i] : "-";
            }
            if(words[i].size() == acc.size()+1 && words[i].rfind(acc, 0) == 0){
                acc = words[i];
            }
        }
        candidates.push_back(acc);
        copy(candidates.begin(), candidates.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
        
        sort(candidates.begin(), candidates.end(), 
             [](const string& a, const string& b) -> bool{
                 //first sort by length and then by lexicographical order
                 //if length are the same, check their lexicographical order
                 //ow, directly sort by their length
                 return (a.size() == b.size()) ? a < b : a.size() > b.size();
             }
        );
        return candidates[0];
    }
};

/*
Hint 1
For every word in the input list, we can check whether all prefixes of that word are in the input list by using a Set.
*/
//Runtime: 540 ms, faster than 5.02% of C++ online submissions for Longest Word in Dictionary.
//Memory Usage: 29.4 MB, less than 30.00% of C++ online submissions for Longest Word in Dictionary.
class Solution {
public:
    string longestWord(vector<string>& words) {
        vector<string> candidates;
        
        for(string word : words){
            bool valid = true;
            for(int i = word.size() - 1; i >= 1; i--){
                string prefix = word.substr(0, i);
                // cout << prefix << endl;
                if(find(words.begin(), words.end(), prefix) == words.end()){
                    valid = false;
                    break;
                }
            }
            if(valid)candidates.push_back(word);
        }
        // cout << candidates.size() << endl;
        // copy(candidates.begin(), candidates.end(), ostream_iterator<string>(cout, " "));

        sort(candidates.begin(), candidates.end(), 
             [](const string& a, const string& b){
                 return a.size() == b.size() ? a < b : a.size() > b.size();
             }
            );
        return candidates[0];
    }
};

//Trie + Depth-First Search
//Runtime: 84 ms, faster than 30.96% of C++ online submissions for Longest Word in Dictionary.
//Memory Usage: 25.6 MB, less than 50.00% of C++ online submissions for Longest Word in Dictionary.
class Node {
public:
    Node(char c){
        this->c = c;
    }

    char c;
    int end; //default is 0
    map<char, Node*> children;
};

class Trie {
public:
    Trie() {
        root = new Node('0');
    }
    
    void insert(string word, int index) {
        Node* cur = root;
        //put the word into the tree vertically
        for(char c : word){
            if(!cur->children[c]){
                cur->children[c] = new Node(c);
            }
            cur = cur->children[c];
        }
        //cur->end - 1 is the index for the input array
        //mark this node comes from input array
        cur->end = index;
    }
    
    string dfs(){
        string ans = "";
        stack<Node*> stk;
        stk.push(root);
        while(!stk.empty()){
            Node* node = stk.top(); stk.pop();
            //root node's end is 0
            //only want node from input array and root, not a non-leaf node
            if(node->end > 0 || node == root){
                //node from input array
                if(node != root){
                    //node->end -1 is the index for the input array
                    string word = words[node->end -1];
                    if(word.size() > ans.size() || 
                      word.size() == ans.size() && word < ans){
                        ans = word;
                    }                    
                }
                for(auto it = node->children.begin(); it != node->children.end(); it++){
                    stk.push(it->second);
                }
            }
        }
        return ans;
    }

    Node* root;
    vector<string> words;
};

class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        int index = 0;
        //put every word in a trie(a prefix tree)
        for(string word : words){
            trie.insert(word, ++index);
        }
        trie.words = words;
        //dfs, only searching nodes that ended a word
        return trie.dfs();
    }
};

//set
//https://leetcode.com/problems/longest-word-in-dictionary/discuss/109114/JavaC%2B%2B-Clean-Code
//Runtime: 52 ms, faster than 78.87% of C++ online submissions for Longest Word in Dictionary.
//Memory Usage: 18 MB, less than 80.00% of C++ online submissions for Longest Word in Dictionary.
class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> built;
        string ans;
        sort(words.begin(), words.end());
        for(string word : words){
            if(word.size() == 1 || built.find(word.substr(0, word.size()-1)) != built.end()){
                //check both length and their lexicographical order
                ans = (word.size() == ans.size()) ? (word < ans ? word : ans) : (word.size() > ans.size() ? word : ans);
                //this works because the vector "words" is sorted
                // ans = word.size() > ans.size() ? word : ans;
                //only record the word can be built from one char into the set,
                //for those word built from 2 or more chars, not record them
                built.insert(word);
            }
        }
        return ans;
    }
};
