//TLE
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(p.size() > s.size()) return vector<int>();
        vector<int> ans;
        
        sort(p.begin(), p.end());
        
        for(int i = 0; i < s.size() - (p.size()-1); i++){
            string s1 = s.substr(i, p.size());
            sort(s1.begin(), s1.end());
            if(s1 == p) ans.push_back(i);
        }
        
        return ans;
    }
};
