//dfs + memorization, greedy
//https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/discuss/855041/C%2B%2BPython-DP-using-mask
//vector version
//Runtime: 64 ms, faster than 51.35% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
//Memory Usage: 26.8 MB, less than 11.50% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
//ARR version
//Runtime: 36 ms, faster than 75.04% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
//Memory Usage: 8.6 MB, less than 71.21% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
//ARR version: visited element in memo will always be >= 1, so we don't need to initialize memo as -1
//m: size of group1, n: size of group2
//time: O(m*2^n * n), it takes O(n) to compute each state
//space: O(m*2^n)
class Solution {
public:
    int m, n;

#define ARR
#ifdef ARR
    int memo[13][1<<12];
#else
    vector<vector<int>> memo;
#endif
    
    int dfs(vector<vector<int>>& cost, vector<int>& min_g2, int i, int mask){
#ifdef ARR
        if(memo[i][mask] != 0){
            return memo[i][mask]-1;
#else
        if(memo[i][mask] != -1){
            return memo[i][mask];
#endif
        }else if(i == m){
            int res = 0;
            
            for(int j = 0; j < n; ++j){
                //if j is not connected
                if(!(mask & (1<<j))){
                    res += min_g2[j];
                }
            }
#ifdef ARR
            memo[i][mask] = res + 1;
#else
            memo[i][mask] = res;
#endif
            return res;
        }else{
            int res = INT_MAX;
            
            for(int j = 0; j < n; ++j){
                res = min(res, 
                    cost[i][j] + dfs(cost, min_g2, i+1, mask | (1 << j)));
            }
#ifdef ARR
            memo[i][mask] = res + 1;
#else
            memo[i][mask] = res;
#endif
            return res;
        }
    }
    
    int connectTwoGroups(vector<vector<int>>& cost) {
        m = cost.size();
        n = cost[0].size();
        
        vector<int> min_g2(n, INT_MAX);
        
        for(int j = 0; j < n; ++j){
            for(int i = 0; i < m; ++i){
                min_g2[j] = min(min_g2[j], cost[i][j]);
            }
        }

#ifndef ARR
        memo = vector<vector<int>>(m+1, vector<int>(1<<12, -1));
#endif
        
        return dfs(cost, min_g2, 0, 0);
    }
};
