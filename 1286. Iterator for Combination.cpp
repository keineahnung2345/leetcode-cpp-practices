//Runtime: 20 ms, faster than 27.38% of C++ online submissions for Iterator for Combination.
//Memory Usage: 13.8 MB, less than 100.00% of C++ online submissions for Iterator for Combination.

class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {
        this->characters = characters;
        this->combinationLength = combinationLength;
        
        for(int i = 0; i < combinationLength; i++){
            comb.push_back(i);
        }
    }
    
    string next() {
        if(!hasNext()){
            return cur;
        }
        string tmp;
        tmp.clear();
        for(int i = 0; i < combinationLength; i++){
            tmp += characters[comb[i]];
        }
        cur = tmp;
        
        //update comb
        bool updated = false;
        //start from tail
        for(int i = combinationLength - 1; i >= 0; i--){
            //if comb[i] is already the last possible character
            if(comb[i] != characters.size() - 1 - (combinationLength - 1 - i)){
                comb[i]++;
                //move the later characters to the just left of current updated position
                for(int j = i+1; j < combinationLength; j++){
                    comb[j] = comb[j-1]+1;
                }
                updated = true;
                break;
            }
        }
        
        return cur;
    }
    
    bool hasNext() {
        return  cur != characters.substr(characters.size() - combinationLength, combinationLength);
    }
    
    vector<int> comb;
    string characters;
    int combinationLength;
    string cur;
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
 
