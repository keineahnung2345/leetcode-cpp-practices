//backtracking
//TLE
//126 / 200 test cases passed.
class Solution {
public:
    string ans;
    
    void backtrack(int n, int k, string& s, vector<bool>& used, int& seq){
        if(s.size() == n){
            // cout << s << ", " << seq << endl;
            if(seq == k){
                ans = s;
            }
            ++seq;
        }else{
            for(int i = 0; i < n; ++i){
                if(!used[i]){
                    s += (i+1+'0');
                    used[i] = true;
                    backtrack(n, k, s, used, seq);
                    s.pop_back();
                    used[i] = false;
                }
                if(ans != "") break;
            }
        }
    }
    
    string getPermutation(int n, int k) {
        string s = "";
        vector<bool> used(n, false);
        int seq = 1;
        backtrack(n, k, s, used, seq);
        return ans;
    }
};

//backtracking + math
//Runtime: 4 ms, faster than 48.53% of C++ online submissions for Permutation Sequence.
//Memory Usage: 5.9 MB, less than 83.89% of C++ online submissions for Permutation Sequence.
class Solution {
public:
    string ans;
    
    vector<int> facts;
    
    void backtrack(int n, int k, string& s, vector<bool>& used, int& seq){
        if(s.size() == n){
            // cout << s << ", " << seq << endl;
            if(seq == k){
                ans = s;
            }
            ++seq;
        }else if(seq + facts[n-s.size()-1] < k){
            //skip the permutations formed by the remaining n-s.size() chars
            seq += facts[n-s.size()-1];
        }else{
            for(int i = 0; i < n; ++i){
                if(!used[i]){
                    s += (i+1+'0');
                    used[i] = true;
                    backtrack(n, k, s, used, seq);
                    s.pop_back();
                    used[i] = false;
                }
                if(ans != "") break;
            }
        }
    }
    
    string getPermutation(int n, int k) {
        string s = "";
        vector<bool> used(n, false);
        int seq = 1;
        
        facts = vector<int>(n);
        facts[0] = 1;
        for(int i = 2; i <= n; ++i){
            facts[i-1] = facts[i-2] * i;
        }
        
        backtrack(n, k, s, used, seq);
        return ans;
    }
};
