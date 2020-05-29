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

