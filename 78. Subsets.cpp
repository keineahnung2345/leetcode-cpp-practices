//Runtime: 4 ms, faster than 97.95% of C++ online submissions for Subsets.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Subsets.
class Solution {
public:
    void backtrack(vector<vector<int>>& ans, vector<int>& subset, vector<int>& nums, int k){
        if(subset.size() == k){
            ans.push_back(subset);
        }else{
            //set "start" so that the elements in subset are in ascending order
            int start = 0;
            if(subset.size() > 0){
                //start from the next element of subset[subset.size()-1]
                start = find(nums.begin(), nums.end(), subset[subset.size()-1]) - nums.begin() + 1;
            }
            // for(int e : nums){
            // for(int i = subset.size(); i < nums.size(); i++){
            for(int i = start; i < nums.size(); i++){
                int e = nums[i];
                // cout << start << " " << i << endl;
                subset.push_back(e);
                backtrack(ans, subset, nums, k);
                subset.pop_back();
            }
        }
    };
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> subset;
        
        //from empty set to itself
        for(int k = 0; k <= nums.size(); k++){
            backtrack(ans, subset, nums, k);
        }
        return ans;
    }
};

//https://leetcode.com/problems/permutations/discuss/18239/A-general-approach-to-backtracking-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partioning)
//Runtime: 4 ms, faster than 97.95% of C++ online submissions for Subsets.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Subsets.
class Solution {
public:
    void backtrack(vector<vector<int>>& ans, vector<int>& subset, vector<int>& nums, int start){
        ans.push_back(subset);
        for(int i = start; i < nums.size(); i++){
            subset.push_back(nums[i]);
            backtrack(ans, subset, nums, i+1);
            subset.pop_back();
        }
    };
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> subset;
        
        backtrack(ans, subset, nums, 0);
        
        return ans;
    }
};

//Approach 1: Recursion
//time: O(N*2^N), space: O(N*2^N)
//Runtime: 4 ms, faster than 97.95% of C++ online submissions for Subsets.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Subsets.
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans = {vector<int>()};
        
        for(int num : nums){
            // cout << "num: " << num << endl;
            int ans_size = ans.size();
            // for(vector<int>& subset : ans){
            for(int i = 0; i < ans_size; i++){
                vector<int> cur = ans[i];
                // cout << "subset size: " << cur.size() << endl;
                cur.push_back(num);
                ans.push_back(cur);
                // cout << "ans size: " << ans.size() << endl;
            }
        }
        
        return ans;
    }
};
