//Runtime: 12 ms, faster than 51.64% of C++ online submissions for Combination Sum II.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for Combination Sum II.
class Solution {
public:
    int tgt;
    
    void backtrack(vector<vector<int>>& combs, vector<int>& comb, vector<int>& candidates, vector<bool>& used, int start){
        int cursum = accumulate(comb.begin(), comb.end(), 0);
        if(cursum > tgt){
        }else if(cursum == tgt){
            combs.push_back(comb);
        }else{
            for(int i = start; i < candidates.size(); i++){
                if(used[i]) continue;
                //if i-1 not used and we use i now, then i acts just as i-1
                if(i > 0 && candidates[i] == candidates[i-1] && !used[i-1]) continue;
                comb.push_back(candidates[i]);
                used[i] = true;
                backtrack(combs, comb, candidates, used, i+1);
                comb.pop_back();
                used[i] = false;
            }
        }
    };
    
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int N = candidates.size();
        vector<vector<int>> combs;
        vector<int> comb;
        vector<bool> used(N, false);
        tgt = target;
        
        sort(candidates.begin(), candidates.end());
        
        backtrack(combs, comb, candidates, used, 0);
        
        return combs;
    }
};
