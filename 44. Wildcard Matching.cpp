//recursion
//TLE
//939 / 1809 test cases passed.
class Solution {
public:
    bool isMatch(string s, string p) {
        if(p.size() == 0) return s.size() == 0;

        bool first_match = (s.size() > 0) && (p[0] == s[0] || p[0] == '?' || p[0] == '*');

        if(p[0] == '*'){
            return first_match && isMatch(s.substr(1), p) ||
                isMatch(s, p.substr(1));
        }else{
            //includes the case when p[0] is equal to '?'
            return first_match && isMatch(s.substr(1), p.substr(1));
        }
    }
};

//recursion + memorization
//Runtime: 68 ms, faster than 58.99% of C++ online submissions for Wildcard Matching.
//Memory Usage: 28 MB, less than 11.54% of C++ online submissions for Wildcard Matching.
class Solution {
public:
    vector<vector<int>> memo;
    string s, p;
    
    bool isMatch(int i, int j){
        //p empty
        if(j == p.size()) return i == s.size();
        
        if(memo[i][j] != -1){
            return memo[i][j];
        }
        
        bool first_match = (i < s.size()) && (p[j] == s[i] || p[j] == '?' || p[j] == '*');
        
        if(p[j] == '*'){
            memo[i][j] = (first_match && isMatch(i+1, j)) || isMatch(i, j+1);
        }else{
            memo[i][j] = first_match && isMatch(i+1, j+1);
        }
        
        return memo[i][j];
    }
    
    bool isMatch(string s, string p) {
        this->s = s;
        this->p = p;
        int m = s.size(), n = p.size();
        memo = vector<vector<int>>(m+1, vector(n+1, -1));
        
        return isMatch(0, 0);
    }
};

//DP
//Runtime: 228 ms, faster than 27.30% of C++ online submissions for Wildcard Matching.
//Memory Usage: 11.1 MB, less than 46.15% of C++ online submissions for Wildcard Matching.
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1, vector(n+1, false));
        
        //base case: both empty
        dp[m][n] = true;
        /*
        dp[i][n] is always false for i not equal to m,
        because at that time, s is not empty and p is empty
        */
        
        for(int i = m; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                bool first_match = (i < m) && (p[j] == s[i] || p[j] == '?' || p[j] == '*');
                
                if(p[j] == '*'){
                    dp[i][j] = (first_match && dp[i+1][j]) || dp[i][j+1];
                }else{
                    dp[i][j] = first_match && dp[i+1][j+1];
                }
            }
        }
        
        return dp[0][0];
    }
};

//greedy
//https://leetcode.com/problems/wildcard-matching/discuss/17810/Linear-runtime-and-constant-space-solution
//Runtime: 8 ms, faster than 95.12% of C++ online submissions for Wildcard Matching.
//Memory Usage: 6.6 MB, less than 100.00% of C++ online submissions for Wildcard Matching.
class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0;
        int m = s.size(), n = p.size();
        int last_match = -1, starj = -1;
        
        while(i < m){
            // cout << s[i] << ", " << ((j < n) ? p[j] : ' ') << endl;
            // cout << i << ", " << j << ", starj: " << starj << ", last_match: " << last_match << endl;
            if(j < n && (p[j] == s[i] || p[j] == '?')){
                //match one
                i++;
                j++;
            }else if(j < n && p[j] == '*'){
                //greedily match one
                starj = j;
                last_match = i;
                j++;
                //why not i++?
            }else if(starj != -1){
                //not match, fallback to use previous found '*'
                last_match++; //the previous star now matches s[last_match+1]
                i = last_match; //?
                j = starj+1; //now start from the next char of previous '*'
            }else{
                //current char not match, and cannot fallback
                // cout << endl;
                return false;
            }
        }
        // cout << endl;
        
        //if the remaining char in p are all '*', we think it's a match
        return p.substr(j) == string(p.size()-j, '*');
    }
};
