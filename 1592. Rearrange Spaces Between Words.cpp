//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Rearrange Spaces Between Words.
//Memory Usage: 6.2 MB, less than 71.55% of C++ online submissions for Rearrange Spaces Between Words.
class Solution {
public:
    string reorderSpaces(string text) {
        int spaces = 0;
        string word = "";
        vector<string> words;
        
        int n = text.size();
        
        for(int i = 0; i < n; ++i){
            if(text[i] != ' ') word += text[i];
            if(text[i] == ' ') ++spaces;
            
            if(text[i] == ' ' || i == n-1){
                if(!word.empty()){
                    words.push_back(word);
                    word = "";
                }
            }
        }
        
        // cout << spaces << endl;
        // cout << words.size() << endl;
        
        string ans = "";
        int k = (words.size() != 1) ? spaces/(words.size()-1) : spaces;
        n = words.size();
        for(int i = 0; i < n; ++i){
            if(i < n-1){
                ans += (words[i] + string(k, ' '));
                spaces -= k;
            }else{
                ans += (words[i] + string(spaces, ' '));
            }
            // cout << ans << " " << spaces << endl;
        }
        
        return ans;
    }
};
