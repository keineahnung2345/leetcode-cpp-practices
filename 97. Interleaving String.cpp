//recursion
//TLE
//99 / 101 test cases passed.
//time: O(2^(m+n)), space: O(m+n)
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

//recursion + memorization, early stopping
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Interleaving String.
//Memory Usage: 7 MB, less than 33.14% of C++ online submissions for Interleaving String.
//time: O(m*n), space: O(m*n)
class Solution {
public:
    vector<vector<int>> memo;
    
    bool dfs(string& s1, string& s2, string& s3, int i, int j){
        // cout << i << ", " << j << endl;
        if(i+j == s1.size() + s2.size()){
            return true;
        }else if(i == s1.size()){
            return s2.substr(j) == s3.substr(i+j);
        }else if(j == s2.size()){
            return s1.substr(i) == s3.substr(i+j);
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
        memo = vector<vector<int>>(m, vector<int>(n, -1));
        return dfs(s1, s2, s3, 0, 0);
    }
};

//DP
//Runtime: 8 ms, faster than 52.84% of C++ online submissions for Interleaving String.
//Memory Usage: 6.7 MB, less than 49.81% of C++ online submissions for Interleaving String.
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int m = s1.size(), n = s2.size();
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        
        for(int i = m; i >= 0; --i){
            for(int j = n; j >= 0; --j){
                if(i == m && j == n){
                    dp[i][j] = true;
                }else{
                    if(s1[i] == s3[i+j] && dp[i+1][j]){
                        dp[i][j] = true;
                        continue;
                    }
                    if(s2[j] == s3[i+j] && dp[i][j+1]){
                        dp[i][j] = true;
                        continue;
                    }
                    dp[i][j] = false;
                }
            }
        }
        
        return dp[0][0];
    }
};

//DP, bottom up
//Runtime: 8 ms, faster than 52.84% of C++ online submissions for Interleaving String.
//Memory Usage: 6.5 MB, less than 68.01% of C++ online submissions for Interleaving String.
//time: O(m*n), space: O(m*n)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int m = s1.size(), n = s2.size();
        /*
        dp[i][j]: seen i char in s1, j char in s2,
        so we are currently looking at s1[i-1] and s2[j-1]
        */
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        
        for(int i = 0; i <= m; ++i){
            for(int j = 0; j <= n; ++j){
                if(i == 0 && j == 0){
                    dp[i][j] = true;
                }else if(i == 0){
                    /*
                    after dp[0][j], we have seen
                    0 chars from s1 and j chars from s2,
                    so it means we are looking at s2[j-1]
                    */
                    dp[i][j] = (s2[j-1] == s3[i+j-1]) && dp[i][j-1];
                }else if(j == 0){
                    dp[i][j] = (s1[i-1] == s3[i+j-1]) && dp[i-1][j];
                }else{
                    dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j])
                     || (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

//O(N) DP
//Runtime: 4 ms, faster than 84.58% of C++ online submissions for Interleaving String.
//Memory Usage: 6.3 MB, less than 83.14% of C++ online submissions for Interleaving String.
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int m = s1.size(), n = s2.size();
        vector<vector<bool>> dp(2, vector<bool>(n+1, false));
        
        for(int i = m; i >= 0; --i){
            for(int j = n; j >= 0; --j){
                if(i == m && j == n){
                    dp[i&1][j] = true;
                }else{
                    if(s1[i] == s3[i+j] && dp[(i+1)&1][j]){
                        dp[i&1][j] = true;
                        continue;
                    }
                    if(s2[j] == s3[i+j] && dp[i&1][j+1]){
                        dp[i&1][j] = true;
                        continue;
                    }
                    dp[i&1][j] = false;
                }
            }
        }
        
        return dp[0][0];
    }
};

//1-D DP
//Runtime: 4 ms, faster than 84.58% of C++ online submissions for Interleaving String.
//Memory Usage: 6.1 MB, less than 94.44% of C++ online submissions for Interleaving String.
//time: O(m*n), space: O(n)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        int m = s1.size(), n = s2.size();
        
        /*
        dp[i][j] depends on dp[i-1][j] and dp[i][j-1]
        for dp[i-1][j], since we visit i from 0 to m, so it's safe
        for dp[i][j-1], since we visit j from 0 to n, so it's safe
        */
        vector<bool> dp(n+1, false);
        
        for(int i = 0; i <= m; ++i){
            for(int j = 0; j <= n; ++j){
                if(i == 0 && j == 0){
                    dp[j] = true;
                }else if(i == 0){
                    dp[j] = (s2[j-1] == s3[i+j-1]) && dp[j-1];
                }else if(j == 0){
                    dp[j] = (s1[i-1] == s3[i+j-1]) && dp[j];
                }else{
                    dp[j] = (s1[i-1] == s3[i+j-1] && dp[j])
                     || (s2[j-1] == s3[i+j-1] && dp[j-1]);
                }
            }
        }
        
        return dp[n];
    }
};
