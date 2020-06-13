//WA
//35 / 41 test cases passed.
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return nums;
        vector<vector<int>> subsets;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; i++){
            for(vector<int>& subset : subsets){
                if(nums[i] % subset.back() == 0){
                    subset.push_back(nums[i]);
                }
            }
            subsets.push_back({nums[i]});
        }
        
        // for(vector<int>& subset : subsets){
        //     for(int e : subset){
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }
        
        sort(subsets.begin(), subsets.end(),
            [](const vector<int>& a, const vector<int>& b){
                return (a.size() == b.size()) ? a[0] < b[0] : a.size() > b.size();
            });
        
        return subsets[0];
    }
};
