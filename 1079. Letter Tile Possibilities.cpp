//Runtime: 120 ms, faster than 17.63% of C++ online submissions for Letter Tile Possibilities.
//Memory Usage: 31.3 MB, less than 100.00% of C++ online submissions for Letter Tile Possibilities.

class Solution {
public:
    set<string> lastCombs, curCombs, allCombs;
    map<char, int> charCount;
        
    void genCombs(string& tiles, int N){
        curCombs.clear();
        if(N == 1){
            for(map<char, int>::iterator it = charCount.begin(); it!=charCount.end(); it++){
                //string(1, c): convert char 'c' to string
                curCombs.insert(string(1, it->first));
                allCombs.insert(string(1, it->first));
            }
        }else{
            //construct curCombs from lastCombs by appending one char after them
            for(string lastComb : lastCombs){
                //choose the char to append
                for(map<char, int>::iterator it = charCount.begin(); it!=charCount.end(); it++){
                    char c = it->first;
                    //check if we still have that char
                    if(count(lastComb.begin(), lastComb.end(), c) < charCount[c]){
                        string comb = lastComb + c;
                        curCombs.insert(comb);
                        allCombs.insert(comb);
                    }
                }
            }
        }
        lastCombs = curCombs;
    }
    
    int numTilePossibilities(string tiles) {
        for(char c : tiles){
            if(charCount.find(c) == charCount.end()){
                charCount[c] = 1;
            }else{
                charCount[c]++;
            }
        }
        
        for(int i = 1; i <= tiles.size(); i++){
            genCombs(tiles, i);
            // cout << i << endl;
            // for(string s : lastCombs){
            //     cout << s << " ";
            // }
            // cout << endl;
        }
        
        return allCombs.size();
    }
};
