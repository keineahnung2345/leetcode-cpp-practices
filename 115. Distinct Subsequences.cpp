//backtracking
//TLE
//52 / 63 test cases passed.
class Solution {
public:
    string s, t;
    int ans;
    
    void backtrack(int start, string& cur){
        if(cur.size() == t.size()){
            //here cur == t must hold
            ++ans;
        }else if(cur.size() < t.size() && 
                 cur.size() + s.size() - start >= t.size()){
            //use s[start]
            if(s[start] == t[cur.size()]){
                cur.push_back(s[start]);
                backtrack(start+1, cur);
                cur.pop_back();
            }
            
            //not use s[start]
            backtrack(start+1, cur);
        }
    }
    
    int numDistinct(string s, string t) {
        this->s = s;
        this->t = t;
        ans = 0;
        
        string cur;
        backtrack(0, cur);
        
        return ans;
    }
};

//backtracking + memorization
//Runtime: 476 ms, faster than 8.83% of C++ online submissions for Distinct Subsequences.
//Memory Usage: 113.1 MB, less than 5.01% of C++ online submissions for Distinct Subsequences.
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

class Solution {
public:
    string s, t;
    
    unordered_map<pair<int, string>, int, pair_hash> memo;
    
    int backtrack(int start, string& cur){
        if(memo.find({start, cur}) != memo.end()){
            return memo[{start, cur}];
        }else if(cur.size() == t.size()){
            //here cur == t must hold
            return memo[{start, cur}] = 1;
        }else if(cur.size() < t.size() && 
                 cur.size() + s.size() - start >= t.size()){
            int ret = 0;
            
            //use s[start]
            if(s[start] == t[cur.size()]){
                cur.push_back(s[start]);
                ret += backtrack(start+1, cur);
                cur.pop_back();
            }
            
            //not use s[start]
            ret += backtrack(start+1, cur);
            
            return memo[{start, cur}] = ret;
        }
        
        return 0;
    }
    
    int numDistinct(string s, string t) {
        this->s = s;
        this->t = t;
        
        string cur;
        return backtrack(0, cur);
    }
};

//top-down DP
//actually we don't need to keep the string "cur", because it must be a prefix of "t", so we can simply use the index "ti"
//Runtime: 16 ms, faster than 47.28% of C++ online submissions for Distinct Subsequences.
//Memory Usage: 11.9 MB, less than 5.01% of C++ online submissions for Distinct Subsequences.
class Solution {
public:
    string s, t;
    vector<vector<int>> dp;
    
    int backtrack(int si, int ti){
        if(dp[si][ti] != -1){
            return dp[si][ti];
        }else if(ti == t.size()){
            return dp[si][ti] = 1;
        }else if(ti < t.size() && 
                 ti + s.size() - si >= t.size()){
            int ret = 0;
            
            //use s[si]
            if(s[si] == t[ti]){
                //ti+1: because t[ti] is matched
                ret += backtrack(si+1, ti+1);
            }
            
            //not use s[si]
            ret += backtrack(si+1, ti);
            
            return dp[si][ti] = ret;
        }
        
        return dp[si][ti] = 0;
    }
    
    int numDistinct(string s, string t) {
        this->s = s;
        this->t = t;
        
        dp = vector<vector<int>>(s.size()+1, vector<int>(t.size()+1, -1));
        
        return backtrack(0, 0);
    }
};
