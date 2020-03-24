//TLE
//31 / 32 test cases passed.
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        set<string> ans;
        
        for(int i = 0; i + 10 <= s.size(); i++){
            string pattern = s.substr(i, 10);
            size_t found = s.find(pattern, i+1);
            if(found != string::npos){
                ans.insert(pattern);
            }
        }
        
        return vector<string>(ans.begin(), ans.end());
    }
};
