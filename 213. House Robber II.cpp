//DP
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for House Robber II.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for House Robber II.
class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return 0;
        if(N <= 3) return *max_element(nums.begin(), nums.end());
        vector<int> dpA = nums, dpB = nums;
        
        //0~N-2
        for(int i = N-3; i >= 0; i--){
            dpA[i] += max(((i+2 < N-1) ? dpA[i+2] : 0), 
                          ((i+3 < N-1) ? dpA[i+3] : 0));
        }
        
        //1~N-1
        for(int i = N-3; i >= 1; i--){
            dpB[i] += max(((i+2 < N) ? dpB[i+2] : 0), 
                          ((i+3 < N) ? dpB[i+3] : 0));
        }
        
        return max(max(dpA[0], dpA[1]), 
                   max(dpB[1], dpB[2]));
        
        // return max(dpA[0], dpB[1]);
    }
};
