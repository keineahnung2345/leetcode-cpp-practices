//Runtime: 32 ms, faster than 54.63% of C++ online submissions for Majority Element II.
//Memory Usage: 15.8 MB, less than 17.16% of C++ online submissions for Majority Element II.
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> counter;
        
        for(int& num : nums){
            ++counter[num];
        }
        
        vector<int> ans;
        int n = nums.size();
        
        for(auto it = counter.begin(); it != counter.end(); ++it){
            if(it->second > n/3){
                ans.push_back(it->first);
            }
        }
        
        return ans;
    }
};
