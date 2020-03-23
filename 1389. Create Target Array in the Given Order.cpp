//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Create Target Array in the Given Order.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Create Target Array in the Given Order.
class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        vector<int> ans;
        
        for(int i = 0; i < index.size(); i++){
            ans.insert(ans.begin() + index[i], nums[i]);
        }
        
        return ans;
    }
};
