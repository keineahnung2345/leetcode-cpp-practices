//LIS
//Runtime: 1360 ms, faster than 17.56% of C++ online submissions for Russian Doll Envelopes.
//Memory Usage: 16.5 MB, less than 16.67% of C++ online submissions for Russian Doll Envelopes.
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 1);
        int ans = 1;

        //the envelopes with smaller width/height are put before
        sort(envelopes.begin(), envelopes.end());
        
        //LIS
        for(int j = 1; j < n; j++){
            for(int i = 0; i < j; i++){
                //stricter condition than ordinal LIS
                if(envelopes[i][0] < envelopes[j][0] && envelopes[i][1] < envelopes[j][1]){
                    dp[j] = max(dp[j], dp[i]+1);
                }
            }
            ans = max(ans, dp[j]);
        }

        return ans;
    }
};
