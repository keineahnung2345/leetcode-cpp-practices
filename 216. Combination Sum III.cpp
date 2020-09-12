//backtracking
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Combination Sum III.
//Memory Usage: 6.3 MB, less than 89.73% of C++ online submissions for Combination Sum III.
//time: O((9!/(9-K)!)*K), there are P(9,K) combinations and the last recursion takes O(n) time
//space: O(K)
class Solution {
public:
    void backtrack(int k, int n, vector<int>& cur, vector<vector<int>>& ans){
        if(cur.size() == k){
            if(accumulate(cur.begin(), cur.end(), 0) == n){
                ans.push_back(cur);
            }
        }else{
            for(int i = (cur.empty() ? 1 : cur.back()+1); i <= 9; ++i){
                cur.push_back(i);
                
                backtrack(k, n, cur, ans);
                
                cur.pop_back();
            }
        }
    }
    
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> cur;
        vector<vector<int>> ans;
        
        backtrack(k, n, cur, ans);
        
        return ans;
    }
};
