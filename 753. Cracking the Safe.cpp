//backtracking
//https://leetcode.com/problems/cracking-the-safe/discuss/153039/DFS-with-Explanations
//Runtime: 12 ms, faster than 85.74% of C++ online submissions for Cracking the Safe.
//Memory Usage: 10.2 MB, less than 40.89% of C++ online submissions for Cracking the Safe.
class Solution {
public:
    int n, k, total;
    
    bool backtrack(string& ans, unordered_set<string>& visited){
        if(visited.size() == total){
            return true;
        }else{
            for(int i = 0; i < k; ++i){
                ans.push_back('0'+i);
                string cur = ans.substr(ans.size()-n);
                if(visited.find(cur) == visited.end()){
                    visited.insert(cur);
                    if(backtrack(ans, visited)) return true;
                    visited.erase(cur);
                }
                ans.pop_back();
            }
            return false;
        }
    }
    
    string crackSafe(int n, int k) {
        this->n = n;
        this->k = k;
        total = pow(k, n);
        
        string ans(n, '0');
        unordered_set<string> visited = {ans};
        
        backtrack(ans, visited);
        
        return ans;
    }
};
