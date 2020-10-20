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
