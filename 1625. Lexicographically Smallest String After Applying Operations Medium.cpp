//dfs
//but the traverse is incomplete
//WA
//43 / 80 test cases passed.
/*
"31"
4
1
Expected: "11"
*/
class Solution {
public:
    int n;
    unordered_set<string> visited;
    unordered_map<string, string> memo;
    
    string add(string& s, int a){
        string ret = s;
        for(int i = 1; i < n; i+=2){
            ret[i] = '0'+(ret[i]-'0'+a)%10;
        }
        return ret;
    }
    
    string rotate(string& s, int b){
        string ret = s;
        
        ret = s.substr(b) + s.substr(0, b);
        
        return ret;
    }
    
    string dfs(string& s, int& a, int& b){
        if(memo.find(s) != memo.end()){
            // cout << "memo" << endl;
            return memo[s];
        }else if(visited.find(s) != visited.end()){
            //to jump out of the loop!
            return "aaaa";
        }else{
            visited.insert(s);
            string sadd = add(s, a);
            string srot = rotate(s, b);
            
            // cout << s << ", add: " << sadd << ", rot: " << srot << endl;
            
            //stop condition
            if(sadd >= s && srot >= s){
                memo[s] = s;
                // cout << s << " is minimum" << endl;
                return memo[s];
            }
            
            memo[s] = min(dfs(sadd, a, b), dfs(srot, a, b));
            
            // cout << s << " -> " << memo[s] << endl;
            return memo[s];
        }
    }
    
    string findLexSmallestString(string s, int a, int b) {
        n = s.size();
        
        return dfs(s, a, b);
    }
};

//dfs, corrected from above
//Runtime: 592 ms, faster than 29.07% of C++ online submissions for Lexicographically Smallest String After Applying Operations.
//Memory Usage: 169.2 MB, less than 5.03% of C++ online submissions for Lexicographically Smallest String After Applying Operations.
class Solution {
public:
    int n;
    unordered_set<string> visited;
    unordered_map<string, string> memo;
    
    string add(string& s, int a){
        string ret = s;
        for(int i = 1; i < n; i+=2){
            ret[i] = '0'+(ret[i]-'0'+a)%10;
        }
        return ret;
    }
    
    string rotate(string& s, int b){
        string ret = s;
        
        ret = s.substr(b) + s.substr(0, b);
        
        return ret;
    }
    
    string dfs(string& s, int& a, int& b){
        if(memo.find(s) != memo.end()){
            // cout << "memo" << endl;
            return memo[s];
        }else if(visited.find(s) != visited.end()){
            //to jump out of the loop!
            return "aaaa";
        }else{
            visited.insert(s);
            string sadd = add(s, a);
            string srot = rotate(s, b);
            
            // cout << s << ", add: " << sadd << ", rot: " << srot << endl;
            
            memo[s] = min({s, dfs(sadd, a, b), dfs(srot, a, b)});
            
            // cout << s << " -> " << memo[s] << endl;
            return memo[s];
        }
    }
    
    string findLexSmallestString(string s, int a, int b) {
        n = s.size();
        
        return dfs(s, a, b);
    }
};

//dfs
//https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/discuss/899489/Basic-DFS-Brute-force-or-This-kind-of-questions-DFS
//no early stop make it correct?
//Runtime: 308 ms, faster than 71.01% of C++ online submissions for Lexicographically Smallest String After Applying Operations.
//Memory Usage: 91.9 MB, less than 5.13% of C++ online submissions for Lexicographically Smallest String After Applying Operations.
class Solution {
public:
    int n, a, b;
    unordered_set<string> visited;
    string ans;
    
    string add(string& s){
        string ret = s;
        for(int i = 1; i < n; i+=2){
            ret[i] = '0'+(ret[i]-'0'+a)%10;
        }
        return ret;
    }
    
    string rotate(string& s){
        string ret = s;
        
        ret = s.substr(b) + s.substr(0, b);
        
        return ret;
    }
    
    void dfs(string s){
        if(visited.find(s) != visited.end()) return;
        
        visited.insert(s);
        ans = min(ans, s);
        
        dfs(add(s));
        dfs(rotate(s));
    }
    
    string findLexSmallestString(string s, int a, int b) {
        n = s.size();
        this->a = a;
        this->b = b;
        ans = "aaaa";
        dfs(s);
        return ans;
    }
};
