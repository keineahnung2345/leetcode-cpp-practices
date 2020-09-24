//backtracking
//Runtime: 520 ms, faster than 50.80% of C++ online submissions for Split a String Into the Max Number of Unique Substrings.
//Memory Usage: 44.1 MB, less than 49.47% of C++ online submissions for Split a String Into the Max Number of Unique Substrings.
class Solution {
public:
    void backtrack(int cur, string& s, 
       unordered_set<string>& split, int& ans){
        if(cur == s.size()){
            ans = max(ans, (int)split.size());
        }else{
            for(int l = 1; l <= s.size() - cur; ++l){
                if(split.find(s.substr(cur, l)) == split.end()){
                    split.insert(s.substr(cur, l));
                    backtrack(cur+l, s, split, ans);
                    split.erase(s.substr(cur, l));
                }
            }
        }
    }
    
    int maxUniqueSplit(string s) {
        unordered_set<string> split;
        int ans = 0;
        
        backtrack(0, s, split, ans);
        
        return ans;
    }
};
