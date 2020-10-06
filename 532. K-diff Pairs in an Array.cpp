//Runtime: 28 ms, faster than 95.45% of C++ online submissions for K-diff Pairs in an Array.
//Memory Usage: 13.4 MB, less than 83.07% of C++ online submissions for K-diff Pairs in an Array.
class Solution {
public:
    struct pair_hash_int {
        inline std::size_t operator()(const std::pair<int,int> & v) const {
            return v.first*31+v.second;
        }
    };
    
    int findPairs(vector<int>& nums, int k) {
        int n = nums.size();
        
        unordered_set<pair<int, int>, pair_hash_int> pairs;
        
        sort(nums.begin(), nums.end());
        
        // for(const int& num : nums){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        for(int i = 0, j = 1; i < n && j < n; ){
            // cout << i << ", " << j << endl;
            if(nums[j] - nums[i] == k){
                // cout << "insert" << endl;
                pairs.insert({nums[i], nums[j]});
                ++i, ++j;
            }else if(nums[j] - nums[i] < k){
                ++j;
            }else{
                ++i;
                //j cannot be same as i
                if(j == i) ++j;
            }
        }
        
        return pairs.size();
    }
};
