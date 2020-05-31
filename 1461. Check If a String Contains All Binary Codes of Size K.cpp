//Runtime: 1648 ms, faster than 16.67% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
//Memory Usage: 60.1 MB, less than 100.00% of C++ online submissions for Check If a String Contains All Binary Codes of Size K.
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        set<string> codes;
        
        for(int i = 0; i+k-1 < s.size(); i++){
            codes.insert(s.substr(i, k));
        }
        
        return codes.size() == pow(2, k);
    }
};
