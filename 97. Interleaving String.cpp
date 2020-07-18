//recursion
//TLE
//99 / 101 test cases passed.
class Solution {
public:
    bool dfs(string& s1, string& s2, string& s3, int i, int j){
        // cout << i << ", " << j << endl;
        if(i+j == s1.size() + s2.size()){
            return true;
        }
        
        if(i < s1.size() && s1[i] == s3[i+j]){
            if(dfs(s1, s2, s3, i+1, j)) return true;
        }
        if(j < s2.size() && s2[j] == s3[i+j]){
            if(dfs(s1, s2, s3, i, j+1)) return true;
        }
        
        return false;
    };
    
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        return dfs(s1, s2, s3, 0, 0);
    }
};
