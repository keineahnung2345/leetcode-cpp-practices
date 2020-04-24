//TLE
//22 / 24 test cases passed.
class Solution {
public:
    string lastSubstring(string s) {
        int maxIdx = 0;
        char maxC = '\0';
        for(int i = 0; i < s.size(); i++){
            if(s[i] > maxC){
                maxIdx = i;
                maxC = s[i];
            }
        }
        
        vector<string> candidates;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == maxC){
                candidates.push_back(s.substr(i));
            }
        }
        
        // cout << candidates.size() << endl;
        
        // sort(candidates.begin(), candidates.end(),
        //            [](const string& a, const string& b){
        //                return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
        //            });
        
        nth_element(candidates.begin(), candidates.begin()+candidates.size()-1, candidates.end(),
                   [](const string& a, const string& b){
                       return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
                   });
        
        return candidates[candidates.size()-1];
    }
};
