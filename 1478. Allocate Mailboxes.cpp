//recursion
//TLE
//31 / 69 test cases passed.
//https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n3)
class Solution {
public:
    /*
    1 <= houses.length <= 100
    1 <= houses[i] <= 10^4
    1 <= k <= houses.length
    
    one mailbox's cost: at most 100*1e4
    k mailboxes' cost: at most 100*100*1e4
    */
    int MAX = 1e8;
    
    int dfs(vector<int>& houses, int k, int start){
        if(k == 0 && start == houses.size()) return 0;
        if(k == 0 || start == houses.size()) return MAX;
        
        int ans = MAX;
        
        for(int end = start; end < houses.size(); end++){
            /*
            put one mailbox in [start, end] and 
            remaining k-1 mailboxes in [end+1, n-1]
            */
            /*
            if there are even houses, 
            cost is minimum when mailbox is put inbetween
            the two middle houses
            if there are odd houses,
            cost is minimum when mailbox is put at the middle house
            */
            int median = houses[(start+end)/2];
            int cost = 0;
            for(int i = start; i <= end; i++){
                cost += abs(houses[i] - median);
            }
            ans = min(ans, cost + dfs(houses, k-1, end+1));
        }
        
        return ans;
    };
    
    int minDistance(vector<int>& houses, int k) {
        //this is important because we need to calculate median!
        sort(houses.begin(), houses.end());
        return dfs(houses, k, 0);
    }
};

//recursion + memorization
//https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n3)
//Runtime: 748 ms, faster than 16.67% of C++ online submissions for Allocate Mailboxes.
//Memory Usage: 8.4 MB, less than 100.00% of C++ online submissions for Allocate Mailboxes.
class Solution {
public:
    int MAX = 1e8;
    vector<vector<int>> memo;
    
    int dfs(vector<int>& houses, int k, int start){
        if(k == 0 && start == houses.size()) return 0;
        if(k == 0 || start == houses.size()) return MAX;
        if(memo[k][start] != 0) return memo[k][start];
        
        int ans = MAX;
        
        for(int end = start; end < houses.size(); end++){
            int median = houses[(start+end)/2];
            int cost = 0;
            for(int i = start; i <= end; i++){
                cost += abs(houses[i] - median);
            }
            ans = min(ans, cost + dfs(houses, k-1, end+1));
        }
        
        return memo[k][start] = ans;
    };
    
    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(), houses.end());
        //k = 0 for padding
        memo = vector<vector<int>>(k+1, vector<int>(houses.size()));
        return dfs(houses, k, 0);
    }
};

//recursion + memorization + cache cost
//https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n3)
//Runtime: 284 ms, faster than 66.67% of C++ online submissions for Allocate Mailboxes.
//Memory Usage: 9.2 MB, less than 66.67% of C++ online submissions for Allocate Mailboxes.
//time: O(n^3 + k*n^2), O(n^3) for calculating cost, O(k*n^2) for k*n states of dp, each takes O(n)
//space: O(n^2)
class Solution {
public:
    int MAX = 1e8;
    vector<vector<int>> cost;
    vector<vector<int>> memo;
    
    int dfs(vector<int>& houses, int k, int start){
        if(k == 0 && start == houses.size()) return 0;
        if(k == 0 || start == houses.size()) return MAX;
        if(memo[k][start] != 0) return memo[k][start];
        
        int ans = MAX;
        
        for(int end = start; end < houses.size(); end++){
            ans = min(ans, cost[start][end] + dfs(houses, k-1, end+1));
        }
        
        return memo[k][start] = ans;
    };
    
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        sort(houses.begin(), houses.end());
        memo = vector<vector<int>>(k+1, vector<int>(n));
        
        //precalculate cost of [i, j]
        cost = vector<vector<int>>(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                for(int k = i; k <= j; k++){
                    cost[i][j] += abs(houses[(i+j)/2] - houses[k]);
                }
            }
        }
        
        return dfs(houses, k, 0);
    }
};

//bottom-up dp
//Runtime: 36 ms, faster than 100.00% of C++ online submissions for Allocate Mailboxes.
//Memory Usage: 9.4 MB, less than 50.00% of C++ online submissions for Allocate Mailboxes.
class Solution {
public:
    int MAX = 1e8;
    
    int minDistance(vector<int>& houses, int k) {
        int n = houses.size();
        sort(houses.begin(), houses.end());
        
        vector<vector<int>> dp(k+1, vector<int>(n+1));
        
        vector<vector<int>> cost(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                for(int k = i; k <= j; k++){
                    cost[i][j] += abs(houses[(i+j)/2] - houses[k]);
                }
            }
        }
        
        //if(k == 0 && start == houses.size()) return 0;
        dp[0][n] = 0;
        //if(k == 0 || start == houses.size()) return MAX;
        for(int start = 1; start < n; start++){
            dp[0][start] = MAX;
        }
        for(int kk = 1; kk <= k; kk++){
            dp[kk][n] = MAX;
        }
        
        for(int kk = 1; kk <= k; kk++){
            for(int start = 0; start < n; start++){
                int res = MAX;
                for(int end = start; end < n; end++){
                    res = min(res, cost[start][end] + dp[kk-1][end+1]);
                }
                
                dp[kk][start] = res;
            }
        }
        
        return dp[k][0];
    }
};
