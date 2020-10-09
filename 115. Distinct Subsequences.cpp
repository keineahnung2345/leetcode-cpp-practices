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
