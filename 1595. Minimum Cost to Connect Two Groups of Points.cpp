//dfs + memorization
//https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/discuss/855041/C%2B%2BPython-DP-using-mask
//Runtime: 64 ms, faster than 51.35% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
//Memory Usage: 26.8 MB, less than 11.50% of C++ online submissions for Minimum Cost to Connect Two Groups of Points.
class Solution {
public:
    int m, n;
    vector<vector<int>> memo;
    
    int dfs(vector<vector<int>>& cost, vector<int>& min_g2, int i, int mask){
        if(memo[i][mask] != -1){
            return memo[i][mask];
        }else if(i == m){
            int res = 0;
            
            for(int j = 0; j < n; ++j){
                //if j is not connected
                if(!(mask & (1<<j))){
                    res += min_g2[j];
                }
            }
            
            return memo[i][mask] = res;
        }else{
            int res = INT_MAX;
            
            for(int j = 0; j < n; ++j){
                res = min(res, 
                    cost[i][j] + dfs(cost, min_g2, i+1, mask | (1 << j)));
            }
            
            return memo[i][mask] = res;
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
        
        memo = vector<vector<int>>(m+1, vector<int>(1<<12, -1));
        
        return dfs(cost, min_g2, 0, 0);
    }
};
