//Runtime: 16 ms, faster than 99.73% of C++ online submissions for Permutations II.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Permutations II.

class Solution {
public:
    void backtrack(vector<vector<int>>& perms, vector<int>& perm, vector<int>& nums, vector<bool>& used){
        if(perm.size() == nums.size()){
            perms.push_back(perm);
        }else{
            /*
            [1,1,2]
            012
            021
            102(x because nums[1] == nums[0] && !used[0] )
            120(index 1 skipped)
            201
            210(x because nums[1] == nums[0] && !used[0])
            */
            for(int i = 0; i < nums.size(); i++){
                if(used[i]) continue;
                //nums[i] plays the role of nums[i-1]
                if(i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
                perm.push_back(nums[i]);
                used[i] = true;
                backtrack(perms, perm, nums, used);
                perm.pop_back();
                used[i] = false;
            }
        }
    };
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int N = nums.size();
        vector<vector<int>> ans;
        vector<int> perm;
        vector<bool> used(N, false);
        
        //sort is important!
        sort(nums.begin(), nums.end());
        backtrack(ans, perm, nums, used);
        
        return ans;
    }
};
