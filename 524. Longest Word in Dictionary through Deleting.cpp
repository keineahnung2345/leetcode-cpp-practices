//Runtime: 88 ms, faster than 64.35% of C++ online submissions for Longest Word in Dictionary through Deleting.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Longest Word in Dictionary through Deleting.

class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end(), [](const string& a, const string& b){
            return (a.size() == b.size()) ? a < b : a.size() > b.size();
        });
        
        for(string& word : d){
            int wi = 0, si = 0;
            while(wi < word.size() && si < s.size()){
                if(word[wi] == s[si]){
                    wi++;
                    si++;
                }else{
                    si++;
                }
            }
            // cout << wi << "/" << word.size() << " " << si << "/" << s.size() << endl;
            if(wi == word.size()){
                return word;
            }
        }
        
        return "";
    }
};
