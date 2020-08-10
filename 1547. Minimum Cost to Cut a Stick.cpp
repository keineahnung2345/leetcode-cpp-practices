//dfs + memorization
//https://leetcode.com/problems/minimum-cost-to-cut-a-stick/discuss/780880/DP-with-picture-(Burst-Balloons)
//Runtime: 124 ms, faster than 25.00% of C++ online submissions for Minimum Cost to Cut a Stick.
//Memory Usage: 10.4 MB, less than 25.00% of C++ online submissions for Minimum Cost to Cut a Stick.
class Solution {
public:
    vector<vector<int>> memo;
    
    int dfs(vector<int>& cuts, int i, int j){
        if(memo[i][j] != INT_MAX){
            return memo[i][j];
        }
        
        /*
        there must be one cut inbetween cuts[i] and cuts[j],
        so that we can cut this segment
        */
        if(j - i <= 1){
            return memo[i][j] = 0;
        }
        
        /*
        find a place(cuts[k]) to cut
        cuts[j] - cuts[i] is the length of current segment
        */
        for(int k = i+1; k < j; ++k){
            memo[i][j] = min(memo[i][j],
                cuts[j] - cuts[i] + dfs(cuts, i, k) + dfs(cuts, k, j));
        }
        
        return memo[i][j];
    };
    
    int minCost(int n, vector<int>& cuts) {
        /*
        we can add these two elements into cuts,
        because we will never actually cut in 0 and n
        */
        cuts.push_back(0);
        cuts.push_back(n);
        
        sort(cuts.begin(), cuts.end());
        
        memo = vector<vector<int>>(cuts.size(), vector<int>(cuts.size(), INT_MAX));
        
        return dfs(cuts, 0, cuts.size()-1);
    }
};

//bottom-up DP
//https://leetcode.com/problems/minimum-cost-to-cut-a-stick/discuss/780880/DP-with-picture-(Burst-Balloons)
//Runtime: 80 ms, faster than 25.00% of C++ online submissions for Minimum Cost to Cut a Stick.
//Memory Usage: 10.4 MB, less than 25.00% of C++ online submissions for Minimum Cost to Cut a Stick.
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        /*
        we can add these two elements into cuts,
        because we will never actually cut in 0 and n
        */
        cuts.push_back(0);
        cuts.push_back(n);
        
        sort(cuts.begin(), cuts.end());
        
        vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size()));
        
        for(int i = cuts.size()-1; i >= 0; --i){
            //[cuts[i], cuts[j]] defines the segment
            /*
            note that j starts from i+2, 
            because [cuts[i],cuts[i+1]] should always be 0
            */
            for(int j = i+2; j < cuts.size(); ++j){
                dp[i][j] = INT_MAX;
                for(int k = i+1; k < j; ++k){
                    dp[i][j] = min(dp[i][j], cuts[j] - cuts[i] + dp[i][k] + dp[k][j]);
                }
            }
        }
        
        return dp[0][cuts.size()-1];
    }
};
