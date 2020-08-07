//Runtime: 244 ms, faster than 100.00% of C++ online submissions for Get the Maximum Score.
//Memory Usage: 55.8 MB, less than 100.00% of C++ online submissions for Get the Maximum Score.
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int MOD = 1e9+7;
        int n1 = nums1.size(), n2 = nums2.size();
        int i = 0, j = 0;
        
        vector<pair<int, int>> splits;
        
        while(i < n1 && j < n2){
            if(nums1[i] == nums2[j]){
                splits.push_back({i, j});
                ++i;
                ++j;
            }else if(nums1[i] < nums2[j]){
                ++i;
            }else{
                ++j;
            }
        }
        
        splits.push_back({n1-1,n2-1});
        
        int ans = 0;
        int li = -1, lj = -1;
        for(int k = 0; k < splits.size(); ++k){
            int i = splits[k].first;
            int j = splits[k].second;
            long seg = max(accumulate(nums1.begin()+li+1, nums1.begin()+i+1, 0L),
                       accumulate(nums2.begin()+lj+1, nums2.begin()+j+1, 0L));
            ans = (ans + seg%MOD) % MOD;
            li = i;
            lj = j;
        }
        
        return ans;
    }
};
