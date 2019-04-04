//Runtime: 24 ms, faster than 8.57% of C++ online submissions for Isomorphic Strings.
//Memory Usage: 9.3 MB, less than 7.37% of C++ online submissions for Isomorphic Strings.

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) return false;
        
        //need to ensure 1-to-1 mapping,
        //so we need to maps
        map<char, char> m, im;
        set<char> values;
        for(int i = 0; i < s.size(); i++){
            if(m.find(s[i]) == m.end()){
                m[s[i]] = t[i];
            }else if(m[s[i]] != t[i]){
                return false;
            }
            if(im.find(t[i]) == im.end()){
                im[t[i]] = s[i];
            }else if(im[t[i]] != s[i]){
                return false;
            }
        }
        
        return true;
    }
};

//https://leetcode.com/problems/isomorphic-strings/discuss/57796/My-6-lines-solution
/**
indirect mapping
**/

//Runtime: 16 ms, faster than 36.56% of C++ online submissions for Isomorphic Strings.
//Memory Usage: 9 MB, less than 32.11% of C++ online submissions for Isomorphic Strings.

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> ms(128, 0), mt(128, 0);
        
        for(int i = 0; i < s.size(); i++){
            if(ms[s[i]] != mt[t[i]]){
                return false;
            }
            ms[s[i]] = i+1;
            mt[t[i]] = i+1;
        }
        
        return true;
    }
};
