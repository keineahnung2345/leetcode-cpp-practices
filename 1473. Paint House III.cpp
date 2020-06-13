//TLE
//24 / 59 test cases passed.
class Solution {
public:
    int ans;
    
    void backtrack(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target, int start, int curCost){
        // cout << "start: " << start << ", curCost: " << curCost << ", target: " << target << endl;
        // cout << "houses: ";
        // for(int i = 0; i < houses.size(); i++){
        //     cout << houses[i] << " ";
        // }
        // cout << endl;
        
        if(start == m){
            //reach end of houses
            //no more neighborhoods to add
            if(target == 0){
                ans = min(ans, curCost);
                // cout << "ans: " << ans << endl;
            }
        }else if(houses[start] != 0){
            //current house is already painted
            int newtarget = target;
            if(start == 0){
                // cout << "start is 0" << endl;
                newtarget = target-1;
            }else if(start > 0 && houses[start-1] != 0 && houses[start] != houses[start-1]){
                // cout << "color not equal to last" << endl;
                newtarget = target-1;
            }
            if(newtarget < 0) return;
            backtrack(houses, cost, m, n, newtarget, start+1, curCost);
        }else{
            for(int i = 0; i < n; i++){
                int newtarget = target;
                if(start == 0){
                    // cout << "start is 0" << endl;
                    newtarget = target-1;
                }else if(start > 0 && houses[start-1] != 0 && i+1 != houses[start-1]){
                    // cout << "color not equal to last" << endl;
                    newtarget = target-1;
                }
                if(newtarget < 0) continue;
                houses[start] = i+1;
                // cout << "target: " << target << " -> " << newtarget << endl;
                backtrack(houses, cost, m, n, newtarget, start+1, curCost+cost[start][i]);
                houses[start] = 0;
            }
        }
    };
    
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        ans = INT_MAX;
        backtrack(houses, cost, m, n, target, 0, 0);
        return (ans == INT_MAX) ? -1 : ans;
    }
};

//dfs + memorization
//TLE
//25 / 60 test cases passed.
//https://leetcode.com/problems/paint-house-iii/discuss/674313/Simple-Python-explanation-and-why-I-prefer-top-down-DP-to-bottom-up
//time: O(m*n^2*target), space: O(m*n*target)
class Solution {
public:
    /*
    m == houses.length == cost.length
    n == cost[i].length
    1 <= m <= 100
    1 <= n <= 20
    1 <= target <= m
    0 <= houses[i] <= n
    1 <= cost[i][j] <= 10^4
    max cost is 10^4 * 100 = 1e6
    */
    int MAX = 1e6+1;
    vector<int> houses;
    vector<vector<int>> cost;
    int m, n, target;
    vector<vector<vector<int>>> memo;
    
    int dfs(int start, int t, int prevColor){
        // cout << "(" << start << ",  " << t << ", " << prevColor << ")" << endl;
        if(t < 0 || t > m-start){
            /*
            t > m-start: 
            we only have (m-1)-(start-1) = m-start houses remained,
            but we need more neighborhoods
            */
            // cout << "(" << start << ",  " << t << ", " << prevColor << "): " << MAX << endl;
            return MAX;
        }else if(start == m){
            // cout << "(" << start << ",  " << t << ", " << prevColor << "): " << ((t == 0) ? 0 : MAX) << endl;
            return (t == 0) ? 0 : MAX;
        }else if(memo[start][t][prevColor+1] < MAX){
            return memo[start][t][prevColor+1];
        }else if(houses[start] != 0){
            memo[start][t][prevColor+1] = dfs(start+1, t - (houses[start] != prevColor), houses[start]);
            // cout << "(" << start << ",  " << t << ", " << prevColor << "): " << memo[start][t][prevColor+1] << endl;
            return memo[start][t][prevColor+1];
        }else{
            /*
            note that color = 0 means unpainted,
            and color's range is [1,n]!
            */
            for(int color = 1; color <= n; color++){
                int tmp = dfs(start+1, t - (color != prevColor), color);
                if(tmp < MAX){
                    memo[start][t][prevColor+1] = min(memo[start][t][prevColor+1], cost[start][color-1] + tmp);
                }
                // memo[start][t][prevColor] = min(memo[start][t][prevColor], cost[start][color-1] + dfs(start+1, t - (color != prevColor), color));
            }
            // cout << "(" << start << ",  " << t << ", " << prevColor << "): " << memo[start][t][prevColor+1] << endl;
            return memo[start][t][prevColor+1];
        }
    };
    
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        this->houses = houses;
        this->cost = cost;
        this->m = m;
        this->n = n;
        this->target = target;
        
        //t: [0, target]
        //prevColor: [-1, n] -> [0, n+1]
        memo = vector<vector<vector<int>>>(m, vector<vector<int>>(target+1, vector<int>(n+2, MAX)));
        
        /*
        set 0th color as -1,
        because when we paint 0th house,
        we will consume one neighborhood anyway
        */
        int ans = dfs(0, target, -1);
        return (ans >= MAX) ? -1 : ans;
    }
};
