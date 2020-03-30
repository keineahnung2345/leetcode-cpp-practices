//KMP & DP memo
//https://leetcode.com/problems/find-all-good-strings/discuss/554806/O(N-*-len(evil))-Solution-with-memorized-DP-and-KMP-algorithm
//TLE
//53 / 53 test cases passed, but took too long.
class Solution {
public:
    int n;
    int m;
    int mod;
    string s1, s2, evil;
    vector<int> lps;
    unordered_map<string, int> memo;
    
    void computeLPSArray(){
        int n = evil.size();
        lps = vector<int>(n, 0);
        
        for(int i = 1, len = 0; i < n; ){
            if(evil[i] == evil[len]){
                len++;
                lps[i] = len;
                i++;
            }else if(len > 0){
                len = lps[len-1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    };
    
    int count(int idx, bool pre1, bool pre2, int preE){
        //we just construct evil
        if(preE == m) return 0;
        //we just construct one valid string
        if(idx == n) return 1;
        
        string hashKey = to_string(idx) + "$" + to_string(pre1) + "$" + to_string(pre2) + "$" + to_string(preE);
        if(memo.find(hashKey) != memo.end()){
            return memo[hashKey];
        }
        
        int total = 0;
        //the first and last possible char of current position
        char first = pre1 ? s1[idx] : 'a';
        char last = pre2 ? s2[idx] : 'z';
        
        for(int i = first-'a'; i <= last-'a'; i++){
            char c = i+'a';
            
            bool _pre1 = pre1 && (first == c);
            bool _pre2 = pre2 && (last == c);
            
            int _preE = preE;
            while(_preE!=0 && c != evil[_preE]){
                _preE = lps[_preE-1];
            }
            if(c == evil[_preE]){
                _preE++;
            }
            
            total += count(idx+1, _pre1, _pre2, _preE);
            total %= mod;
        }
        
        memo[hashKey] = total;
        
        return total;
    };
    
    int findGoodStrings(int n, string s1, string s2, string evil) {
        this->n = n;
        this->s1 = s1;
        this->s2 = s2;
        this->evil = evil;
        this->m = evil.size();
        this->mod = 1e9+7;
        computeLPSArray();
        
        return count(0, true, true, 0);
    }
};
