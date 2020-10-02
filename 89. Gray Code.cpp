//backtracking
//TLE
//4 / 12 test cases passed.
//testcase: 4
class Solution {
public:
    int n;
    vector<int> ans;
    
    void backtrack(vector<int>& perm, vector<bool>& used){
        if(all_of(used.begin(), used.end(), [](const bool& b){return b;})){
            bool valid = true;
            for(int i = 0; i+1 < n; ++i){
                if(__builtin_popcount(perm[i]^perm[i+1]) != 1){
                    valid = false;
                    break;
                }
            }
            if(valid){
                ans = perm;
            }
        }else{
            for(int i = 0; i < n; ++i){
                if(used[i]) continue;
                perm.push_back(i);
                used[i] = true;
                backtrack(perm, used);
                if(!ans.empty()) return;
                perm.pop_back();
                used[i] = false;
            }
        }
    }
    
    vector<int> grayCode(int n) {
        this->n = 1<<n;
        vector<int> perm;
        vector<bool> used(1<<n, false);
        backtrack(perm, used);
        return ans;
    }
};
