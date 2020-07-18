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

//recursion + memorization
//Runtime: 8 ms, faster than 52.84% of C++ online submissions for Interleaving String.
//Memory Usage: 6.8 MB, less than 39.08% of C++ online submissions for Interleaving String.
class Solution {
public:
    vector<vector<int>> memo;
    
    bool dfs(string& s1, string& s2, string& s3, int i, int j){
        // cout << i << ", " << j << endl;
        if(i+j == s1.size() + s2.size()){
            return true;
        }
        
        if(memo[i][j] != -1){
            return memo[i][j];
        }
        
        if(i < s1.size() && s1[i] == s3[i+j]){
            if(dfs(s1, s2, s3, i+1, j)) return memo[i][j] = true;
        }
        if(j < s2.size() && s2[j] == s3[i+j]){
            if(dfs(s1, s2, s3, i, j+1)) return memo[i][j] = true;
        }
        
        return memo[i][j] = false;
    };
    
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int m = s1.size(), n = s2.size();
        memo = vector<vector<int>>(m+1, vector<int>(n+1, -1));
        return dfs(s1, s2, s3, 0, 0);
    }
};
