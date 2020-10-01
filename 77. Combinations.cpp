//backtracking
//Runtime: 36 ms, faster than 73.39% of C++ online submissions for Combinations.
//Memory Usage: 9.3 MB, less than 61.50% of C++ online submissions for Combinations.
class Solution {
public:
    int n, k;
    
    void backtrack(int start, vector<int>& comb, vector<vector<int>>& combs){
        if(comb.size() == k){
            combs.push_back(comb);
        }else{
            for(int i = start; i <= n; ++i){
                comb.push_back(i);
                backtrack(i+1, comb, combs);
                comb.pop_back();
            }
        }
    }
    
    vector<vector<int>> combine(int n, int k) {
        this->n = n;
        this->k = k;
        
        vector<int> comb;
        vector<vector<int>> combs;
        
        backtrack(1, comb, combs);
        
        return combs;
    }
};
