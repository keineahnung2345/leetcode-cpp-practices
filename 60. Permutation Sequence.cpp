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
