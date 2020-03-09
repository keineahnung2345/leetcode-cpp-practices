//Runtime: 12 ms, faster than 81.07% of C++ online submissions for Combination Sum.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Combination Sum.

class Solution {
public:
    int tgt;
    
    void backtrack(vector<vector<int>>& combs, vector<int>& comb, vector<int>& candidates, int start){
        int cursum = accumulate(comb.begin(), comb.end(), 0);
        // cout << "cursum: " << cursum << endl;
        if(cursum > tgt){
        }else if(cursum == tgt){
            combs.push_back(comb);
        }else{
            //we may reuse the last element
            for(int i = max(0,start-1); i < candidates.size(); i++){
                comb.push_back(candidates[i]);
                // cout << i << endl;
                backtrack(combs, comb, candidates, i+1);
                comb.pop_back();
            }
        }
    };
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> combs;
        vector<int> comb;
        tgt = target;
        
        backtrack(combs, comb, candidates, 0);
        
        return combs;
    }
};
