//Runtime: 12 ms, faster than 64.52% of C++ online submissions for Permutations.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Permutations.
class Solution {
public:
    void backtrack(vector<vector<int>>& pers, vector<int>& per, vector<int>& nums){
        if(per.size() == nums.size()){
            pers.push_back(per);
        }else{
            for(int e : nums){
                if(find(per.begin(), per.end(), e) != per.end()){
                    continue;
                }
                per.push_back(e);
                backtrack(pers, per, nums);
                per.pop_back();
            }
        }
    };
    
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> pers;
        vector<int> per;
        
        backtrack(pers, per, nums);
        
        return pers;
    }
};
