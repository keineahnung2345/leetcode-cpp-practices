//Brute force
//TLE
//40 / 41 test cases passed.
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(n-1, i+k); ++j){
                if(abs((long long)nums[i]-nums[j]) <= t){
                    return true;
                }
            }
        }
        
        return false;
    }
};
