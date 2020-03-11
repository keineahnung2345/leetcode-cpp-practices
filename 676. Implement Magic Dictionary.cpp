//Approach #1: Brute Force with Bucket-By-Length [Accepted]
//Runtime: 4 ms, faster than 69.86% of C++ online submissions for Implement Magic Dictionary.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Implement Magic Dictionary.
//S: total letter count, N: dict length, K: length of the word to be searched
//time: O(S) to build, O(NK) to search
//space: O(S)
class MagicDictionary {
public:
    map<int, vector<string>> buckets;
    
    /** Initialize your data structure here. */
    MagicDictionary() {
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for(string& word : dict){
            buckets[word.size()].push_back(word);
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        bool flag = false;
        
        for(string& candidate : buckets[word.size()]){
            int dist = 0;
            for(int i = 0; i < word.size(); i++){
                if(word[i] != candidate[i]){
                    dist++;
                }
                if(dist > 1){
                    break;
                }
            }
            
            if(dist == 1){
                flag = true;
                break;
            }
        }
        
        return flag;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dict);
 * bool param_2 = obj->search(word);
 */
 
//Approach #2: Generalized Neighbors
//Runtime: 4 ms, faster than 69.86% of C++ online submissions for Implement Magic Dictionary.
//Memory Usage: 9.3 MB, less than 66.67% of C++ online submissions for Implement Magic Dictionary.
//wi: length of words[i], K: length of the word to be searched
//time: build: O(sigma(w_i^2)), search: O(K^2)
//space: counter: O(sigma(w_i^2)), neighbors of word to be searched : O(K^2)
class MagicDictionary {
public:
    set<string> dictset;
    map<string, int> counter;
    
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    vector<string> genneighbors(string& word){
        vector<string> neighbors;
        
        for(int i = 0; i < word.size(); i++){
            neighbors.push_back(word.substr(0, i) + "*" + word.substr(i+1));
        }
        
        return neighbors;
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        //counter : record possible neighbors' counts
        for(string& word : dict){
            vector<string> neighbors = genneighbors(word);
            for(string& neighbor : neighbors){
                counter[neighbor]++;
            }
            dictset.insert(word);
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        bool flag = false;
        vector<string> neighbors = genneighbors(word);
        
        for(string& neighbor : neighbors){
            //if word has more than 1 neighbor, then one of them must not be word
            //if word has only 1 neighbor, we need to check whether the neighbor is generated from word itself
            if(counter[neighbor] > 1 || (counter[neighbor] == 1 && dictset.find(word) == dictset.end())){
                flag = true;
                break;
            }
        }
        
        return flag;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dict);
 * bool param_2 = obj->search(word);
 */
