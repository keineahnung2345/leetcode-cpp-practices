//TLE
//20 / 27 test cases passed.
class Solution {
public:
    vector<vector<int>> memo;
    
    int change(int amount, vector<int>& coins, int start) {
        //coin >= 1
        if(start == coins.size()) return amount == 0;
        //impossible
        if(amount < 0) return 0;
        
        if(memo[start][amount] != 0){
            return memo[start][amount];
        }
        
        for(int times = 0; coins[start]*times <= amount; times++){
            int tmp = change(amount-coins[start]*times, coins, start+1);
            // cout << "coin: " << coins[start] << ", times: " << times << ", " << tmp << endl;
            memo[start][amount] += tmp;
            // memo[start][amount] += change(amount-coins[start]*times, coins, start+1);
        }
        
        // cout << "(" << start << ", " << amount << "): " << memo[start][amount] << endl;
        return memo[start][amount];
    }
    
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        if(n == 0) return amount == 0;
        //the range of amount is [0,5000]
        memo = vector<vector<int>>(n, vector<int>(5001));
        change(amount, coins, 0);
        
        return memo[0][amount];
    }
};
