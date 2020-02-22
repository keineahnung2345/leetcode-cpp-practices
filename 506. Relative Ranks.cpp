//Runtime: 16 ms, faster than 89.15% of C++ online submissions for Relative Ranks.
//Memory Usage: 11 MB, less than 33.33% of C++ online submissions for Relative Ranks.

class Solution {
public:
    template <typename T>
    vector<size_t> sort_indexes(const vector<T> &v) {

      // initialize original index locations
      vector<size_t> idx(v.size());
      iota(idx.begin(), idx.end(), 0);

      // sort indexes based on comparing values in v
      sort(idx.begin(), idx.end(),
           [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

      return idx;
    }
    
    vector<string> findRelativeRanks(vector<int>& nums) {
        vector<size_t> sixs = sort_indexes(nums);
        vector<string> ans(nums.size());
        for(int i = 0; i < sixs.size(); i++){
            int six = sixs[i];
            //the smaller i means nums[six] larger
            switch(i){
                case 0:
                    ans[six] = "Gold Medal";
                    break;
                case 1:
                    ans[six] = "Silver Medal";
                    break;
                case 2:
                    ans[six] = "Bronze Medal";
                    break;
                default:
                    ans[six] = to_string(i + 1);
            }
        }
        
        return ans;
    }
};
