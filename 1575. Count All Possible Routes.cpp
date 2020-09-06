//recursion + memorization
//https://leetcode.com/problems/count-all-possible-routes/discuss/830400/Dynamic-Programming-or-Simple-Explanation
//Runtime: 148 ms, faster than 28.57% of C++ online submissions for Count All Possible Routes.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Count All Possible Routes.
//time: O(fuel*N*N), space: O(fuel*N)
class Solution {
public:
    int MOD = 1e9+7;
    //location: [2,100], fuel: [1,200]
    int memo[101][201];
    int n;
    
    int dfs(vector<int>& A, int finish, int cur, int cur_fuel){
        if(cur_fuel < 0){
            return 0;
        }else if(memo[cur][cur_fuel] != -1){
            return memo[cur][cur_fuel];
        }else{
            //cur_fuel >= 0
            //if cur == finish, we have found a possible way
            int ways = (cur == finish);
            
            if(cur_fuel > 0){
                for(int next = 0; next < n; ++next){
                    if(next == cur) continue;
                    ways = (ways +
                        dfs(A, finish, next, cur_fuel - abs(A[cur]-A[next]))) % MOD;
                }
            }
            
            return memo[cur][cur_fuel] = ways;
        }
    };
    
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        /*
        first we should observe that the "state" is (location, fuel),
        so we can use recursion + memorization
        */
        
        n = locations.size();
        
        memset(memo, -1, sizeof(memo));
        
        return dfs(locations, finish, start, fuel);
    }
};
