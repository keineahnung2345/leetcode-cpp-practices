//Runtime: 4 ms, faster than 99.58% of C++ online submissions for Subsets II.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Subsets II.

class Solution {
public:
    void backtrack(vector<vector<int>>& ans, vector<int>& subset, vector<int>& nums, int start){
        ans.push_back(subset);
        for(int i = start; i < nums.size(); i++){
            /*
            [1,4,4,4,4]
            0
            01
            012
            0123
            01234
            0124(equals 0123)
            013(equals 012)
            0134(equlas 0124)
            014(equlas 013)
            02(equals 01)
            023(equals 013)
            0234(equlas 0134)
            1
            12
            123
            1234
            124(equlas 123)
            13(equlas 12)
            134(equals 124)
            14(equals 13)
            2(equals 1)
            ...
            3(equals 2)
            ...
            4(equals 3)
            */
            if(i > start && nums[i] == nums[i-1]) continue;
            subset.push_back(nums[i]);
            backtrack(ans, subset, nums, i+1);
            subset.pop_back();
        }
    };
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> cur;
        
        //sorting here is important!
        sort(nums.begin(), nums.end());
        backtrack(ans, cur, nums, 0);
        
        return ans;
    }
};
